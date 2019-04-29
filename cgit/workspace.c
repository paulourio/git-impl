#include "workspace.h"

#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "global.h"
#include "path.h"


void workspace_list_files(struct workspace *ws, const char *root_path)
{
	DIR *dir_stream;
 	struct dirent *dir;
 	struct ws_file *file;
 	unsigned int nfiles = 0;

 	strcpy(ws->root_path, root_path);
 	strcpy(ws->git_path, mkpath("%s/%s", root_path, ".git"));

	ws->files = NULL;
	ws->nfiles = 0;

	dir_stream = opendir(ws->root_path);

	if (!dir_stream)
		die("directory '%s' does not exist", ws->root_path);

	while ((dir = readdir(dir_stream)) != NULL) {
		if (strstr(dir->d_name, ".c") == NULL &&
		    strstr(dir->d_name, ".h") == NULL)
			continue;

		nfiles++;
		if (!ws->files) {
			ws->files = xmalloc(sizeof(struct ws_file));
		} else {
			ws->files = xrealloc(ws->files,
					     nfiles * sizeof(struct ws_file));
		}
		file = &ws->files[nfiles - 1];
		strncpy(file->path, dir->d_name, PATH_MAX);
	}
	ws->nfiles = nfiles;
	closedir(dir_stream);
}


void workspace_read_file(const struct workspace *ws, unsigned int id,
                         struct blob *contents)
{
	FILE *fp;
	long int len;
	void *buffer;
	const char *path = workspace_get_path(ws, id);

	strcpy(contents->name, path);

	fp = fopen(path, "r");
	if (!fp)
		die("fopen: cannot read %s", path);

	fseek(fp, 0L, SEEK_END);
	len = ftell(fp);
	if (len == -1L)
		die("ftell: cannot read %s", path);

	rewind(fp);

	buffer = xcalloc(1, len + 1);

	if (fread(buffer, len, 1, fp) != 1)
		die("fread: cannot read %s", path);

	contents->buffer = buffer;
	contents->size = (size_t)len;
	fclose(fp);
}


const char *workspace_get_path(const struct workspace *ws, unsigned int id)
{
	return ws->files[id].path;
}


void workspace_free(struct workspace *ws)
{
	if (ws->files) {
		free(ws->files);
		ws->files = NULL;
	}
}
