#ifndef _PATH_H_
#define _PATH_H_

#include <stdbool.h>

extern char *mkpath(const char *fmt, ...);

extern bool path_exists(const char *path);

extern int mkdir_p(const char *dir);

#endif  /* _PATH_H_ */
