#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>

#include <boost/asio/buffer.hpp>
#include <boost/uuid/detail/sha1.hpp>

namespace git {

using boost::asio::const_buffer;
using boost::uuids::detail::sha1;
using std::string;

class Object {
 public:
  virtual const_buffer data() const = 0;

  virtual string type() const = 0;

  sha1 oid() const { return oid_; }
  void set_oid(sha1 oid) { oid_ = oid; }

  string hex() const {
    unsigned hash[5] = {0};

    oid().get_digest(hash);

    char buf[41] = {0};

    for (int i = 0; i < 5; i++) {
      std::sprintf(buf + (i << 3), "%08x", hash[i]);
    }
    return string(buf);
  }

 private:
  sha1 oid_;
};

}  // namespace git

#endif /* _OBJECT_H_ */
