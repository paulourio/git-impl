#ifndef _COMMIT_H_
#define _COMMIT_H_

#include <stddef.h>

static const char *commit_type = "commit";


extern void commit_to_buffer(const unsigned char *sha1, const char *author,
			     const char *email, const char *message,
			     void **bufout, size_t *bufsize);

#endif  /* _COMMIT_H_ */
