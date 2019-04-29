
CFILES = commit.c database.c date.c git.c global.c message.c path.c sha1.c \
		 tree.c workspace.c

git: $(CFILES)
	clang -g -Wall -Wextra -std=gnu11 -o git $(CFILES) -lssl -lcrypto -lz

clean:
	$(RM) git
