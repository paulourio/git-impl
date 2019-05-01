#include "./workspace.hh"

#include <filesystem>
#include <fstream>
#include <vector>

#include <boost/asio/streambuf.hpp>
#include <iostream>

namespace fs = std::filesystem;

namespace git {

vector<string> Workspace::ListFiles() const {
  vector<string> files;

  for (const auto& p : fs::directory_iterator(pathname_)) {
    auto ext = p.path().extension();
    if (ext == ".cc" || ext == ".hh") files.push_back(p.path());
  }
  return files;
}

const_buffer Workspace::ReadFile(string path) const {
  using std::basic_ifstream;
  using std::ios;
  using std::streamsize;

  auto fname = std::filesystem::path(pathname_) / path;

  basic_ifstream<unsigned char> file;
  file.open(fname, ios::ate | ios::binary);
  streamsize size = file.tellg();
  file.seekg(0, ios::beg);

  vector<unsigned char> buffer(size);
  file.read(buffer.data(), size);
  return {buffer.data(), buffer.size()};
}

}  // namespace git
