#ifndef _WORKSPACE_H_
#define _WORKSPACE_H_

#include <stddef.h>
#include <linux/limits.h>

#include "blob.h"


struct ws_file {
	char path[PATH_MAX];
};


struct workspace {
	struct ws_file *files;
	char root_path[PATH_MAX];
	char git_path[PATH_MAX];
	size_t nfiles;
};


extern void workspace_list_files(struct workspace *ws, const char *root_path);

extern void workspace_read_file(const struct workspace *ws, unsigned int id,
                                struct blob *contents);

extern const char *workspace_get_path(const struct workspace *ws,
                                      unsigned int id);

extern void workspace_free(struct workspace *ws);

#endif  /* _WORKSPACE_H_ */
