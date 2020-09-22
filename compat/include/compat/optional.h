#pragma once

#if __has_include(<optional>)
#include <optional>
#else
#include <experimental/optional>
#include <utility>

namespace std {

template <typename T> class optional {
private:
  std::experimental::optional<T> inner_;

public:
  optional() = default;
  optional(const optional &rhs) = delete;
  optional &operator=(const optional &rhs) = delete;

  constexpr bool has_value() const noexcept { return (bool)inner_; }

  template <class U = T> optional &operator=(U &&value) {
    inner_.operator=(std::forward<U>(value));
    return *this;
  }

  constexpr const T *operator->() const { return inner_.operator->(); }
  constexpr T *operator->() { return inner_.operator->(); }
};

} // namespace std
#endif