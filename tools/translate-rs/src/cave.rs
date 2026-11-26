use anyhow::{bail, Result};

pub const SLOT: usize = 2;
pub const ADDRESS: u32 = 0x8039_D6C0;
pub const CAPACITY: usize = 0x4000;
pub const DISC_OFFSET: u64 = 0x1F_9000;
pub const DISC_END: u64 = 0x1F_D000;

#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub struct Cave {
    pub data: Vec<u8>,
}

impl Cave {
    pub fn is_empty(&self) -> bool {
        self.data.is_empty()
    }

    pub fn next(&self) -> u32 {
        ADDRESS + self.data.len() as u32
    }

    pub fn push(&mut self, name: &str, code: &[u8]) -> Result<u32> {
        let address = self.next();
        if !code.len().is_multiple_of(4) {
            bail!("{name}: {} bytes is not whole instructions", code.len());
        }
        if self.data.len() + code.len() > CAPACITY {
            bail!(
                "{name}: {} bytes do not fit the code cave, {} of {CAPACITY} used",
                code.len(),
                self.data.len()
            );
        }
        self.data.extend_from_slice(code);
        Ok(address)
    }

    pub fn section(&self) -> Vec<u8> {
        let mut data = self.data.clone();
        data.resize(data.len().div_ceil(32) * 32, 0);
        data
    }
}

pub fn branch(from: u32, to: u32) -> Result<[u8; 4]> {
    let displacement = i64::from(to) - i64::from(from);
    if displacement.rem_euclid(4) != 0 || !(-(1 << 25)..1 << 25).contains(&displacement) {
        bail!("branch from {from:08X} to {to:08X} exceeds its signed range");
    }
    Ok((0x4800_0000 | (displacement & 0x03FF_FFFC) as u32).to_be_bytes())
}

pub fn branch_target(address: u32, word: u32) -> Option<u32> {
    if word >> 26 != 18 {
        return None;
    }
    let displacement = ((word & 0x03FF_FFFC) << 6) as i32 >> 6;
    Some(if word & 2 != 0 {
        displacement as u32
    } else {
        address.wrapping_add(displacement as u32)
    })
}
