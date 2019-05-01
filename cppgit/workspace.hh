#ifndef _WORKSPACE_H_
#define _WORKSPACE_H_

#include <string>
#include <vector>

#include <boost/asio/buffer.hpp>

namespace git {

using boost::asio::const_buffer;
using std::string;
using std::vector;

class Workspace {
 public:
  Workspace(string pathname) : pathname_(pathname) {}

  vector<string> ListFiles() const;

  const_buffer ReadFile(string path) const;

 private:
  string pathname_;
};

}  // namespace git

#endif /* _WORKSPACE_H_ */
