use crate::elf::{Elf, Relocation, Section, Symbol};
use anyhow::{anyhow, bail, Result};
use std::cell::{OnceCell, RefCell};
use std::collections::{BTreeMap, BTreeSet, HashMap};
use std::rc::Rc;

pub type Sections = BTreeMap<usize, (usize, i64)>;

const ASM_LEAF_FUNCTIONS: &[&str] = &[
    "OSDisableInterrupts",
    "OSEnableInterrupts",
    "OSRestoreInterrupts",
    "LCDisable",
    "LCStoreBlocks",
    "LCQueueWait",
    "__LCEnable",
    "__OSPSInit",
    "DCInvalidateRange",
    "DCFlushRange",
    "DCStoreRange",
    "DCFlushRangeNoSync",
    "DCStoreRangeNoSync",
    "DCZeroRange",
    "ICInvalidateRange",
    "OSGetTime",
    "HSD_ByteCodeEval",
    "PPCHalt",
    "__start",
    "TRKInterruptHandler",
    "TRKSwapAndGo",
    "TRKInterruptHandlerEnableInterrupts",
    "TRKSaveExtended1Block",
    "TRKRestoreExtended1Block",
    "TRKLoadContext",
    "InitMetroTRK",
    "ExternalInterruptHandler",
    "__init_registers",
    "__init_hardware",
    "__flush_cache",
    "TRK_flush_cache",
    "TRK_ppc_memcpy",
    "TRKExceptionHandler",
    "__cvt_fp2unsigned",
    "__div2u",
    "__div2i",
    "__mod2u",
    "__mod2i",
    "__shl2i",
    "__shr2u",
    "__shr2i",
    "__cvt_sll_flt",
    "__cvt_dbl_usll",
    "GetR2",
    "__DBExceptionDestination",
    "__AICallbackStackSwitch",
    "PSMTXIdentity",
    "PSMTXCopy",
    "PSMTXConcat",
    "PSMTXTranspose",
    "PSMTXInverse",
    "PSMTXInvXpose",
    "PSMTXRotRad",
    "PSMTXRotTrig",
    "PSMTXRotAxisRad",
    "PSMTXTrans",
    "PSMTXScale",
    "PSMTXQuat",
    "PSMTXMultVec",
    "PSMTXMultVecArray",
    "PSMTXMultVecSR",
    "PSVECAdd",
    "PSVECSubtract",
    "PSVECScale",
    "PSVECNormalize",
    "PSVECMag",
    "PSVECDotProduct",
    "PSVECCrossProduct",
    "WriteMTXPS4x3",
    "WriteMTXPS3x3from3x4",
    "WriteMTXPS4x2",
    "__THPDecompressYUV",
    "__THPDecompressiMCURow512x448",
    "__THPDecompressiMCURow640x480",
    "__THPDecompressiMCURowNxN",
    "__THPHuffDecodeDCTCompY",
    "__THPHuffDecodeDCTCompU",
    "__THPHuffDecodeDCTCompV",
    "THPInit",
    "__OSDBIntegrator",
    "__OSDBJump",
    "OSExceptionVector",
    "OSDefaultExceptionHandler",
    "DecrementerExceptionHandler",
    "__OSLoadFPUContext",
    "__OSSaveFPUContext",
    "OSSetCurrentContext",
    "OSSaveContext",
    "OSLoadContext",
    "OSGetStackPointer",
    "OSInitContext",
    "OSSwitchFPUContext",
    "OSFillFPUContext",
    "Config24MB",
    "Config48MB",
    "RealMode",
    "Run",
    "Reset",
    "SystemCallVector",
    "HSD_SaveContext",
];

fn stem(name: &str) -> Option<&str> {
    let at = name.rfind('$')?;
    let digits = &name[at + 1..];
    (at > 0 && !digits.is_empty() && digits.bytes().all(|byte| byte.is_ascii_digit()))
        .then(|| &name[..at])
}

fn dollar_name(name: &str) -> Option<String> {
    let at = name.rfind('_')?;
    let digits = &name[at + 1..];
    (at > 0 && !digits.is_empty() && digits.bytes().all(|byte| byte.is_ascii_digit()))
        .then(|| format!("{}${digits}", &name[..at]))
}

fn slice(data: &[u8], start: i64, size: i64) -> &[u8] {
    let start = (start.max(0) as usize).min(data.len());
    let end = (start + size.max(0) as usize).min(data.len());
    &data[start..end]
}

fn contains(start: u32, size: u32, address: i64) -> bool {
    i64::from(start) <= address && address < i64::from(start) + i64::from(size)
}

fn within(owner: &Symbol, relocation: &Relocation) -> bool {
    relocation.section == owner.section
        && contains(owner.address, owner.size, i64::from(relocation.address))
}

fn valid(elf: &Elf, section: usize) -> bool {
    0 < section && section < elf.sections.len()
}

fn section_of(elf: &Elf, index: usize) -> Result<&Section> {
    elf.sections
        .get(index)
        .ok_or_else(|| anyhow!("Section index {index} is out of range."))
}

fn symbol_of(elf: &Elf, index: usize) -> Result<&Symbol> {
    elf.symbols
        .get(index)
        .ok_or_else(|| anyhow!("Symbol index {index} is out of range."))
}

fn base_of(elf: &Elf, section: &Section) -> i64 {
    if elf.kind == 2 {
        i64::from(section.address)
    } else {
        0
    }
}

