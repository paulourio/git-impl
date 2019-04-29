#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdlib.h>


#define ARRAY_SIZE(arr)	(sizeof(arr) / sizeof(0[arr]))


extern void die(const char *err, ...);


static inline void *xcalloc(size_t nmemb, size_t size)
{
	void *ret = calloc(nmemb, size);
	if (!ret)
		die("Out of memory, calloc failed");
	return ret;
}


static inline void *xmalloc(size_t size)
{
	void *ret = malloc(size);
	if (!ret)
		die("Out of memory, malloc failed");
	return ret;
}


static inline void *xrealloc(void *ptr, size_t size)
{
	void *ret = realloc(ptr, size);
	if (!ret)
		die("Out of memory, realloc failed");
	return ret;
}

#endif  /* _GLOBAL_H_ */
