#include <boost/format.hpp>
#include <cstring>
#include <libc/open.h>
#include <stdexcept>
#include <stdio.h>

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

namespace deeznes {
namespace libc {

unique_fd open(const char *path, int oflag, mode_t mode) {
    int fd = ::open(path, oflag, mode);
    if (fd == -1) {
        char buf[1024];
        strerror_r(errno, buf, ARRAYSIZE(buf));
        throw std::runtime_error(
            (boost::format("open(%1%) failed: %2%") % path % buf).str());
    }
    return unique_fd(fd);
}

} // namespace libc
} // namespace deeznes