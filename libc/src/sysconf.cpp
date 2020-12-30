#include <boost/format.hpp>
#include <libc/sysconf.h>
#include <stdexcept>

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

namespace deeznes {
namespace libc {

long sysconf(int name) {
    long ret = ::sysconf(name);
    if (ret == -1) {
        throw std::runtime_error("sysconf failed");
    }
    return ret;
}

} // namespace libc
} // namespace deeznes