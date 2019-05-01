package git

type Blob struct {
	oid  []byte
	data []byte
}

func (blob *Blob) Init(data []byte) *Blob {
	blob.data = data
	return blob
}

func (blob Blob) Type() string {
	return "blob"
}

func (blob Blob) Data() []byte {
	return blob.data
}

func (blob Blob) Id() []byte {
	return blob.oid
}

func (blob *Blob) SetId(oid []byte) {
	blob.oid = oid
}
