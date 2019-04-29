#include <errno.h>
#include <linux/limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <openssl/sha.h>
#include <zlib.h>

#include "blob.h"
#include "global.h"
#include "path.h"
#include "sha1.h"


void write_object(const unsigned char *sha1, void *buffer, size_t size)
{
	const char *hex = sha1_to_hex(sha1);
	char dname[3];
	char fname[39];
	char tmpfile[PATH_MAX];
	char *path;  // points to global memory.
	FILE *fp;
	z_stream stream;
	int ret;
	int fd;
	uLong compressed_size;
	void *compressed;

	strncpy(dname, hex, 2);
	dname[2] = 0;
	strcpy(fname, hex + 2);

	path = mkpath(".git/objects/%s", dname);
	if (!path_exists(path))
		mkdir(path, S_IRWXU);

	path = mkpath(".git/objects/%s/%s", dname, fname);

	/* allocate deflate state */
	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;
	stream.opaque = Z_NULL;
	ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
	if (ret != Z_OK)
		die("could not compress to write");

	compressed_size = deflateBound(&stream, size);
	compressed = xmalloc(compressed_size);

	/* Compress it */
	stream.next_out = compressed;
	stream.avail_out = compressed_size;

	/* First header.. */
	stream.next_in = buffer;
	stream.avail_in = size;
	while (deflate(&stream, Z_FINISH) == Z_OK)
		/* nothing */;
	deflateEnd(&stream);
	compressed_size = stream.total_out;

	snprintf(tmpfile, sizeof(tmpfile), ".git/tmp_obj_XXXXXX");
	fd = mkstemp(tmpfile);
	if (fd < 0)
		die("unable to create temporary sha1 filename %s: %s",
		    tmpfile, strerror(errno));

	fp = fopen(tmpfile, "w");
	if (fp == NULL)
		die("fopen: unable to write object");
	if (fwrite(compressed, (size_t)compressed_size, 1, fp) != 1)
		die("fwrite: unable to write object");
	fclose(fp);
	chmod(path, 0444);
	free(compressed);

	fd = rename(tmpfile, path);
	if (fd != 0)
		die("error renaming temporary file to %s", path);
}


unsigned char *database_store(const char *type, void *buffer, size_t size)
{
	static unsigned char sha1[20];
	char header[32];
	size_t header_len;
	size_t total_len;
	void *wbuf;

	snprintf(header, sizeof(header), "%s %zu", type, size);

	SHA1((unsigned char *)buffer, size, sha1);
	header_len = strlen(header);

	total_len = header_len + 1 + size;

	wbuf = xmalloc(total_len);
	memcpy(wbuf, header, header_len + 1);
	memcpy(header_len + 1 + wbuf, buffer, size);
	write_object(sha1, wbuf, total_len);
	free(wbuf);
	return sha1;
}


void database_store_blob(const char *type, struct blob *blob)
{
	// We are computing SHA1 twice for each blob.
	SHA1((unsigned char *)blob->buffer, blob->size, blob->sha1);
	database_store(type, blob->buffer, blob->size);
}
