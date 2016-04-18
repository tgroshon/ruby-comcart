extern crate comcart;

use std::io::{Cursor, BufReader};
use std::slice;
use comcart::process;

#[no_mangle]
pub extern "C" fn process_file(ptr: *const u8, len: usize) {
    unsafe {
        let slice: &[u8] = slice::from_raw_parts(ptr, len);
        let cursor = Cursor::new(slice);     // for Seek trait
        let reader = BufReader::new(cursor); // for efficient reading
        let summary = process(reader);
        println!("{:?}", summary.unwrap().modules.last());
    }
}
