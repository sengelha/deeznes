#include <boost/format.hpp>
#include <cstring>
#include <libc/fstat.h>
#include <stdexcept>

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

namespace deeznes {
namespace libc {

void fstat(int fd, struct stat *buf) {
    int ret = ::fstat(fd, buf);
    if (ret == -1) {
        char buf[1024];
        strerror_r(errno, buf, ARRAYSIZE(buf));
        throw std::runtime_error(
            (boost::format("fstat failed: %1%") % buf).str());
    }
}

} // namespace libc
} // namespace deeznes