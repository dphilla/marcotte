use std::io;
use std::path::Path;
use std::ffi::CString;
use std::os::raw::{c_char, c_int, c_void};
use std::sync::Once;
use std::cell::UnsafeCell;
use std::path::PathBuf;
use wasm_vfs::{Process, FileSystem, File};

static mut FILESYSTEM: Option<UnsafeCell<FileSystem>> = None;
static mut PROCESS: Option<UnsafeCell<Process>> = None;
static INIT: Once = Once::new();

pub fn initialize_globals() {
    INIT.call_once(|| {
        unsafe {
            FILESYSTEM = Some(UnsafeCell::new(FileSystem::new()));
            PROCESS = Some(UnsafeCell::new(Process::new()));
        }
    });
}


type size_t  = usize;
type ssize_t  = isize;

// TODO - maybe use this first? for fs open gen step
// opens a file or device and returns a file descriptor
#[cfg_attr(target_arch = "wasm32", export_name = "open")] // can add apply to all as needed
#[no_mangle]
pub extern "C" fn open(path: *const c_char, oflag: c_int, mode: c_int) -> c_int {
  // function body for --full open syscall

    let inode;
    let cstr = unsafe { CString::from_raw(path as *mut c_char) };
    let path_buf = PathBuf::from(cstr.to_str().expect("Failed to convert CString to str"));

    {
        let fs = unsafe { &mut *FILESYSTEM.as_ref().unwrap().get() };
        inode = fs.lookup_inode(&path_buf).expect("Failed to find the inode for the given path");
    }


    let fd;
    {
        let process = unsafe { &mut *PROCESS.as_ref().unwrap().get() };
        fd = process.open(unsafe { &mut *FILESYSTEM.as_ref().unwrap().get() }, inode).expect("Failed to open the file");
    }
    return fd as c_int;

}

// reads data from a file descriptor into a buffer
// writes data from a buffer to a file descriptor
pub extern "C" fn write(fd: c_int, buf: *const c_void, count: size_t) -> ssize_t {
    let process = unsafe { &mut *PROCESS.as_ref().unwrap().get() };
    let bytes_to_write = unsafe { std::slice::from_raw_parts(buf as *const u8, count as usize) };
    process.write(fd as i32, bytes_to_write).unwrap() as ssize_t

}

// closes a file descriptor
pub extern "C" fn close(fd: c_int) -> c_int {
    let process = unsafe { &mut *PROCESS.as_ref().unwrap().get() };
    process.close(fd as i32).unwrap()

}

use std::sync::{Arc, Mutex};
pub trait FileOps {
    #[cfg(target_arch = "wasm32")]
    fn open(path: &String) -> std::io::Result<Self>
    where
        Self: Sized;

    #[cfg(target_arch = "wasm32")]
    fn close(&self) -> std::io::Result<()>;

    #[cfg(target_arch = "wasm32")]
    fn read(&mut self, buf: &mut [u8]) -> std::io::Result<usize>;

    #[cfg(target_arch = "wasm32")]
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize>;

    #[cfg(target_arch = "wasm32")]
    fn read_to_string(&mut self) -> std::io::Result<String>;
}

impl FileOps for wasm_vfs::File {
    #[cfg(target_arch = "wasm32")]
    fn open(_path: &String) -> std::io::Result<Self> {
        let inode;
        let path_buf = PathBuf::from(_path);
        {
            let fs = unsafe { &mut *FILESYSTEM.as_ref().unwrap().get() };
            inode = fs.lookup_inode(&path_buf).expect("Failed to find the inode for the given path");
        }
        let fd;
        {
            let process = unsafe { &mut *PROCESS.as_ref().unwrap().get() };
            fd = process.open(unsafe { &mut *FILESYSTEM.as_ref().unwrap().get() }, inode).expect("Failed to open the file");
        }
        let data = Mutex::new(Vec::new());
        let file = Self { data: data, inode: inode, position: 0,  path: path_buf };

        Ok(file)
    }

    #[cfg(target_arch = "wasm32")]
    fn close(&self) -> std::io::Result<()> {
        // no action needed for a File to be closed
        Ok(())
    }

    #[cfg(target_arch = "wasm32")]
    fn read(&mut self, buf: &mut [u8]) -> std::io::Result<usize> {
        let mut file_data = self.data.lock().unwrap();

        //let mut file_data = file_data1.clone();

        //let bytes_to_read = std::cmp::min(buf.len(), (file_data.len() - self.position as usize));
        //buf[..bytes_to_read].copy_from_slice(&file_data[self.position as usize..(self.position + bytes_to_read as u64) as usize]);

        //buf.len();
        //file_data[0];

        let bytes_to_read = file_data.len();
        for i in 0..file_data.len() {
            buf[i] = file_data[i];
        }

        self.position += bytes_to_read as u64;
        Ok(bytes_to_read)
    }

    #[cfg(target_arch = "wasm32")]
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
        let mut file_data = self.data.lock().unwrap();
        let new_size = std::cmp::max(file_data.len(), buf.len());
        file_data.resize(new_size, 0);
        file_data[self.position as usize..self.position as usize + buf.len()]
            .copy_from_slice(buf);
        self.position += buf.len() as u64;
        Ok(buf.len())
    }

    #[cfg(target_arch = "wasm32")]
    fn read_to_string(&mut self) -> std::io::Result<String> {
        //let mut contents = Vec::new();
        //const size = self.position;
        let mut contents = [0; 100]; // Create a buffer of zeros
        self.read(&mut contents)?;

        Ok(String::from_utf8(contents.to_vec()).unwrap())
    }
}


