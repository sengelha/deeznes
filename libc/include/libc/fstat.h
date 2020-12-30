#pragma once

#include <sys/stat.h>

namespace deeznes {
namespace libc {

void fstat(int fd, struct stat* buf);

} // namespace io
} // namespace deeznes