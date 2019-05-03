#ifndef _ENTRY_H_
#define _ENTRY_H_

#include <string>

#include <boost/uuid/detail/sha1.hpp>

namespace git {

using boost::uuids::detail::sha1;
using std::string;

class Entry {
 public:
  Entry(const string& path, const sha1& oid) : path_(path), oid_(oid) {}

  virtual string path() const { return path_; }

  virtual sha1 oid() const { return oid_; }

 private:
  string path_;
  sha1 oid_;
};

}  // namespace git

#endif /* _ENTRY_H_ */
