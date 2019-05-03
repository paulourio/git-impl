#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>
#include <string>

#include "./author.hh"
#include "./blob.hh"
#include "./commit.hh"
#include "./database.hh"
#include "./entry.hh"
#include "./tree.hh"
#include "./workspace.hh"

namespace fs = std::filesystem;

namespace git {

void command(int argc, const char** argv) {
  using namespace std;

  string command(argv[1]);

  if (command == "init") {
    auto path = fs::absolute(argv[2]);
    auto git_path = path / ".git";

    try {
      for (auto dirname : {"objects", "refs"}) {
        fs::create_directories(git_path / dirname);
      }

      cerr << "Initialized empty git repository in " << git_path << endl;
    } catch (fs::filesystem_error& e) {
      cerr << "fatal: " << e.what() << endl;
    }
  } else if (command == "commit") {
    auto root_path = fs::absolute(".");
    auto git_path = root_path / ".git";
    auto db_path = git_path / "objects";

    auto ws = Workspace(root_path);
    auto database = Database(db_path);
    auto tree = Tree();
    for (auto& path : ws.ListFiles()) {
      auto content = ws.ReadFile(path);
      auto blob = Blob(content);
      database.Store(blob);
      content.data();
      tree.add_entry({fs::relative(path), blob.oid()});
      delete const_cast<void*>(content.data());
    }
    database.Store(tree);

    auto name = std::getenv("GIT_AUTHOR_NAME");
    auto email = std::getenv("GIT_AUTHOR_EMAIL");
    time_t now;
    time(&now);
    auto author = Author(name, email, now);

    cin >> std::noskipws;
    istream_iterator<char> it(cin);
    istream_iterator<char> end;
    string message(it, end);

    auto commit = Commit(tree.hex(), author, message);
    database.Store(commit);

    ofstream head;
    head.open(git_path / "HEAD");
    head << commit.hex();
    head.close();

    cout << "[(root-commit) " << commit.hex() << "] " << message << endl;
  } else {
    cerr << "git: '" << command << "' is not a git command." << endl;
    exit(1);
  }
}

}  // namespace git
