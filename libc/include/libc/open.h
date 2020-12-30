#pragma once

#include <fcntl.h>
#include <libc/unique_fd.h>

namespace deeznes {
namespace libc {

unique_fd open(const char* path, int oflag, mode_t mode);

} // namespace io
} // namespace deeznes