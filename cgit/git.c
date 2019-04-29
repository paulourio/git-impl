#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <openssl/sha.h>

#include "blob.h"
#include "commit.h"
#include "database.h"
#include "global.h"
#include "message.h"
#include "path.h"
#include "sha1.h"
#include "tree.h"
#include "workspace.h"


static void init_command(int argc, const char **argv)
{
	char resolved_path[PATH_MAX];
	char git_path[PATH_MAX];
	char path[PATH_MAX];
	char *dirnames[2] = {"objects", "refs"};

	if (argc != 3)
		die("a single path name is required");

	if (realpath(argv[2], resolved_path) == NULL)
		die("could not resolve init path");

	strcpy(git_path, resolved_path);
	strcat(git_path, "/.git");

	if (strcpy(path, git_path) == NULL)
		die("could not copy init path");

	size_t len = strlen(path);
	size_t object_len;
	unsigned long i;

	for (i = 0; i < ARRAY_SIZE(dirnames); ++i) {
		object_len = strlen(dirnames[i]);
		if (len + object_len + 1 >= PATH_MAX)
			die("path name too large");
		path[len] = '/';
		path[len + 1] = '\0';
		strncat(path, dirnames[i], PATH_MAX - len - 1);
		if (mkdir_p(path) != 0)
			die("could not create init dirs");
	}
	printf("Initialized empty git repository in %s\n", git_path);
	exit(EXIT_SUCCESS);
}


static void commit_command()
{
	unsigned char sha1[20];
	unsigned i;
	struct workspace ws;
	struct blob blob;
	struct tree tree;
	void *tree_buffer;
	size_t tree_size;
	void *commit_buffer;
	size_t commit_size;
	char *author;
	char *email;
	char *message;
	size_t message_len;
	unsigned char *commit_sha1;
	char *commit_hex;
	FILE *fp;

	tree_init(&tree);
	workspace_list_files(&ws, ".");
	for (i = 0; i < ws.nfiles; i++) {
	 	workspace_read_file(&ws, i, &blob);
	 	database_store_blob(blob_type, &blob);
	 	tree_add_entry(&tree, blob.name, blob.sha1);
	 	/* Free buffer allocated inside read_file. */
	 	free(blob.buffer);
	}

	tree_sort_entries(&tree);
	tree_to_buffer(&tree, &tree_buffer, &tree_size);
	database_store(tree_type, tree_buffer, tree_size);

	author = getenv("GIT_AUTHOR_NAME");
	email = getenv("GIT_AUTHOR_EMAIL");
	if (author == NULL || email == NULL)
		die("git author and email are not set");
	message_read(&message, &message_len);

	/* Get tree SHA-1 to write to the commit message. */
	SHA1((unsigned char *)tree_buffer, tree_size, sha1);
	commit_to_buffer(sha1, author, email, message,
			 &commit_buffer, &commit_size);
	commit_sha1 = database_store(commit_type, commit_buffer, commit_size);

	commit_hex = sha1_to_hex(commit_sha1);
	fp = fopen(".git/HEAD", "w");
	fwrite(commit_hex, 41, 1, fp);
	fclose(fp);

	printf("[root-commit] %s %s\n", commit_hex, message);

	workspace_free(&ws);
	tree_free(&tree);
	free(tree_buffer);
	free(commit_buffer);
	free(message);
}


int main(int argc, const char **argv)
{
	const char *command = argv[1];


	if (strcmp(command, "init") == 0) {
		init_command(argc, argv);
	} else if (strcmp(command, "commit") == 0) {
		commit_command();
	} else {
	    fprintf(stderr, "git: '%s' is not a git command.\n", command);
	    exit(1);
	}
	return 0;
}
