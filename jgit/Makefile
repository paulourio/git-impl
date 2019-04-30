
JAVA_FILES = GitInterface.java \
	com/git/Author.java \
	com/git/Blob.java \
	com/git/Commit.java \
	com/git/Database.java \
	com/git/Entry.java \
	com/git/Git.java \
	com/git/Tree.java \
	com/git/Workspace.java \
	com/git/base/Object.java

CLASS_FILES = $(JAVA_FILES:.java=.class)

.PHONY: init commit

git:
	javac $(JAVA_FILES)

init: git
	java -classpath . GitInterface init .

commit: git
	java -classpath . GitInterface commit
