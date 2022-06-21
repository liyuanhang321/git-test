#ifndef MUDUO_BASE_ATOMIC_H
#define MUDUO_BASE_ATOMIC_H

#include <mymuduo/base/noncopyable.h>
#include <stdint.h>

namespace mymuduo {

namespace detail {
template <typename T>
class AtomicIntegerT : noncopyable {
 public:
  AtomicIntegerT() : value_(0) {}
  // type __sync_fetch_and_add (type *ptr, type value, ...)
  // 将value加到*ptr上，结果更新到*ptr，并返回操作之前*ptr的值
  // type __sync_fetch_and_sub (type *ptr, type value, ...)
  // 从*ptr减去value，结果更新到*ptr，并返回操作之前*ptr的值
  // type __sync_fetch_and_or (type *ptr, type value, ...)
  // 将*ptr与value相或，结果更新到*ptr， 并返回操作之前*ptr的值
  // type __sync_fetch_and_and (type *ptr, type value, ...)
  // 将*ptr与value相与，结果更新到*ptr，并返回操作之前*ptr的值
  // type __sync_fetch_and_xor (type *ptr, type value, ...)
  // 将*ptr与value异或，结果更新到*ptr，并返回操作之前*ptr的值
  // type __sync_fetch_and_nand (type *ptr, type value, ...)
  // 将*ptr取反后，与value相与，结果更新到*ptr，并返回操作之前*ptr的值

  // type __sync_add_and_fetch (type *ptr, type value, ...)
  // 将value加到*ptr上，结果更新到*ptr，并返回操作之后新*ptr的值
  // type __sync_sub_and_fetch (type *ptr, type value, ...)
  // 从*ptr减去value，结果更新到*ptr，并返回操作之后新*ptr的值
  // type __sync_or_and_fetch (type *ptr, type value, ...)
  // 将*ptr与value相或， 结果更新到*ptr，并返回操作之后新*ptr的值
  // type __sync_and_and_fetch (type *ptr, type value, ...)
  // 将*ptr与value相与，结果更新到*ptr，并返回操作之后新*ptr的值
  // type __sync_xor_and_fetch (type *ptr, type value, ...)
  // 将*ptr与value异或，结果更新到*ptr，并返回操作之后新*ptr的值
  // type __sync_nand_and_fetch (type *ptr, type value, ...)
  // 将*ptr取反后，与value相与，结果更新到*ptr，并返回操作之后新*ptr的值

  // bool __sync_bool_compare_and_swap (type *ptr, type oldval type newval, ...)
  // 比较*ptr与oldval的值，如果两者相等，则将newval更新到*ptr并返回true
  // type __sync_val_compare_and_swap (type *ptr, type oldval type newval, ...)
  // 比较*ptr与oldval的值，如果两者相等，则将newval更新到*ptr并返回操作之前*ptr的值

  // __sync_synchronize (...)
  // 发出完整内存栅栏
  // type __sync_lock_test_and_set (type *ptr, type value, ...)
  // 将value写入*ptr，对*ptr加锁，并返回操作之前*ptr的值。即，try spinlock语义
  // void __sync_lock_release (type *ptr, ...)
  // 将0写入到*ptr，并对*ptr解锁。即，unlock spinlock语义


  // CAS原语有三个参数，内存地址，期望值，新值。如果内存地址的值==期望值，表示该值未修改，
  //  此时可以修改成新值。否则表示修改失败，返回false，

  T get() {
    // in gcc >= 4.7: __atomic_load_n(&value_, __ATOMIC_SEQ_CST)
    return __sync_val_compare_and_swap(&value_, 0, 0);
  }
  //得到加前的值
  T getAndAdd(T x) {
    // in gcc >= 4.7: __atomic_fetch_add(&value_, x, __ATOMIC_SEQ_CST)
    return __sync_fetch_and_add(&value_, x);
  }
  //得到加之后的值
  T addAndGet(T x) { return getAndAdd(x) + x; }

  //加一
  T incrementAndGet() { return addAndGet(1); }

  //减一
  T decrementAndGet() { return addAndGet(-1); }

  //加x操作
  void add(T x) { getAndAdd(x); }

  //加一操作
  void increment() { incrementAndGet(); }

  //减一操作
  void decrement() { decrementAndGet(); }

  T getAndSet(T newValue) {
    // in gcc >= 4.7: __atomic_exchange_n(&value_, newValue, __ATOMIC_SEQ_CST)
    return __sync_lock_test_and_set(&value_, newValue);
  }

 private:
  volatile T value_;
};
}  // namespace detail

typedef detail::AtomicIntegerT<int32_t> AtomicInt32;
typedef detail::AtomicIntegerT<int64_t> AtomicInt64;
}  // namespace mymuduo

#endif