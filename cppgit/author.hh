#ifndef _AUTHOR_H_
#define _AUTHOR_H_

#include <ctime>
#include <sstream>
#include <string>

namespace git {

using std::string;
using std::stringstream;

class Author {
 public:
  Author(string name, string email, time_t time)
      : name_(name), email_(email), time_(time) {}

  string str() const;

 private:
  string name_;
  string email_;
  time_t time_;
};

}  // namespace git

#endif /* _AUTHOR_H_ */
