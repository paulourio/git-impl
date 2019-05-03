#include "author.hh"

#include <sstream>
#include <string>

#include "date.hh"

namespace git {

using std::string;
using std::stringstream;

string Author::str() const {
  stringstream ss;
  ss << name_ << " <" << email_ << "> ";

  char tstamp[40];
  datestamp(tstamp, sizeof(tstamp));
  ss << tstamp;
  return ss.str();
}

}  // namespace git
