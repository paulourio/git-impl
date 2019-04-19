extern crate exitcode;

use std::env;
use std::fs;
use std::path::Path;
use std::process;

fn init_command(_path: &String) {
    let path = fs::canonicalize(Path::new(_path)).unwrap();
    let git_path = path.join(".git");

    const DIRNAMES: [&'static str; 2] = ["objects", "refs"];

    for i in 0..2 {
        let dirpath = git_path.join(DIRNAMES[i]);
        fs::create_dir_all(dirpath).unwrap_or_else(
            |err| {
                println!("fatal: {}", err);
                process::exit(1);
            }
        )
    }
    println!("Initialized empty git repository in {}",
             git_path.into_os_string().into_string().unwrap());
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let command: &String = &args[1];

    match command == "init" {
        true => init_command(&args[2]),
        _ => {
            eprintln!("git: '{}' is not a git command.", command);
            process::exit(exitcode::DATAERR);
        }
    }
}
