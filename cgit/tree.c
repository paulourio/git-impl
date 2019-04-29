#include "tree.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "global.h"


void tree_init(struct tree *tree)
{
	tree->entries = NULL;
	tree->nentries = 0;
}


void tree_add_entry(struct tree *tree, const char *name,
		    const unsigned char *sha1)
{
	struct entry *entry;

	tree->entries = xrealloc(tree->entries,
				 ++tree->nentries * sizeof(struct entry));
	entry = tree->entries + tree->nentries - 1;
	strcpy(entry->name, name);
	memcpy(entry->sha1, sha1, 20);
}


static int compare_entry_name(const void *a, const void *b)
{
	struct entry *lentry = (struct entry *)a;
	struct entry *rentry = (struct entry *)b;

	return strcmp(lentry->name, rentry->name);
}


void tree_sort_entries(struct tree *tree)
{
	if (!tree->entries)
		return;

	qsort(tree->entries, tree->nentries, sizeof(struct entry),
	      compare_entry_name);
}


void tree_to_buffer(struct tree *tree, void **buffer, size_t *bufsize)
{
	size_t size = tree->nentries * 60;
	void *buf = xmalloc(size);
	unsigned int i;
	struct entry *entry;
	size_t offset = 0;
	char header[40];
	size_t header_len;

	for (i = 0; i < tree->nentries; i++) {
		entry = &tree->entries[i];
		header_len = sprintf(header, "100644 %s", entry->name);
		if (size < offset + header_len + 21) {
			size += header_len + 21;
			buf = xrealloc(buf, size);
		}
		strcpy(buf + offset, header);
		memcpy(buf + offset + header_len + 1, entry->sha1, 20);
		offset += header_len + 1 + 20;
	}
	*buffer = buf;
	*bufsize = offset;
}


void tree_free(struct tree *tree)
{
	if (tree->entries) {
		free(tree->entries);
		tree->entries = NULL;
	}
}
