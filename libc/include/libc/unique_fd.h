#pragma once

#include <unistd.h>

namespace deeznes {
namespace libc {

class unique_fd {
private:
  int fd_;
public:
  constexpr unique_fd() noexcept : fd_(-1) {}
  explicit unique_fd(int fd) noexcept : fd_(fd) {}
  unique_fd(unique_fd&& fd) noexcept : fd_(fd.release()) {}
  ~unique_fd() { reset(); }

  unique_fd& operator=(unique_fd&& r) noexcept
  {
    reset(r.release());
    return *this;
  }

  int get() const { return fd_; }

  int release() {
    int fd = fd_;
    fd_ = -1;
    return fd;
  }

  void reset(int fd = -1) {
    if (fd_ != -1) {
      close(fd_);
    }
    fd_ = fd;
  }
};

} // namespace io
} // namespace deeznes