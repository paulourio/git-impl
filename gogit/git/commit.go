package git

import "bytes"
import "fmt"

type Commit struct {
	oid     []byte
	tree    []byte
	author  Author
	message string
}

func (commit *Commit) Init(tree []byte, author Author, msg string) *Commit {
	commit.tree = tree
	commit.author = author
	commit.message = msg
	return commit
}

func (commit Commit) Type() string {
	return "commit"
}

func (commit Commit) Data() []byte {
	var buf bytes.Buffer
	buf.WriteString(fmt.Sprintf("tree %x\n", commit.tree))
	buf.WriteString(fmt.Sprintf("author %s\n", commit.author.String()))
	buf.WriteString(fmt.Sprintf("committer %s\n", commit.author.String()))
	buf.WriteString("\n")
	buf.WriteString(commit.message)
	return buf.Bytes()
}

func (commit Commit) Id() []byte {
	return commit.oid
}

func (commit *Commit) SetId(oid []byte) {
	commit.oid = oid
}
