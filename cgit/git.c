#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <linux/limits.h>
#include <sys/stat.h>

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif


static int mkdir_p(const char *dir)
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


static void init_command(int argc, const char **argv)
{
	char resolved_path[PATH_MAX];
	char git_path[PATH_MAX];
	char path[PATH_MAX];
	char *dirnames[2] = {"objects", "refs"};
	char err_msg[255];

	if (realpath(argv[2], resolved_path) == NULL){
		strcpy(err_msg, "could not resolve init path");
		goto error;
	}

	strcpy(git_path, resolved_path);
	strcat(git_path, "/.git");

	if (strcpy(path, git_path) == NULL) {
		strcpy(err_msg, "could not copy init path");
		goto error;
	}

	size_t len = strlen(path);
	size_t object_len;

	for (int i = 0; i < sizeof(dirnames) / sizeof(0[dirnames]); ++i) {
		object_len = strlen(dirnames[i]);
		if (len + object_len + 1 >= PATH_MAX) {
			strcpy(err_msg, "path name too large");
			goto error;
		}
		path[len] = '/';
		path[len + 1] = '\0';
		if (strncat(path, dirnames[i], PATH_MAX - len - 1) == NULL) {
			goto error;
		}
		if (mkdir_p(path) != 0) {
			strcpy(err_msg, "could not create init dirs");
			goto error;
		}
	}
	printf("Initialized empty git repository in %s\n", git_path);
	exit(EXIT_SUCCESS);

error:
	fprintf(stderr, "fatal: %s\n", err_msg);
	exit(EXIT_FAILURE);
}


int main(int argc, const char **argv)
{
	const char *command = argv[1];


	if (strcmp(command, "init") == 0) {
		init_command(argc, argv);
	} else {
	    fprintf(stderr, "git: '%s' is not a git command.\n", command);
	    exit(1);
	}
	return 0;
}
