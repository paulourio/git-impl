package git

import "bytes"
import "sort"

type Tree struct {
	oid     []byte
	data    []byte
	entries []Entry
}

func (tree *Tree) Init(entries []Entry) *Tree {
	tree.entries = entries
	return tree
}

func (tree Tree) Type() string {
	return "tree"
}

func (tree Tree) Data() []byte {
	entries := tree.entries
	sort.Slice(entries, func(i, j int) bool {
		return entries[i].name < entries[j].name
	})

	var buf bytes.Buffer
	for _, entry := range entries {
		buf.WriteString("100644 ")
		buf.WriteString(entry.name)
		buf.WriteByte(0)
		buf.Write(entry.oid)
	}
	return buf.Bytes()
}

func (tree Tree) Id() []byte {
	return tree.oid
}

func (tree *Tree) SetId(oid []byte) {
	tree.oid = oid
}
