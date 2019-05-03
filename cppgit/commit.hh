#ifndef _COMMIT_H_
#define _COMMIT_H_

#include <ctime>
#include <sstream>
#include <string>

#include <boost/asio/buffer.hpp>

#include "./author.hh"
#include "./object.hh"

namespace git {

using boost::asio::const_buffer;
using std::string;
using std::stringstream;

class Commit: public Object {
 public:
  Commit(string tree, Author author, string message)
      : tree_(tree), author_(author), message_(message) {}

  virtual const_buffer data() const;

  virtual string type() const { return "commit"; }

 private:
  string tree_;
  Author author_;
  string message_;
};

}  // namespace git

#endif /* _COMMIT_H_ */
