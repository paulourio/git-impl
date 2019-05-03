#include "./tree.hh"

#include <sstream>

namespace git {

using std::stringstream;

const_buffer Tree::data() const {
  using std::ios;

  stringstream stream;

  string mode{"100644"};
  string space{" "};

  for (const auto& entry : entries_) {
    stream.write(mode.c_str(), mode.size());
    stream.write(space.c_str(), space.size());
    stream.write(entry.path().c_str(), entry.path().size());
    char nil = 0;
    stream.write(&nil, 1);
    union hash {
      char c[20];
      unsigned u[5];
    } hash;
    entry.oid().get_digest(hash.u);
    stream.write(hash.c, sizeof(hash.c));
  }
  stream.flush();
  stream.seekg(0, ios::end);

  string data{stream.str()};

  char* buffer = new char[data.size()];
  data.copy(buffer, data.size());
  return {buffer, data.size()};
}

};  // namespace git
