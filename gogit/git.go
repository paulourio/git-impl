package main

import "os"

import "./git"

func main() {
	git.Command(os.Args)
}
