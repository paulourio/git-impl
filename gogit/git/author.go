package git

import "fmt"
import "time"

type Author struct {
	name   string
	email  string
	tstamp time.Time
}

func (author Author) String() string {
	return fmt.Sprintf("%s <%s> %s", author.name, author.email,
		author.tstamp.Format("1257894000 +0300"))
}
