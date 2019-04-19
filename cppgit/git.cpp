#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
  using std::string;
  using std::cin, std::cout, std::cerr, std::endl;

  string command(argv[1]);

  if (command == "init") {
    auto path = fs::absolute(argv[2]);
    auto git_path = path /= ".git";

    try {
      for (auto dirname : {"objects", "refs"}) {
        fs::create_directories(git_path /= dirname);
      }

      cerr << "Initialized empty git repository in " << git_path << endl;
    } catch (std::filesystem::filesystem_error& e) {
      cerr << "fatal: " << e.what() << endl;
    }
  } else {
    cerr << "git: '" << command << "' is not a git command." << endl;
    exit(1);
  }
  return 0;
}
