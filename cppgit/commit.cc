#include "./commit.hh"

namespace git {

const_buffer Commit::data() const {
  using std::endl;

  stringstream stream;

  stream << "tree " << tree_ << endl;
  stream << "author " << author_.str() << endl;
  stream << "committer " << author_.str() << endl;
  stream << endl;
  stream << message_;
  stream << endl;

  string data{stream.str()};
  char* buffer = new char[data.size()];
  data.copy(buffer, data.size());
  return {buffer, data.size()};
}

}  // namespace git
