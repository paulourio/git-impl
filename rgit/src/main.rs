extern crate exitcode;

use std::env;
use std::fs;
use std::path::Path;

fn init_command(_path: &String) {
    let path = fs::canonicalize(Path::new(".")).unwrap();
    let root_path = path.join(_path);
    let git_path = path.join(".git");

    const dirnames: [&'static str; 2] = ["objects", "refs"];

    for i in 0..2 {
        std::fs::create_dir_all(git_path.join(dirnames[i]));
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
            println!("git: '{}' is not a git command.", command);
            std::process::exit(exitcode::DATAERR);
        }
    }
}
