#include <libc/mmap.h>
#include <boost/format.hpp>
#include <stdexcept>
#include <iostream>

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

namespace deeznes {
namespace libc {

void* mmap(void* addr, size_t len, int prot, int flags, int fd, off_t offset)
{
    void* ret = ::mmap(addr, len, prot, flags, fd, offset);
    if (ret == MAP_FAILED) {
        char buf[1024];
        strerror_r(errno, buf, ARRAYSIZE(buf));
        throw std::runtime_error((boost::format("mmap failed: %1%") % buf).str());
    }
    return ret;
}

}
}