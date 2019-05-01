#include "./database.hh"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/filesystem/operations.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>

#include "./ustring.hh"

namespace fs = std::filesystem;
namespace io = boost::iostreams;

namespace git {

using std::basic_stringstream;
using std::stringstream;
using std::ios;

void Database::Store(Object& object) const {
  const auto& odata = object.data();

  stringstream stream;

  auto type = object.type();
  stream.write(type.c_str(), type.size());

  string space = string(" ");
  stream.write(space.c_str(), space.size());

  string size = std::to_string(object.data().size());
  stream.write(size.c_str(), size.size());

  char nil = 0;
  stream.write(&nil, 1);
  stream.write(reinterpret_cast<const char *>(odata.data()), odata.size());
  stream.flush();

  stream.seekg(0, ios::end);

  boost::uuids::detail::sha1 sha1;
  sha1.process_bytes(stream.str().c_str(), stream.tellg());

  object.set_oid(sha1);

  writeObject(object.hex(), stream);
}

void Database::writeObject(const string& hex, stringstream& content) const {
  using std::ofstream;

  auto dname = fs::path(pathname_) / hex.substr(0, 2);
  auto fname = fs::path(pathname_) / hex.substr(0, 2) / hex.substr(2);

  fs::create_directories(dname);

  std::cout << fname << std::endl;

  stringstream compressed;

  io::filtering_streambuf<io::input> out;
  out.push(io::zlib_compressor());
  out.push(content);
  io::copy(out, compressed);

  auto tmpname = fs::path(dname) / boost::filesystem::unique_path().string();

  ofstream object_file;
  object_file.open(tmpname);
  compressed.seekg(0, ios::end);
  object_file.write(content.str().c_str(), content.tellg());
  object_file.close();

  fs::rename(tmpname, fname);
}

}  // namespace git
