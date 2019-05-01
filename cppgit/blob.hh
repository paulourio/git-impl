#ifndef _BLOB_H_
#define _BLOB_H_

#include <string>
#include <vector>

#include <boost/asio/buffer.hpp>

#include "./object.hh"

namespace git {

using boost::asio::const_buffer;
using std::string;
using std::vector;

class Blob : public Object {
 public:
  Blob(const const_buffer& data) : data_(data) {}

  virtual const_buffer data() const { return data_; }

  virtual string type() const { return "blob"; }

 private:
  const_buffer data_;
};

}  // namespace git

#endif /* _BLOB_H_ */
