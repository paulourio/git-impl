
CPP_FILES = author.cc command.cc commit.cc database.cc date.cc git.cc \
			tree.cc workspace.cc
OBJECT_FILES = $(CPP_FILES:.cc=.o)
HEADER_FILES = author.hh blob.hh commit.hh database.hh date.hh entry.hh \
			   git.hh object.hh tree.hh workspace.hh

CXX = clang++
CXXFLAGS = -std=c++17 -g
LDFLAGS = -lstdc++fs -lboost_iostreams -lboost_filesystem -lz

.PHONY: init commit clean lint

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $<

git: $(OBJECT_FILES)
	$(CXX) -o git $(OBJECT_FILES) $(LDFLAGS)

init: git
	valgrind -q --leak-check=full ./git init .

commit: git
	valgrind -q --leak-check=full ./git commit

format:
	clang-format -i -style=google $(CPP_FILES) $(HEADER_FILES)

lint:
	clang-tidy -format-style=google $(CPP_FILES) -- -std=c++17
	cppcheck --std=c++14 .
	cpplint --filter=-legal/copyright $(CPP_FILES)

clean:
	$(RM) $(OBJECT_FILES) git
