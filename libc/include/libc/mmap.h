#pragma once

#include <sys/mman.h>

namespace deeznes {
namespace libc {

// TODO: Replace below with RAII class
void* mmap(void* addr, size_t len, int prot, int flags, int fd, off_t offset);

} // namespace io
} // namespace deeznes