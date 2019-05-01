package git

import "io/ioutil"
import "os"
import "path/filepath"

type Workspace struct {
	pathname string
}

func (ws Workspace) ListFiles() (files []string) {
	err := filepath.Walk(
		ws.pathname,
		func(path string, info os.FileInfo, err error) error {
			if info.IsDir() && info.Name() == ".git" {
				return filepath.SkipDir
			}
			if !info.IsDir() {
				files = append(files, path)
			}
			return nil
		})

	if err != nil {
		panic(err)
	}
	return
}

func (ws Workspace) ReadFile(path string) (bytes []byte) {
	bytes, err := ioutil.ReadFile(path)
	if err != nil {
		panic(err)
	}
	return
}
