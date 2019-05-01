package git

import "bytes"
import "compress/zlib"
import "crypto/sha1"
import "fmt"
import "io/ioutil"
import "os"
import "path"

func check(e error) {
	if e != nil {
		panic(e)
	}
}

type Database struct {
	pathname string
}

func (db *Database) Init(pathname string) *Database {
	db.pathname = pathname
	return db
}

func (db Database) Store(obj Object) {
	otype := obj.Type()
	odata := obj.Data()
	olen := len(odata)
	header := fmt.Sprintf("%s %d", otype, olen)
	var buf bytes.Buffer
	buf.WriteString(header)
	buf.WriteByte(0)
	buf.Write(odata)
	content := buf.Bytes()

	hash := sha1.New()
	hash.Write(content)
	sha1 := hash.Sum(nil)

	obj.SetId(sha1)

	db.writeObject(sha1, content)
}

func (db Database) writeObject(oid []byte, content []byte) {
	hex := fmt.Sprintf("%x", oid)
	dir := hex[:2]
	dirname := path.Join(db.pathname, dir)
	fname := path.Join(dirname, hex[2:])
	if _, err := os.Stat(dirname); os.IsNotExist(err) {
		merr := os.MkdirAll(dirname, os.ModePerm)
		check(merr)
	}
	file, err := ioutil.TempFile(dirname, "obj_")
	check(err)

	var compressed bytes.Buffer

	w := zlib.NewWriter(&compressed)
	w.Write(content)
	w.Close()

	err = ioutil.WriteFile(file.Name(), compressed.Bytes(), 0644)
	check(err)

	file.Close()

	err = os.Rename(file.Name(), fname)
	check(err)
}
