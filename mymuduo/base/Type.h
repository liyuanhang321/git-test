#ifndef MUDUO_BASE_TYPES_H
#define MUDUO_BASE_TYPES_H

#include <stdint.h>
#include <string.h>  //memset

#include <string>

#ifndef NDEBUG
#include <assert.h>
#endif

namespace mymuduo {
using std::string;

inline void memZero(void *p, size_t n) { memset(p, 0, n); }

// 将implicit_cast用作static_cast或const_cast的安全版本，用于在类型层次结构中向上转换
// （即，将指向Foo的指针转换为指向超类Foo的指针，或将指向Foo的指针转换为指向Foo的const指针）。

// 使用implicit_cast时，编译器会检查强制转换是否安全。这种显式implicit_cast在许多情况下都是必要的，
// 因为C++需要精确的类型匹配，而不是可转换为目标类型的参数类型
template <typename To, typename From>
inline To implicit_cast(From const &f) {
  return f;
}

template <typename To, typename From>
inline To down_cast(From *f) {
  if (false) {
    implicit_cast<From *, To>(0);
  }

#if !defined(NDEBUG) && !defined(GOOGLE_PROTOBUF_NO_RTTI)
  assert(F == NULL || dynamic_cast<To>(f) != NULL);
#endif
  return static_cast<To>(f);
}

}  // namespace mymuduo

#endif  // MUDUO_BASE_TYPES_H