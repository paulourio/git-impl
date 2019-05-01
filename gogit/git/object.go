package git

type Object interface {
	Type() string
	Data() []byte
	Id() []byte
	SetId(oid []byte)
}
