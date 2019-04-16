package main

import "os"
import "fmt"
import "path"
import "path/filepath"

func main() {
	command := os.Args[1]
	if command == "init" {
		root_path, _ := filepath.Abs(os.Args[2])
		git_path := path.Join(root_path, ".git")
		for _, dir := range [3]string{"objects", "refs"} {
			new_path := path.Join(git_path, dir)
		    merr := os.MkdirAll(new_path, os.ModePerm)
		    if merr != nil {
		        panic(merr)
		    }
		}
		fmt.Println("Initialized empty git repository in", git_path)
	} else {
        fmt.Printf("git: '%s' is not a git command.\n", command)
        panic(1)
    }
}
