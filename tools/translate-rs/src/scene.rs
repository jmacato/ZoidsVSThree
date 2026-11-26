use crate::hsd::Archive;
use anyhow::{anyhow, bail, Result};

pub type Vec3 = [f64; 3];
pub type Mat3 = [[f64; 3]; 3];
pub type Mat4 = [[f64; 4]; 4];

#[derive(Clone, Debug, PartialEq)]
pub struct Camera {
    pub projection: u16,
    pub viewport: [u16; 4],
    pub eye: Vec3,
    pub interest: Vec3,
    pub roll: f64,
    pub up: Vec3,
    pub near: f64,
    pub far: f64,
    pub fovy: f64,
    pub aspect: f64,
}

pub fn dot(a: Vec3, b: Vec3) -> f64 {
    a[0] * b[0] + a[1] * b[1] + a[2] * b[2]
}

fn cross(a: Vec3, b: Vec3) -> Vec3 {
    [
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0],
    ]
}

fn normalized(v: Vec3) -> Vec3 {
    let norm = dot(v, v).sqrt();
    v.map(|x| x / norm)
}

pub fn matmul<const R: usize, const K: usize, const C: usize>(
    a: &[[f64; K]; R],
    b: &[[f64; C]; K],
) -> [[f64; C]; R] {
    let mut out = [[0.0; C]; R];
    for (i, row) in out.iter_mut().enumerate() {
        for (j, cell) in row.iter_mut().enumerate() {
            let mut sum = a[i][0] * b[0][j];
            for k in 1..K {
                sum += a[i][k] * b[k][j];
            }
            *cell = sum;
        }
    }
    out
}

pub fn transform(m: &Mat4, v: Vec3) -> Vec3 {
    let mut out = [0.0; 3];
    for (i, cell) in out.iter_mut().enumerate() {
        *cell = m[i][0] * v[0] + m[i][1] * v[1] + m[i][2] * v[2] + m[i][3];
    }
    out
}

pub fn linear(m: &Mat4) -> Mat3 {
    let mut out = [[0.0; 3]; 3];
    for (i, row) in out.iter_mut().enumerate() {
        row.copy_from_slice(&m[i][..3]);
    }
    out
}

pub fn translation(m: &Mat4) -> Vec3 {
    [m[0][3], m[1][3], m[2][3]]
}

/// LAPACK gesv: LU with partial pivoting, then one solve per right-hand side.
pub fn solve<const N: usize, const M: usize>(
    mut a: [[f64; N]; N],
    mut b: [[f64; M]; N],
) -> Result<[[f64; M]; N]> {
    for j in 0..N {
        let mut pivot = j;
        for i in j + 1..N {
            if a[i][j].abs() > a[pivot][j].abs() {
                pivot = i;
            }
        }
        if a[pivot][j] == 0.0 {
            bail!("singular matrix");
        }
        a.swap(j, pivot);
        b.swap(j, pivot);
        let reciprocal = 1.0 / a[j][j];
        let upper = a[j];
        for row in a.iter_mut().skip(j + 1) {
            row[j] *= reciprocal;
            for k in j + 1..N {
                row[k] -= row[j] * upper[k];
            }
        }
    }
    for column in 0..M {
        let mut x: [f64; N] = std::array::from_fn(|i| b[i][column]);
        for k in 0..N {
            if x[k] != 0.0 {
                for i in k + 1..N {
                    x[i] -= x[k] * a[i][k];
                }
            }
        }
        for k in (0..N).rev() {
            if x[k] != 0.0 {
                x[k] /= a[k][k];
                for i in 0..k {
                    x[i] -= x[k] * a[i][k];
                }
            }
        }
        for (row, value) in b.iter_mut().zip(x) {
            row[column] = value;
        }
    }
    Ok(b)
}

pub fn inverse(m: &Mat4) -> Result<Mat4> {
    let mut identity = [[0.0; 4]; 4];
    for (i, row) in identity.iter_mut().enumerate() {
        row[i] = 1.0;
    }
    solve(*m, identity)
}

pub fn project(camera: &Camera, point: Vec3, width: f64, height: f64) -> (f64, f64) {
    let eye = camera.eye;
    let look = normalized([
        eye[0] - camera.interest[0],
        eye[1] - camera.interest[1],
        eye[2] - camera.interest[2],
    ]);
    let right = normalized(cross(camera.up, look));
    let up = cross(look, right);
    let p = [point[0] - eye[0], point[1] - eye[1], point[2] - eye[2]];
    let (x, y, z) = (dot(p, right), dot(p, up), dot(p, look));
    let cot = 1.0 / (camera.fovy * (std::f64::consts::PI / 180.0) / 2.0).tan();
    let ndc_x = cot / camera.aspect * x / -z;
    let ndc_y = cot * y / -z;
    ((ndc_x + 1.0) / 2.0 * width, (1.0 - ndc_y) / 2.0 * height)
}

