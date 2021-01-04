#pragma once

#include <iterator>
#include <type_traits>

namespace std {

template <typename T> class span {
  public:
    typedef T element_type;
    typedef typename std::remove_cv<T>::type value_type;
    typedef std::size_t size_type;
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;

  private:
    T *data_;
    size_type size_;

  public:
    constexpr span(pointer ptr, size_type count) noexcept : data_(ptr), size_(count) {}

    template <std::size_t N>
    constexpr span(element_type (&arr)[N]) noexcept : data_(arr), size_(N) {}

    constexpr iterator begin() const noexcept { return data_; }
    constexpr iterator end() const noexcept { return data_ + size_; }

    constexpr reference operator[](size_type idx) const { return data_[idx]; }

    constexpr size_type size() const noexcept { return size_; }
};

} // namespace std