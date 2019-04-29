#include "path.h"

#include <errno.h>
#include <linux/limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif


static char pathname[PATH_MAX];
static char bad_path[] = "/bad-path/";


static char *cleanup_path(char *path)
{
	/* Clean it up */
	if (memcmp(path, "./", 2) == 0) {
		path += 2;
		while (*path == '/')
			path++;
	}
	return path;
}


/*
 * Copied from git source code:
 * 	commit 	a3eb250f996bf5e12376ec88622c4ccaabf20ea8
 * 	tag 	v0.99
 * 	date 	Sun Jul 10 15:40:43 2005 -0700
 */
char *mkpath(const char *fmt, ...)
{
	va_list args;
	unsigned len;

	va_start(args, fmt);
	len = vsnprintf(pathname, PATH_MAX, fmt, args);
	va_end(args);
	if (len >= PATH_MAX)
		return bad_path;
	return cleanup_path(pathname);
}


int mkdir_p(const char *dir)
{
	char buffer[PATH_MAX];
	char *p = NULL;
	size_t len;

	snprintf(buffer, sizeof(buffer), "%s", dir);
	len = strlen(buffer);
	if (buffer[len - 1] == PATH_SEPARATOR) {
		buffer[len - 1] = '\0';
	}
	for (p = buffer + 1; *p; ++p) {
		if (*p == PATH_SEPARATOR) {
			*p = '\0';
			if (mkdir(buffer, S_IRWXU) != 0) {
				if (errno != EEXIST)
					return -1;
			}
			*p = PATH_SEPARATOR;
		}
	}
	return mkdir(buffer, S_IRWXU);
}


// Checks if directory exists when path ends with a slash.
bool path_exists(const char *path)
{
	struct stat sb;

	return (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode));
}
