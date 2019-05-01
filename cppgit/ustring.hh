#ifndef _USTRING_H_
#define _USTRING_H_

#include <sstream>
#include <string>

namespace git {

typedef std::basic_string<unsigned char> ustring;

inline ustring to_ustring(const std::string& sys_enc) {
  return ustring(sys_enc.begin(), sys_enc.end());
}

template <std::size_t N>
inline ustring to_ustring(const char (&array)[N]) {
  return ustring(array, array + N);
}

inline ustring to_ustring(const char* pstr) {
  return ustring(reinterpret_cast<const ustring::value_type*>(pstr));
}

std::ostream& operator<<(std::ostream& os, const ustring& u) {
  for (auto c : u) os << c;
  return os;
}

}  // namespace git

#endif /* _USTRING_H_ */
