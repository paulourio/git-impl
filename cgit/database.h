#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <stddef.h>

#include "blob.h"

extern unsigned char *database_store(const char *type, void *buffer,
				     size_t size);

extern void database_store_blob(const char *type, struct blob *blob);

#endif  /* _DATABASE_H_ */