pub struct Scene {
    pub archive: Archive,
    pub root: usize,
}

impl Scene {
    pub fn new(data: Vec<u8>) -> Result<Self> {
        let archive = Archive::new(data)?;
        let root = archive.word(archive.data_size + archive.reloc_count * 4)? as usize;
        Ok(Self { archive, root })
    }

    pub fn word(&self, offset: usize) -> Result<u32> {
        self.archive.word(offset)
    }

    pub fn ptr(&self, offset: usize) -> Result<Option<usize>> {
        self.archive.pointer(offset)
    }

    fn follow(&self, offset: usize) -> Result<usize> {
        self.ptr(offset)?
            .ok_or_else(|| anyhow!("no pointer at {offset:#x}"))
    }

    pub fn floats(&self, offset: usize, count: usize) -> Result<Vec<f64>> {
        Ok(self
            .archive
            .bytes(offset, count * 4)?
            .as_chunks::<4>()
            .0
            .iter()
            .map(|raw| f64::from(f32::from_be_bytes([raw[0], raw[1], raw[2], raw[3]])))
            .collect())
    }

    fn vec3(&self, offset: usize) -> Result<Vec3> {
        let v = self.floats(offset, 3)?;
        Ok([v[0], v[1], v[2]])
    }

    pub fn model(&self, index: usize) -> Result<usize> {
        let models = self.follow(self.root)?;
        let model = self.follow(models + index * 4)?;
        self.follow(model)
    }

    pub fn local(&self, joint: usize) -> Result<Mat4> {
        let r = self.vec3(joint + 0x14)?;
        let s = self.vec3(joint + 0x20)?;
        let t = self.vec3(joint + 0x2C)?;
        let (cx, sx) = (r[0].cos(), r[0].sin());
        let (cy, sy) = (r[1].cos(), r[1].sin());
        let (cz, sz) = (r[2].cos(), r[2].sin());
        let rot_x = [[1.0, 0.0, 0.0], [0.0, cx, -sx], [0.0, sx, cx]];
        let rot_y = [[cy, 0.0, sy], [0.0, 1.0, 0.0], [-sy, 0.0, cy]];
        let rot_z = [[cz, -sz, 0.0], [sz, cz, 0.0], [0.0, 0.0, 1.0]];
        let scale = [[s[0], 0.0, 0.0], [0.0, s[1], 0.0], [0.0, 0.0, s[2]]];
        let rotation = matmul(&matmul(&matmul(&rot_z, &rot_y), &rot_x), &scale);
        let mut m = [[0.0; 4]; 4];
        for i in 0..3 {
            m[i][..3].copy_from_slice(&rotation[i]);
            m[i][3] = t[i];
        }
        m[3][3] = 1.0;
        Ok(m)
    }

    /// The joint reached by `path` under a model and its world matrix; negative steps are skipped.
    pub fn world(&self, model: usize, path: &[i32]) -> Result<(usize, Mat4)> {
        let mut parent = [[0.0; 4]; 4];
        for (i, row) in parent.iter_mut().enumerate() {
            row[i] = 1.0;
        }
        let mut joint = self.model(model)?;
        for (depth, &count) in path.iter().filter(|&&step| step >= 0).enumerate() {
            if depth > 0 {
                parent = matmul(&parent, &self.local(joint)?);
                joint = self.follow(joint + 0x08)?;
            }
            for _ in 0..count {
                joint = self.follow(joint + 0x0C)?;
            }
        }
        Ok((joint, matmul(&parent, &self.local(joint)?)))
    }

    pub fn position(&self, model: usize, path: &[i32]) -> Result<Vec3> {
        Ok(translation(&self.world(model, path)?.1))
    }

    pub fn camera(&self) -> Result<Camera> {
        let cameras = self.follow(self.root + 4)?;
        let desc = self.follow(cameras)?;
        let projection = self.archive.half(desc + 6)?;
        let mut viewport = [0; 4];
        for (i, value) in viewport.iter_mut().enumerate() {
            *value = self.archive.half(desc + 8 + i * 2)?;
        }
        let eye = self.vec3(self.follow(desc + 0x18)? + 4)?;
        let interest = self.vec3(self.follow(desc + 0x1C)? + 4)?;
        let roll = self.floats(desc + 0x20, 1)?[0];
        let lens = self.floats(desc + 0x28, 4)?;
        let up = match self.ptr(desc + 0x24)? {
            Some(up) => self.vec3(up)?,
            None => [0.0, 1.0, 0.0],
        };
        Ok(Camera {
            projection,
            viewport,
            eye,
            interest,
            roll,
            up,
            near: lens[0],
            far: lens[1],
            fovy: lens[2],
            aspect: lens[3],
        })
    }
}