fn put32(data: &mut [u8], offset: usize, value: i64) -> Result<()> {
    data.get_mut(offset..offset + 4)
        .ok_or_else(|| anyhow!("Write past the end of the data at {offset:#X}."))?
        .copy_from_slice(&(value as u32).to_be_bytes());
    Ok(())
}

fn get32(data: &[u8], offset: usize) -> Result<u32> {
    let bytes = data
        .get(offset..offset + 4)
        .ok_or_else(|| anyhow!("Read past the end of the data at {offset:#X}."))?;
    Ok(u32::from_be_bytes([bytes[0], bytes[1], bytes[2], bytes[3]]))
}

fn unique_places(candidates: &[Symbol]) -> usize {
    candidates
        .iter()
        .map(|target| (target.address, target.section))
        .collect::<BTreeSet<_>>()
        .len()
}

type Referenced<'a> = Rc<Vec<&'a Symbol>>;

struct Link<'a> {
    compiled: &'a Elf,
    reference: &'a Elf,
    placement: i64,
    files: OnceCell<HashMap<&'a Symbol, usize>>,
    referenced: RefCell<HashMap<(usize, u32, u32), Referenced<'a>>>,
}

impl<'a> Link<'a> {
    fn files(&self) -> &HashMap<&'a Symbol, usize> {
        self.files.get_or_init(|| {
            let mut files = HashMap::new();
            let mut owner = None;
            for (index, symbol) in self.reference.symbols.iter().enumerate() {
                if symbol.kind() == 4 {
                    owner = Some(index);
                } else if symbol.binding() == 0 {
                    if let Some(owner) = owner {
                        files.insert(symbol, owner);
                    }
                }
            }
            files
        })
    }

    fn referenced(&self, function: &Symbol) -> Referenced<'a> {
        let key = (function.section, function.address, function.size);
        if let Some(found) = self.referenced.borrow().get(&key) {
            return Rc::clone(found);
        }
        let found: Referenced = Rc::new(
            self.reference
                .relocations
                .iter()
                .filter(|relocation| within(function, relocation))
                .filter_map(|relocation| self.reference.symbols.get(relocation.symbol))
                .collect(),
        );
        self.referenced.borrow_mut().insert(key, Rc::clone(&found));
        found
    }

    fn owners(&self, section: usize, address: i64) -> Vec<&'a Symbol> {
        self.compiled
            .functions()
            .iter()
            .filter(|owner| {
                owner.section == section && contains(owner.address, owner.size, address)
            })
            .collect()
    }

    fn users(&self, symbol: &Symbol) -> Vec<&'a Symbol> {
        self.compiled
            .functions()
            .iter()
            .filter(|owner| {
                self.compiled.relocations.iter().any(|relocation| {
                    within(owner, relocation)
                        && self.compiled.symbols.get(relocation.symbol) == Some(symbol)
                })
            })
            .collect()
    }

    fn source(&self, function: &Symbol) -> Result<&'a Symbol> {
        let sources: Vec<&Symbol> = self
            .compiled
            .functions()
            .iter()
            .filter(|source| source.name == function.name)
            .collect();
        if sources.len() != 1 {
            bail!("Expected one compiled function named {}.", function.name);
        }
        Ok(sources[0])
    }

    fn original_function(&self, name: &str, primary: &Symbol) -> Result<Symbol> {
        if name == primary.name {
            return Ok(primary.clone());
        }
        let mut originals: Vec<Symbol> = self
            .reference
            .functions()
            .iter()
            .filter(|function| function.name == name)
            .cloned()
            .collect();
        if originals.len() > 1 {
            let sources: Vec<&Symbol> = self
                .compiled
                .functions()
                .iter()
                .filter(|source| source.name == name)
                .collect();
            if sources.len() == 1 && sources[0].binding() == 0 {
                originals = self.local_file_candidates(originals);
            }
        }
        if originals.len() != 1 {
            bail!("Emitted function has no unique original: {name}");
        }
        Ok(originals.remove(0))
    }

    fn local_file_candidates(&self, candidates: Vec<Symbol>) -> Vec<Symbol> {
        let files = self.files();
        let mut anchors = BTreeSet::new();
        for source in self.compiled.functions() {
            let originals: Vec<&Symbol> = self
                .reference
                .functions()
                .iter()
                .filter(|target| target.name == source.name && target.info == source.info)
                .collect();
            if originals.len() != 1 || originals[0].size != source.size {
                continue;
            }
            let original = originals[0];
            if let Some(&owner) = files.get(original) {
                anchors.insert(owner);
            }
            for relocation in &self.compiled.relocations {
                if !within(source, relocation)
                    || relocation.addend != 0
                    || ![4, 6, 10].contains(&relocation.kind)
                {
                    continue;
                }
                let Some(callback) = self.compiled.symbols.get(relocation.symbol) else {
                    continue;
                };
                if callback.info != 2 || !self.compiled.functions().contains(callback) {
                    continue;
                }
                let site = i64::from(original.address) + i64::from(relocation.address)
                    - i64::from(source.address);
                let referenced: Vec<&Symbol> = self
                    .reference
                    .relocations
                    .iter()
                    .filter(|item| {
                        item.section == original.section
                            && i64::from(item.address) == site
                            && item.kind == relocation.kind
                            && item.addend == 0
                    })
                    .filter_map(|item| self.reference.symbols.get(item.symbol))
                    .collect();
                if referenced.len() != 1 {
                    continue;
                }
                let target = referenced[0];
                if target.info == callback.info
                    && target.name == callback.name
                    && target.size == callback.size
                {
                    if let Some(&owner) = files.get(target) {
                        anchors.insert(owner);
                    }
                }
            }
        }
        if anchors.len() != 1 {
            return candidates;
        }
        let owner = anchors.into_iter().next();
        candidates
            .into_iter()
            .filter(|target| files.get(target).copied() == owner)
            .collect()
    }

    fn constant_data(&self, symbol: &Symbol, function: &Symbol) -> Result<Vec<u8>> {
        let compiled = self.compiled;
        let reference = self.reference;
        let mut data = compiled.symbol_data(symbol)?.to_vec();
        let source = self.source(function)?;
        let mut covered = BTreeSet::new();
        for relocation in &compiled.relocations {
            if !within(symbol, relocation) {
                continue;
            }
            let offset = (relocation.address - symbol.address) as usize;
            if relocation.kind != 1 {
                bail!("Unsupported constant relocation: {}", relocation.kind);
            }
            if !offset.is_multiple_of(4) || offset + 4 > data.len() || covered.contains(&offset) {
                bail!("Constant relocation overlaps or exceeds its data.");
            }
            let target = symbol_of(compiled, relocation.symbol)?;
            let address = i64::from(target.address) + i64::from(relocation.addend);
            if target.section == 0 && target.kind() == 0 && relocation.addend == 0 {
                let originals: Vec<&Symbol> = reference
                    .named(&target.name)
                    .into_iter()
                    .filter(|item| {
                        item.kind() == 2
                            && item.size != 0
                            && valid(reference, item.section)
                            && reference.sections[item.section].flags & 4 != 0
                    })
                    .collect();
                if originals.len() != 1 {
                    bail!(
                        "Constant callback has no unique original function: {}",
                        target.name
                    );
                }
                covered.insert(offset);
                put32(&mut data, offset, i64::from(originals[0].address))?;
                continue;
            }
            if target.kind() == 1
                && target.name.starts_with('@')
                && relocation.addend == 0
                && valid(compiled, target.section)
            {
                let section = &compiled.sections[target.section];
                let start = i64::from(target.address) - base_of(compiled, section);
                if section.kind != 1
                    || section.flags & 4 != 0
                    || target.size == 0
                    || start < 0
                    || start + i64::from(target.size) > i64::from(section.size)
                    || compiled.relocations.iter().any(|item| within(target, item))
                {
                    bail!("Constant literal pointer has invalid initialized storage.");
                }
                let tables = self.referenced(function);
                let mut originals = BTreeSet::new();
                for table in tables.iter() {
                    if table.kind() != 1
                        || table.size != symbol.size
                        || !valid(reference, table.section)
                        || reference.sections[table.section].kind != 1
                        || reference.sections[table.section].flags & 4 != 0
                    {
                        continue;
                    }
                    let address = get32(reference.symbol_data(table)?, offset)?;
                    for literal in &reference.symbols {
                        if literal.address != address
                            || literal.size != target.size
                            || literal.info != target.info
                            || !valid(reference, literal.section)
                        {
                            continue;
                        }
                        let original_section = &reference.sections[literal.section];
                        let original_offset =
                            i64::from(literal.address) - i64::from(original_section.address);
                        if original_section.kind == 1
                            && original_section.flags & 4 == 0
                            && original_section.name == section.name
                            && original_offset >= 0
                            && literal.size != 0
                            && original_offset + i64::from(literal.size)
                                <= i64::from(original_section.size)
                            && reference.symbol_data(literal)? == compiled.symbol_data(target)?
                        {
                            originals.insert((literal.address, literal.section));
                        }
                    }
                }
                if originals.len() != 1 {
                    bail!("Constant literal pointer has no unique original table entry.");
                }
                covered.insert(offset);
                let original = originals.into_iter().next().unwrap_or_default().0;
                put32(&mut data, offset, i64::from(original))?;
                continue;
            }
            if target.section != source.section
                || address.rem_euclid(4) != 0
                || !contains(source.address, source.size, address)
            {
                bail!("Constant relocation leaves its compiled function.");
            }
            if self.placement != i64::from(function.address) {
                bail!("{} has a jump table and cannot move.", function.name);
            }
            covered.insert(offset);
            put32(
                &mut data,
                offset,
                i64::from(function.address) + address - i64::from(source.address),
            )?;
        }
        Ok(data)
    }

    fn resolve_symbol(
        &self,
        symbol: &Symbol,
        function: &Symbol,
        data_sections: Option<&Sections>,
        site: Option<i64>,
    ) -> Result<Symbol> {
        let compiled = self.compiled;
        let reference = self.reference;
        if let Some(&(target_section, base)) =
            data_sections.and_then(|sections| sections.get(&symbol.section))
        {
            let section = section_of(compiled, symbol.section)?;
            let offset = i64::from(symbol.address) - base_of(compiled, section);
            if offset < 0 || offset + i64::from(symbol.size) > i64::from(section.size) {
                bail!("Data symbol exceeds its verified section: {}", symbol.name);
            }
            return Ok(Symbol {
                address: u32::try_from(base + offset).map_err(|_| {
                    anyhow!("Data symbol leaves the address space: {}", symbol.name)
                })?,
                section: target_section,
                ..symbol.clone()
            });
        }
        let referenced = self.referenced(function);
        let local_name = if symbol.kind() == 1 && symbol.binding() == 0 {
            stem(&symbol.name)
        } else {
            None
        };
        let mut candidates: Vec<Symbol>;
        if symbol.name.starts_with('@') && valid(compiled, symbol.section) {
            let data = self.constant_data(symbol, function)?;
            candidates = Vec::new();
            for target in referenced.iter() {
                if target.size as usize == data.len()
                    && valid(reference, target.section)
                    && reference.sections[target.section].kind != 8
                    && reference.symbol_data(target)? == data
                {
                    candidates.push((*target).clone());
                }
            }
            if unique_places(&candidates) > 1 {
                let identical = candidates.clone();
                let section = &compiled.sections[symbol.section];
                if section.kind == 1
                    && section.flags & 4 == 0
                    && !compiled
                        .relocations
                        .iter()
                        .any(|relocation| relocation.section == symbol.section)
                {
                    let pool = compiled.section_data(section)?;
                    let source_offset = i64::from(symbol.address) - base_of(compiled, section);
                    let size = i64::from(section.size);
                    let mut placements = Vec::new();
                    for target in &candidates {
                        let original_section = &reference.sections[target.section];
                        let base = i64::from(target.address) - source_offset;
                        let offset = base - i64::from(original_section.address);
                        if original_section.kind == 1
                            && original_section.flags & 4 == 0
                            && original_section.name == section.name
                            && base.rem_euclid(i64::from(section.alignment.max(1))) == 0
                            && offset >= 0
                            && size > 0
                            && offset + size <= i64::from(original_section.size)
                            && pool.len() as i64 == size
                            && slice(reference.section_data(original_section)?, offset, size)
                                == pool
                        {
                            placements.push(target.clone());
                        }
                    }
                    candidates = placements;
                }
                if candidates.len() != 1 {
                    if let Some(site) = site {
                        let address = i64::from(function.address) + site;
                        let sited: Vec<&Symbol> = reference
                            .relocations
                            .iter()
                            .filter(|relocation| {
                                relocation.section == function.section
                                    && i64::from(relocation.address) == address
                            })
                            .filter_map(|relocation| reference.symbols.get(relocation.symbol))
                            .collect();
                        candidates = identical
                            .into_iter()
                            .filter(|target| sited.contains(&target))
                            .collect();
                    }
                }
            }
        } else if let Some(local_name) = local_name {
            candidates = referenced
                .iter()
                .filter(|target| {
                    target.kind() == 1
                        && target.binding() == 0
                        && stem(&target.name) == Some(local_name)
                })
                .map(|target| (*target).clone())
                .collect();
        } else {
            candidates = reference
                .named(&symbol.name)
                .into_iter()
                .filter(|target| target.section != 0)
                .cloned()
                .collect();
            let local: Vec<Symbol> = candidates
                .iter()
                .filter(|target| referenced.contains(target))
                .cloned()
                .collect();
            if !local.is_empty() {
                candidates = local;
            } else if candidates.len() > 1 && symbol.binding() == 0 && symbol.section != 0 {
                candidates = self.local_file_candidates(candidates);
            } else if candidates.len() > 1
                && symbol.kind() == 1
                && symbol.binding() != 0
                && symbol.section != 0
            {
                candidates.retain(|target| target.info == symbol.info);
            }
        }
        if unique_places(&candidates) != 1 {
            bail!(
                "Unresolved or ambiguous symbol in {}: {}",
                function.name,
                symbol.name
            );
        }
        candidates
            .pop()
            .ok_or_else(|| anyhow!("Unresolved symbol: {}", symbol.name))
    }

    fn data_pool_bases(&self, primary: &Symbol, kind: u32) -> Result<Sections> {
        let compiled = self.compiled;
        let reference = self.reference;
        let mut sections = Sections::new();
        let root_names: &[&str] = if kind == 1 {
            &["...data.0", "...rodata.0"]
        } else {
            &["...bss.0"]
        };
        for (index, root) in compiled.symbols.iter().enumerate() {
            if !root_names.contains(&root.name.as_str())
                || root.kind() != 0
                || root.size != 0
                || !valid(compiled, root.section)
            {
                continue;
            }
            let read_only = root.name == "...rodata.0";
            let section = &compiled.sections[root.section];
            if section.kind != kind || section.flags & 4 != 0 {
                bail!("Compiler data-pool base has the wrong section type.");
            }
            if read_only && (section.name != ".rodata" || section.flags != 2) {
                bail!("Compiler read-only pool has the wrong section type.");
            }
            let offset = i64::from(root.address) - base_of(compiled, section);
            if offset < 0 || offset >= i64::from(section.size) {
                bail!("Compiler data-pool base exceeds its section.");
            }
            let mut unmatched = None;
            for relocation in &compiled.relocations {
                if relocation.symbol != index
                    || section_of(compiled, relocation.section)?.flags & 4 == 0
                {
                    continue;
                }
                let owners = self.owners(relocation.section, i64::from(relocation.address));
                if owners.len() != 1 {
                    bail!("Data-pool reference has no unique compiled function owner.");
                }
                let owner = self.original_function(&owners[0].name, primary)?;
                let site = i64::from(relocation.address) - i64::from(owners[0].address);
                let mut originals = BTreeSet::new();
                for item in &reference.relocations {
                    if !within(&owner, item) {
                        continue;
                    }
                    let target = symbol_of(reference, item.symbol)?;
                    if target.name == root.name
                        && (!read_only
                            || (i64::from(item.address) - i64::from(owner.address) == site
                                && item.kind == relocation.kind
                                && item.addend == relocation.addend))
                    {
                        originals.insert(target);
                    }
                }
                if originals.len() != 1 {
                    if originals.is_empty() {
                        unmatched = Some(owner.name.clone());
                        continue;
                    }
                    bail!(
                        "Data-pool reference has no unique original base: {} ({} at {site:#x}, {} matches)",
                        owner.name,
                        root.name,
                        originals.len()
                    );
                }
                let Some(target) = originals.into_iter().next() else {
                    continue;
                };
                if target.kind() != 0 || target.size != 0 || !valid(reference, target.section) {
                    bail!("Original data-pool base is invalid.");
                }
                let original_section = &reference.sections[target.section];
                if original_section.kind != kind || original_section.flags & 4 != 0 {
                    bail!("Original data-pool base has the wrong section type.");
                }
                if read_only && (original_section.name != ".rodata" || original_section.flags != 2)
                {
                    bail!("Original read-only pool has the wrong section type.");
                }
                let mapping = (target.section, i64::from(target.address) - offset);
                if sections
                    .get(&root.section)
                    .is_some_and(|known| *known != mapping)
                {
                    bail!("Compiled functions disagree on their data-pool base.");
                }
                sections.insert(root.section, mapping);
            }
            if let Some(name) = unmatched.filter(|_| !sections.contains_key(&root.section)) {
                bail!(
                    "Data-pool reference has no unique original base: {name} ({}, no site matched)",
                    root.name
                );
            }
        }
        Ok(sections)
    }

    fn site_data_bases(&self, primary: &Symbol, mut sections: Sections) -> Result<Sections> {
        let compiled = self.compiled;
        let reference = self.reference;
        for (index, symbol) in compiled.symbols.iter().enumerate() {
            if symbol.kind() != 1
                || symbol.binding() != 0
                || symbol.name.starts_with('@')
                || !valid(compiled, symbol.section)
                || sections.contains_key(&symbol.section)
                || !reference.named(&symbol.name).is_empty()
            {
                continue;
            }
            let source_section = &compiled.sections[symbol.section];
            let source_offset = i64::from(symbol.address) - base_of(compiled, source_section);
            for relocation in &compiled.relocations {
                if relocation.symbol != index
                    || section_of(compiled, relocation.section)?.flags & 4 == 0
                {
                    continue;
                }
                let owners = self.owners(relocation.section, i64::from(relocation.address));
                if owners.len() != 1 || !ASM_LEAF_FUNCTIONS.contains(&owners[0].name.as_str()) {
                    continue;
                }
                let original = self.original_function(&owners[0].name, primary)?;
                let site = i64::from(original.address) + i64::from(relocation.address)
                    - i64::from(owners[0].address);
                let matches: Vec<&Relocation> = reference
                    .relocations
                    .iter()
                    .filter(|item| {
                        item.section == original.section
                            && i64::from(item.address) == site
                            && item.kind == relocation.kind
                    })
                    .collect();
                if matches.len() != 1 {
                    continue;
                }
                let target = symbol_of(reference, matches[0].symbol)?;
                if !valid(reference, target.section) {
                    continue;
                }
                let mapping = (
                    target.section,
                    i64::from(target.address) + i64::from(matches[0].addend)
                        - i64::from(relocation.addend)
                        - source_offset,
                );
                if sections
                    .get(&symbol.section)
                    .is_some_and(|known| *known != mapping)
                {
                    bail!("Compiled functions disagree on their data-pool base.");
                }
                sections.insert(symbol.section, mapping);
            }
        }
        Ok(sections)
    }

    fn shared_owner_target(
        &self,
        symbol: &Symbol,
        owners: &[&Symbol],
        function: &Symbol,
    ) -> Option<Symbol> {
        let mut candidates = BTreeSet::new();
        for owner in owners {
            let original = self.original_function(&owner.name, function).ok()?;
            candidates.insert(self.resolve_symbol(symbol, &original, None, None).ok()?);
        }
        if candidates.len() != 1 {
            return None;
        }
        candidates.into_iter().next()
    }

    fn verify_initialized_data(&self, function: &Symbol) -> Result<Sections> {
        let compiled = self.compiled;
        let reference = self.reference;
        let mut sections = self.site_data_bases(function, self.data_pool_bases(function, 1)?)?;
        let mut owned: BTreeMap<usize, Vec<(i64, i64)>> = BTreeMap::new();
        let objects: Vec<&Symbol> = compiled
            .symbols
            .iter()
            .filter(|symbol| {
                symbol.kind() == 1
                    && symbol.section != 0
                    && !(valid(compiled, symbol.section)
                        && compiled.sections[symbol.section].kind == 8)
                    && !symbol.name.starts_with('@')
            })
            .collect();
        let aliases: Vec<&Symbol> = objects
            .iter()
            .copied()
            .filter(|symbol| {
                symbol.binding() == 0
                    && reference.named(&symbol.name).is_empty()
                    && stem(&symbol.name).is_none()
            })
            .collect();
        let ordered: Vec<&Symbol> = objects
            .iter()
            .copied()
            .filter(|symbol| !aliases.contains(symbol))
            .chain(aliases.iter().copied())
            .collect();
        for symbol in ordered {
            if !valid(compiled, symbol.section) {
                bail!(
                    "Defined game data needs separate verification: {}; the object has no initialized section.",
                    symbol.name
                );
            }
            let mut context = function.clone();
            let mut shared_target = None;
            if stem(&symbol.name).is_some() && symbol.binding() == 0 {
                let owners = self.users(symbol);
                if owners.len() == 1 {
                    context = self.original_function(&owners[0].name, function)?;
                } else if !sections.contains_key(&symbol.section) {
                    shared_target = Some(
                        self.shared_owner_target(symbol, &owners, function)
                            .ok_or_else(|| {
                                anyhow!("Local data has no unique function owner: {}", symbol.name)
                            })?,
                    );
                }
            }
            let pooled = symbol.binding() == 0 && sections.contains_key(&symbol.section);
            let pooled_local = if pooled { stem(&symbol.name) } else { None };
            let target = if aliases.contains(&symbol) || pooled_local.is_some() {
                let Some(&(target_index, base)) = sections.get(&symbol.section) else {
                    bail!(
                        "Local initialized data has no verified pool: {}",
                        symbol.name
                    );
                };
                let source_section = &compiled.sections[symbol.section];
                let source_offset = i64::from(symbol.address) - base_of(compiled, source_section);
                let candidates: Vec<&Symbol> = reference
                    .symbols
                    .iter()
                    .filter(|target| {
                        target.kind() == 1
                            && target.binding() == 0
                            && target.section == target_index
                            && i64::from(target.address) == base + source_offset
                            && target.size == symbol.size
                            && match pooled_local {
                                Some(local) => stem(&target.name) == Some(local),
                                None => {
                                    target.name.starts_with('@')
                                        || dollar_name(&symbol.name).as_deref()
                                            == Some(target.name.as_str())
                                }
                            }
                    })
                    .collect();
                if candidates.len() != 1 {
                    if let Some(local) = pooled_local {
                        if !reference.symbols.iter().any(|target| {
                            target.kind() == 1
                                && target.section == target_index
                                && stem(&target.name) == Some(local)
                        }) {
                            bail!(
                                "Unresolved or ambiguous symbol in {}: {}",
                                context.name,
                                symbol.name
                            );
                        }
                    }
                    bail!(
                        "Local initialized data has no original pool object: {} (expected at {:#x} in section {target_index})",
                        symbol.name,
                        base + source_offset
                    );
                }
                candidates[0].clone()
            } else if let Some(target) = shared_target {
                target
            } else {
                self.resolve_symbol(symbol, &context, None, None)?
            };
            let section = &compiled.sections[symbol.section];
            if !valid(reference, target.section) {
                bail!("Initialized data has no original section: {}", symbol.name);
            }
            let target_section = &reference.sections[target.section];
            if section.kind != 1
                || section.flags & 4 != 0
                || target_section.kind != 1
                || target_section.flags & 4 != 0
                || target.kind() != 1
            {
                bail!(
                    "Defined game data needs separate verification: {}; only initialized data sections are supported.",
                    symbol.name
                );
            }
            if symbol.size == 0 || symbol.size != target.size {
                bail!("Initialized data size differs: {}", symbol.name);
            }
            let offset = i64::from(symbol.address) - base_of(compiled, section);
            let end = offset + i64::from(symbol.size);
            if offset < 0 || end > i64::from(section.size) {
                bail!("Initialized data exceeds its section: {}", symbol.name);
            }
            let mapping = (target.section, i64::from(target.address) - offset);
            if sections
                .get(&symbol.section)
                .is_some_and(|known| *known != mapping)
            {
                bail!("Initialized data objects disagree on their section placement.");
            }
            sections.insert(symbol.section, mapping);
            let owners = owned.entry(symbol.section).or_default();
            if owners
                .iter()
                .any(|&(start, stop)| offset < stop && end > start)
            {
                bail!("Overlapping initialized data objects: {}", symbol.name);
            }
            owners.push((offset, end));
        }
        for (&index, &(target_index, base)) in &sections {
            let section = &compiled.sections[index];
            let target_section = section_of(reference, target_index)?;
            let size = i64::from(section.size);
            let offset = base - i64::from(target_section.address);
            if offset < 0 || size <= 0 || offset + size > i64::from(target_section.size) {
                bail!("Initialized data pool exceeds its original section.");
            }
            let mut actual = compiled.section_data(section)?.to_vec();
            if actual.len() as i64 != size {
                bail!("Initialized data pool is truncated.");
            }
            let mut covered = BTreeSet::new();
            for relocation in &compiled.relocations {
                if relocation.section != index {
                    continue;
                }
                let position = i64::from(relocation.address) - base_of(compiled, section);
                if relocation.kind != 1 {
                    bail!(
                        "Unsupported initialized data relocation: {}",
                        relocation.kind
                    );
                }
                if position.rem_euclid(4) != 0
                    || position < 0
                    || position + 4 > size
                    || covered.contains(&position)
                {
                    bail!("Initialized data relocation overlaps or exceeds its pool.");
                }
                covered.insert(position);
                let source = symbol_of(compiled, relocation.symbol)?;
                let value = if valid(compiled, source.section)
                    && compiled.sections[source.section].flags & 4 != 0
                {
                    let address = i64::from(source.address) + i64::from(relocation.addend);
                    let owners = self.owners(source.section, address);
                    if address.rem_euclid(4) != 0 || owners.len() != 1 {
                        bail!("Initialized data target leaves its compiled functions.");
                    }
                    let target = self.original_function(&owners[0].name, function)?;
                    i64::from(target.address) + address - i64::from(owners[0].address)
                } else {
                    let target = if valid(compiled, source.section)
                        && compiled.sections[source.section].kind == 8
                    {
                        let bss = self.verify_bss_data(function)?;
                        self.resolve_symbol(source, function, Some(&bss), None)?
                    } else {
                        self.resolve_symbol(source, function, Some(&sections), None)?
                    };
                    i64::from(target.address) + i64::from(relocation.addend)
                };
                put32(&mut actual, position as usize, value)?;
            }
            let expected = slice(reference.section_data(target_section)?, offset, size);
            if actual != expected {
                let position = actual
                    .iter()
                    .zip(expected)
                    .position(|(left, right)| left != right)
                    .ok_or_else(|| {
                        anyhow!("Initialized data pool is truncated in the original.")
                    })?;
                bail!(
                    "Initialized data pool: byte mismatch at {:08X}: {:02X} != {:02X}",
                    base + position as i64,
                    actual[position],
                    expected[position]
                );
            }
        }
        Ok(sections)
    }

    fn verify_bss_data(&self, function: &Symbol) -> Result<Sections> {
        let compiled = self.compiled;
        let reference = self.reference;
        let mut sections = self.data_pool_bases(function, 8)?;
        let pool_sections = sections.clone();
        let mut owned: BTreeMap<usize, Vec<(i64, i64)>> = BTreeMap::new();
        let mut targets: BTreeMap<usize, BTreeSet<Symbol>> = BTreeMap::new();
        for symbol in &compiled.symbols {
            if symbol.kind() != 1
                || !valid(compiled, symbol.section)
                || compiled.sections[symbol.section].kind != 8
            {
                continue;
            }
            let section = &compiled.sections[symbol.section];
            let mut context = function.clone();
            let mut target = None;
            let local_name = stem(&symbol.name);
            if let (Some(local), 0) = (local_name, symbol.binding()) {
                let owners = self.users(symbol);
                if let (true, Some(&(target_section, base))) =
                    (owners.is_empty(), pool_sections.get(&symbol.section))
                {
                    let offset = i64::from(symbol.address) - base_of(compiled, section);
                    let candidates: Vec<&Symbol> = reference
                        .symbols
                        .iter()
                        .filter(|item| {
                            item.section == target_section
                                && i64::from(item.address) == base + offset
                                && item.kind() == symbol.kind()
                                && item.info == symbol.info
                                && item.size == symbol.size
                                && stem(&item.name) == Some(local)
                        })
                        .collect();
                    if candidates.len() != 1 {
                        bail!(
                            "Local zero-initialized data has no unique pool object: {}",
                            symbol.name
                        );
                    }
                    target = Some(candidates[0].clone());
                } else if owners.len() != 1 {
                    target = Some(
                        self.shared_owner_target(symbol, &owners, function)
                            .ok_or_else(|| {
                                anyhow!(
                                    "Local zero-initialized data has no unique function owner: {}",
                                    symbol.name
                                )
                            })?,
                    );
                } else {
                    context = self.original_function(&owners[0].name, function)?;
                }
            }
            let target = match target {
                Some(target) => target,
                None => {
                    let named: Vec<Symbol> = reference
                        .named(&symbol.name)
                        .into_iter()
                        .filter(|item| item.section != 0)
                        .cloned()
                        .collect();
                    if symbol.binding() == 0 && local_name.is_none() && unique_places(&named) > 1 {
                        let owners = self.users(symbol);
                        if owners.is_empty() {
                            let candidates = self.local_file_candidates(named);
                            if candidates.len() != 1
                                || reference.relocations.iter().any(|relocation| {
                                    reference.symbols.get(relocation.symbol) == Some(&candidates[0])
                                })
                            {
                                bail!(
                                    "Private zero-initialized data has no function owner: {}",
                                    symbol.name
                                );
                            }
                            candidates[0].clone()
                        } else {
                            let mut candidates = BTreeSet::new();
                            for owner in owners {
                                let original = self.original_function(&owner.name, function)?;
                                candidates
                                    .insert(self.resolve_symbol(symbol, &original, None, None)?);
                            }
                            if candidates.len() != 1 {
                                bail!(
                                    "Compiled functions disagree on private data: {}",
                                    symbol.name
                                );
                            }
                            candidates
                                .into_iter()
                                .next()
                                .unwrap_or_else(|| symbol.clone())
                        }
                    } else {
                        self.resolve_symbol(symbol, &context, None, None)?
                    }
                }
            };
            if !valid(reference, target.section) {
                bail!(
                    "Zero-initialized data has no original section: {}",
                    symbol.name
                );
            }
            let original_section = &reference.sections[target.section];
            if section.flags & 4 != 0
                || original_section.kind != 8
                || section.flags != original_section.flags
                || section.name != original_section.name
                || symbol.info != target.info
            {
                bail!(
                    "Zero-initialized data type or binding differs: {}",
                    symbol.name
                );
            }
            if symbol.size == 0 || symbol.size != target.size {
                bail!("Zero-initialized data size differs: {}", symbol.name);
            }
            let offset = i64::from(symbol.address) - base_of(compiled, section);
            let end = offset + i64::from(symbol.size);
            if offset < 0 || end > i64::from(section.size) {
                bail!("Zero-initialized data exceeds its section: {}", symbol.name);
            }
            let mapping = (target.section, i64::from(target.address) - offset);
            if sections
                .get(&symbol.section)
                .is_some_and(|known| *known != mapping)
            {
                bail!("Zero-initialized data objects disagree on their section placement.");
            }
            sections.insert(symbol.section, mapping);
            let owners = owned.entry(symbol.section).or_default();
            if owners
                .iter()
                .any(|&(start, stop)| offset < stop && end > start)
            {
                bail!("Overlapping zero-initialized data objects: {}", symbol.name);
            }
            owners.push((offset, end));
            targets.entry(symbol.section).or_default().insert(target);
        }
        for (&index, &(target_index, base)) in &sections {
            let section = &compiled.sections[index];
            let original_section = section_of(reference, target_index)?;
            let size = i64::from(section.size);
            let offset = base - i64::from(original_section.address);
            if offset < 0
                || size <= 0
                || offset + size > i64::from(original_section.size)
                || base.rem_euclid(i64::from(section.alignment.max(1))) != 0
            {
                bail!("Zero-initialized data pool exceeds its original section or alignment.");
            }
            if compiled
                .relocations
                .iter()
                .any(|relocation| relocation.section == index)
            {
                bail!("Zero-initialized data cannot contain relocations.");
            }
            let originals: BTreeSet<Symbol> = reference
                .symbols
                .iter()
                .filter(|symbol| {
                    symbol.kind() == 1
                        && symbol.size != 0
                        && symbol.section == target_index
                        && i64::from(symbol.address) < base + size
                        && base < i64::from(symbol.address) + i64::from(symbol.size)
                })
                .cloned()
                .collect();
            if targets.get(&index).unwrap_or(&BTreeSet::new()) != &originals {
                bail!("Zero-initialized data pool does not cover its original objects exactly.");
            }
        }
        if compiled
            .sections
            .iter()
            .enumerate()
            .any(|(index, section)| {
                section.kind == 8 && section.size != 0 && !sections.contains_key(&index)
            })
        {
            bail!("Zero-initialized data section has no verified original placement.");
        }
        Ok(sections)
    }

    fn relocate(&self, function: &Symbol) -> Result<Vec<u8>> {
        let compiled = self.compiled;
        let reference = self.reference;
        let mut data_sections = self.verify_initialized_data(function)?;
        data_sections.extend(self.verify_bss_data(function)?);
        let source = self.source(function)?;
        let mut output = compiled.symbol_data(source)?.to_vec();
        if self.placement == i64::from(function.address) && output.len() != function.size as usize {
            bail!(
                "{}: generated {} bytes; expected {}.",
                function.name,
                output.len(),
                function.size
            );
        }
        for relocation in &compiled.relocations {
            if relocation.section != source.section {
                continue;
            }
            if !within(source, relocation) {
                if self
                    .owners(relocation.section, i64::from(relocation.address))
                    .len()
                    != 1
                {
                    bail!("Relocation lies outside the compiled functions.");
                }
                continue;
            }
            let offset = (relocation.address - source.address) as usize;
            let target = self.resolve_symbol(
                symbol_of(compiled, relocation.symbol)?,
                function,
                Some(&data_sections),
                Some(offset as i64),
            )?;
            let value = i64::from(target.address) + i64::from(relocation.addend);
            let word_offset = offset & !3;
            let word = get32(&output, word_offset)?;
            match relocation.kind {
                10 => {
                    let displacement = value - (self.placement + word_offset as i64);
                    if displacement.rem_euclid(4) != 0
                        || !(-(1 << 25)..1 << 25).contains(&displacement)
                    {
                        bail!("PowerPC branch exceeds its signed range.");
                    }
                    let field = (displacement & 0x03FF_FFFC) as u32;
                    put32(
                        &mut output,
                        word_offset,
                        i64::from((word & 0xFC00_0003) | field),
                    )?;
                }
                109 => {
                    let section = section_of(reference, target.section)?.name.as_str();
                    let (base, register) = match section {
                        ".sdata2" | ".sbss2" => ("_SDA2_BASE_", 2u32),
                        ".sdata" | ".sbss" => ("_SDA_BASE_", 13u32),
                        _ => bail!("SDA relocation refers to {section}."),
                    };
                    let anchor = reference
                        .named(base)
                        .first()
                        .map(|symbol| i64::from(symbol.address))
                        .ok_or_else(|| anyhow!("The original has no {base} symbol."))?;
                    let displacement = value - anchor;
                    if !(-32768..32768).contains(&displacement) {
                        bail!("SDA relocation exceeds its signed range.");
                    }
                    let field = (displacement & 0xFFFF) as u32;
                    put32(
                        &mut output,
                        word_offset,
                        i64::from((word & 0xFFE0_0000) | (register << 16) | field),
                    )?;
                }
                4..=6 => {
                    let half = match relocation.kind {
                        4 => value,
                        5 => value >> 16,
                        _ => (value + 0x8000) >> 16,
                    };
                    output
                        .get_mut(offset..offset + 2)
                        .ok_or_else(|| anyhow!("Relocation leaves its function."))?
                        .copy_from_slice(&(half as u16).to_be_bytes());
                }
                1 => put32(&mut output, offset, value)?,
                kind => bail!("Unsupported PowerPC relocation: {kind}"),
            }
        }
        Ok(output)
    }
}

pub fn relocate(compiled: &Elf, reference: &Elf, function: &Symbol) -> Result<Vec<u8>> {
    relocate_at(compiled, reference, function, function.address)
}

pub fn relocate_at(
    compiled: &Elf,
    reference: &Elf,
    function: &Symbol,
    address: u32,
) -> Result<Vec<u8>> {
    Link {
        compiled,
        reference,
        placement: i64::from(address),
        files: OnceCell::new(),
        referenced: RefCell::new(HashMap::new()),
    }
    .relocate(function)
}
