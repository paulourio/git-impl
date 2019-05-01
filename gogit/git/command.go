package git

import "bufio"
import "fmt"
import "io/ioutil"
import "os"
import "path"
import "path/filepath"
import "time"

func Command(args []string) {
	command := args[1]
	if command == "init" {
		root_path, _ := filepath.Abs(os.Args[2])
		git_path := path.Join(root_path, ".git")
		for _, dir := range [3]string{"objects", "refs"} {
			new_path := path.Join(git_path, dir)
			merr := os.MkdirAll(new_path, os.ModePerm)
			check(merr)
		}
		fmt.Println("Initialized empty git repository in", git_path)
	} else if command == "commit" {
		root_path, _ := os.Getwd()
		git_path := path.Join(root_path, ".git")
		db_path := path.Join(git_path, "objects")

		ws := Workspace{root_path}
		database := new(Database).Init(db_path)
		entries := []Entry{}
		for _, path := range ws.ListFiles() {
			content := ws.ReadFile(path)
			blob := new(Blob).Init(content)
			fmt.Println(path)
			database.Store(blob)
			entries = append(entries, Entry{path, blob.Id()})
		}

		tree := new(Tree).Init(entries)
		database.Store(tree)
		fmt.Println(tree.Id())

		name := os.Getenv("GIT_AUTHOR_NAME")
		email := os.Getenv("GIT_AUTHOR_EMAIL")
		author := Author{name, email, time.Now()}

		reader := bufio.NewReader(os.Stdin)
		message, _ := reader.ReadString('\n')

		commit := new(Commit).Init(tree.Id(), author, message)
		database.Store(commit)

		hex := fmt.Sprintf("%x", commit.Id())
		err := ioutil.WriteFile(path.Join(git_path, "HEAD"), []byte(hex), 0644)
		check(err)

		fmt.Printf("[(root-commit) %x] %s\n", commit.Id(), message)
	} else {
		fmt.Printf("git: '%s' is not a git command.\n", command)
		panic(1)
	}
}
