#include <filesystem>
#include <iostream>
#include <string>

#include "./blob.hh"
#include "./database.hh"
#include "./workspace.hh"

namespace fs = std::filesystem;

namespace git {

void command(int argc, const char** argv) {
  using std::cin, std::cout, std::cerr, std::endl;
  using std::string;

  string command(argv[1]);

  if (command == "init") {
    auto path = fs::absolute(argv[2]);
    auto git_path = path / ".git";

    try {
      for (auto dirname : {"objects", "refs"}) {
        fs::create_directories(git_path / dirname);
      }

      cerr << "Initialized empty git repository in " << git_path << endl;
    } catch (std::filesystem::filesystem_error& e) {
      cerr << "fatal: " << e.what() << endl;
    }
  } else if (command == "commit") {
    auto root_path = fs::absolute(".");
    auto git_path = root_path / ".git";
    auto db_path = git_path / "objects";

    auto ws = Workspace(root_path);
    auto database = Database(db_path);
    for (auto& path : ws.ListFiles()) {
      auto content = ws.ReadFile(path);
      auto blob = Blob(content);
      database.Store(blob);
    }

  } else {
    cerr << "git: '" << command << "' is not a git command." << endl;
    exit(1);
  }
}

}  // namespace git
