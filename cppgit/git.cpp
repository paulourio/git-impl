#include <filesystem>
#include <string>
#include <stdio.h>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
  using std::string;
  string command(argv[1]);

  if (command == "init") {
    auto path = fs::absolute(argv[2]);
    auto git_path = path /= ".git";

    for (auto dirname : {"objects", "refs"}) {
      fs::create_directories(git_path /= dirname);
    }

    printf("Initialized empty git repository in %s\n", git_path.c_str());
  } else {
    fprintf(stderr, "git: '%s' is not a git command.\n", command.c_str());
    exit(1);
  }
  return 0;
}
