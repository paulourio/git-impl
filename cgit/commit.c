#include "commit.h"

#include <stdio.h>
#include <string.h>

#include "date.h"
#include "global.h"
#include "sha1.h"


void commit_to_buffer(const unsigned char *sha1, const char *author,
		      const char *email, const char *message,
		      void **bufout, size_t *bufsize)
{
	const char *hex = sha1_to_hex(sha1);
	size_t size = strlen(message) + 2048;
	void *buffer = xmalloc(size);
	char tstamp[40];

	datestamp(tstamp, sizeof(tstamp));

	snprintf(buffer, size,
		 "tree %s\nauthor %s <%s> %s\ncommiter %s <%s> %s\n\n%s",
		 hex,
		 author, email, tstamp,
		 author, email, tstamp,
		 message);

	*bufout = buffer;
	*bufsize = strlen(buffer);
}
