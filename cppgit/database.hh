#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <sstream>
#include <string>

#include "./object.hh"

namespace git {

using std::string;
using std::stringstream;

class Database {
 public:
  Database(string pathname) : pathname_(pathname) {}

  void Store(Object& object) const;

 private:
  void writeObject(const string& hex, stringstream& content, size_t size) const;

  string pathname_;
};

}  // namespace git

#endif /* _DATABASE_H_ */
