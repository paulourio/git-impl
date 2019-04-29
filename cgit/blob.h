#ifndef _BLOB_H_
#define _BLOB_H_

#include <stddef.h>
#include <linux/limits.h>

static const char *blob_type = "blob";

struct blob {
	char name[PATH_MAX];
 	void *buffer;
 	size_t size;
 	unsigned char sha1[20];
};

#endif  /* _BLOB_H_ */
