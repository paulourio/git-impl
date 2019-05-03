#ifndef _TREE_H_
#define _TREE_H_

#include <string>
#include <vector>

#include <boost/asio/buffer.hpp>

#include "entry.hh"
#include "object.hh"

namespace git {

using boost::asio::const_buffer;
using std::string;
using std::vector;

class Tree : public Object {
 public:
  void add_entry(Entry&& entry) { entries_.emplace_back(entry); }

  virtual const_buffer data() const;

  virtual string type() const { return "tree"; }

 private:
  vector<Entry> entries_;
};

}  // namespace git

#endif /* _TREE_H_ */
