use std::fs;
use std::io::{BufRead, BufReader};
use std::process::Command;

use anyhow::{anyhow, Result};
use regex::Regex;
use std::collections::HashSet;
use std::fs::File;

/// Build your C files for Wasm, linking against only the Marcotte libc
/// parts that correspond to the top-level headers the user includes.
///
/// Usage from CLI: `marcotte build file1.c file2.c ... [-v]`
/// Usage from Rust: `marcotte::build(&["file1.c", "file2.c", "-v"])?;`
pub fn build(args: &[impl AsRef<str>]) -> Result<()> {
    // 1. Separate .c files from other flags (like -v)
    let mut c_files = Vec::new();
    let mut keep_makefile = false;

    for arg in args {
        let a = arg.as_ref();
        if a.ends_with(".c") {
            c_files.push(a.to_string());
        } else if a == "-v" || a == "--verbose" {
            keep_makefile = true;
        } else {
            // ignore or handle other flags
        }
    }

    if c_files.is_empty() {
        return Err(anyhow!(
            "No .c files provided! Usage: marcotte build <file(s).c> [-v]"
        ));
    }

    // 2. Figure out which headers are included (top-level) in these user .c files.
    let mut included_headers = HashSet::new();
    for user_c in &c_files {
        let headers = parse_includes_in_file(user_c)?;
        for h in headers {
            included_headers.insert(h);
        }
    }

    // 3. Map those included headers to specific Marcotte libc .c files.
    let needed_libc_sources = headers_to_sources(&included_headers);

    // 4. Generate a Makefile that references only those needed sources + the user’s .c files.
    let out_wasm = "output.wasm";
    let makefile_content = build_makefile_contents(&needed_libc_sources, &c_files, out_wasm);

    let makefile_name = "MarcotteMakefile";
    fs::write(makefile_name, &makefile_content)?;

    // 5. Run `make -f MarcotteMakefile`
    let status = Command::new("make")
        .arg("-f")
        .arg(makefile_name)
        .status()?;

    if !status.success() {
        return Err(anyhow!("Makefile build failed."));
    }

    // 6. Clean up the Makefile if not verbose
    if !keep_makefile {
        let _ = fs::remove_file(makefile_name);
    }

    println!("\n[marcotte] Successfully built: {}\nOutput: {}\n",
        c_files.join(", "),
        out_wasm
    );

    Ok(())
}

/// Parse top-level `#include <...>` or `#include "..."` lines from a given .c file.
/// Returns a set of header filenames (e.g. `stdio.h`, `string.h`).
///
/// We only look at the user’s .c file—NOT nested includes from within those headers.
fn parse_includes_in_file(file_path: &str) -> Result<HashSet<String>> {
    let f = File::open(file_path)
        .map_err(|e| anyhow!("Failed to open {}: {}", file_path, e))?;
    let reader = BufReader::new(f);

    // Regex that captures #include <SOMETHING> or #include "SOMETHING"
    // group 1 = "SOMETHING"
    let re = Regex::new(r#"#\s*include\s*[<"]([^">]+)[">]"#)
        .expect("Failed to compile regex");

    let mut headers = HashSet::new();
    for line in reader.lines() {
        let line = line?;
        if let Some(cap) = re.captures(&line) {
            let h = cap[1].trim().to_string();
            headers.insert(h);
        }
    }
    Ok(headers)
}

/// A manual mapping from standard headers to Marcotte’s `.c` sources.
///
/// Extend or customize this to reflect your actual `builder/` structure.
fn headers_to_sources(headers: &HashSet<String>) -> Vec<String> {
    use std::collections::HashSet;
    let mut result = HashSet::new();

    // Helper closure
    let mut add_sources = |patterns: &[&str]| {
        for p in patterns {
            result.insert(p.to_string());
        }
    };

    for h in headers {
                //TODO - add opt to remove unused code
                    //-ffunction-sections -fdata-sections + -Wl,--gc-sections, or
                    //-flto (Link-Time Optimization).
                add_sources(&["builder/src/stdio/*.c"]);
                add_sources(&["builder/src/string/*.c"]);
                add_sources(&["builder/src/strings/*.c"]);
                add_sources(&["builder/src/stdlib/*.c"]);
                add_sources(&["builder/src/fcntl/*.c"]);
                add_sources(&["builder/src/unistd/*.c"]);
                add_sources(&["builder/src/dirent/*.c"]);
                add_sources(&["builder/src/sys/stat/*.c"]);
                add_sources(&["builder/src/sys/file/*.c"]);
                add_sources(&["builder/src/sys/mman/*.c"]);
                add_sources(&["builder/src/sys/mount/*.c"]);
                add_sources(&["builder/src/sys/mount/*.c"]);
                add_sources(&["builder/src/errno/*.c"]);
                add_sources(&["builder/src/utime/*.c"]);
                add_sources(&["builder/src/network/*.c"]);
                add_sources(&["builder/src/network/arpa/*.c"]);
                // For networking
            // etc.

            // If your code requires always linking in extern_syscall.c or r.c
            // for certain headers, do that here. Or you can always add them.
    }

    // Optionally ALWAYS add extern_syscall.c or r.c if your environment requires them.
    // result.insert("builder/extern_syscall.c".to_string());
    // result.insert("builder/r.c".to_string());

    result.into_iter().collect()
}

/// Creates the Makefile contents.
///
/// We detect the best compiler for the current OS (Windows vs. not).
fn build_makefile_contents(
    needed_libc_sources: &[String],
    user_c_files: &[String],
    out_wasm: &str,
) -> String {
    // Provide a space-separated string of the needed Marcotte .c sources
    let marcotte_c_files = needed_libc_sources.join(" ");

    // Detect compiler (simplistic approach)
    let compiler = detect_compiler();

    // careful with LD flags --allow-undefined doesnt tell whats not defined and just builds!
    format!(
r#"# Auto-generated Makefile for Marcotte (Selective Build)

CC = {cc}
CFLAGS = --target=wasm32 -Ibuilder/include -nostdlib -O3 -w
LDFLAGS = -Wl,--no-entry -Wl,--export-all

all: build

build:
	$(CC) $(CFLAGS) $(LDFLAGS) -o {out_wasm} {marcotte_c_files} {user_files} libwasm_vfs.a

clean:
	rm -f {out_wasm}

"#,
        cc = compiler,
        out_wasm = out_wasm,
        marcotte_c_files = marcotte_c_files,
        user_files = user_c_files.join(" ")
    )
}

/// Basic logic to pick a compiler based on the OS.
///
/// - On Windows, returns `"clang.exe"`
/// - Otherwise, returns `"clang"`
///
/// You can expand this to try `emcc`, check for `clang` in PATH, etc.
fn detect_compiler() -> String {
    if cfg!(target_os = "windows") {
        "clang.exe".to_string()
    } else {
        "clang".to_string()
    }
}

