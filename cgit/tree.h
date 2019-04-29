#ifndef _TREE_H_
#define _TREE_H_

#include <stddef.h>
#include <linux/limits.h>

static const char *tree_type = "tree";

struct entry {
	char name[PATH_MAX];
	unsigned char sha1[20];
};

struct tree {
	struct entry *entries;
	size_t nentries;
};

extern void tree_init(struct tree *tree);

extern void tree_add_entry(struct tree *tree, const char *name,
			   const unsigned char *sha1);

extern void tree_sort_entries(struct tree *tree);

extern void tree_to_buffer(struct tree *tree, void **buffer, size_t *bufsize);

extern void tree_free(struct tree *tree);

#endif  /* _TREE_H_ */
