use std::env;
use std::process;

/// CLI entry point for `marcotte`.
///
/// - No arguments → Prints ASCII art & usage.
/// - `marcotte build <file1.c> <file2.c> ... [-v]` → Builds
///   only the Marcotte libc parts that the top-level includes request,
///   plus the user’s .c files, into a single `output.wasm`.
fn main() -> anyhow::Result<()> {
    let args: Vec<String> = env::args().collect();

    // If no arguments, print ASCII art & usage, then exit
    if args.len() == 1 {
        println!("\n");
        let multiline_str = r#"
       _ __ ___   __ _ _ __ ___ ___ | |_| |_ ___
____  | '_ ` _ \ / _` | '__/ __/ _ \| __| __/ _ \  ____
____  | | | | | | (_| | | | (_| (_) | |_| ||  __/  ____
      |_| |_| |_|\__,_|_|  \___\___/ \__|\__\___|     "#;
        println!("{}", multiline_str);
        println!("\n- Generate System Layers - ");
        println!("\n");

        println!(" marcotte (alias: mct) [args] --[flag]");
        println!("\n");
        println!("\n\n More info at: https://github.com/dphilla/marcotte");
        return Ok(());
    }

    match args[1].as_str() {
        "build" => {
            // Everything after "build" we pass to library function
            let files_and_flags = &args[2..];
            marcotte::build(files_and_flags)?;
        }
        other => {
            eprintln!("Unknown command: '{}'", other);
            std::process::exit(1);
        }
    }

    Ok(())
}

