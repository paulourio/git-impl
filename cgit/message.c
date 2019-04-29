#include "message.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "global.h"

#define BUF_SIZE 1024


void message_read(char **outmsg, size_t *outsize)
{
	char buffer[BUF_SIZE];
	size_t msg_size = 1;
	char *msg;

	msg = xmalloc(BUF_SIZE);
	*msg = 0;

	while (fgets(buffer, BUF_SIZE, stdin)) {
		msg_size += strlen(buffer);
		msg = xrealloc(msg, msg_size);
		strcat(msg, buffer);
	}

	if (ferror(stdin))
    		die("Error reading from stdin.");

    	*outmsg = msg;
    	*outsize = msg_size;
}
