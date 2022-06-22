#ifndef MUDUO_BASE_MUTEX_H
#define MUDUO_BASE_MUTEX_H

#include "mymuduo/base/CurrentThread.h"
#include "mymuduo/base/noncopyable.h"
#include <assert.h>
#include <pthread.h>

// Thread safety annotations {
// https://clang.llvm.org/docs/ThreadSafetyAnalysis.html

// Enable thread safety attributes only with clang.
// The attributes can be safely erased when compiling with other compilers.
#if defined(__clang__) && (!defined(SWIG))
#define THREAD_ANNOTATION_ATTRIBUTE__(x)   __attribute__((x))
#else
#define THREAD_ANNOTATION_ATTRIBUTE__(x)   // no-op
#endif

//CAPABILITY 表明某个类对象可以当作 capability 使用
#define CAPABILITY(x) \
  THREAD_ANNOTATION_ATTRIBUTE__(capability(x))

//SCOPED_CAPABILITY 用于修饰基于 RAII 实现的 capability。
#define SCOPED_CAPABILITY \
  THREAD_ANNOTATION_ATTRIBUTE__(scoped_lockable)

//它声明数据成员受给定功能的保护
#define GUARDED_BY(x) \
  THREAD_ANNOTATION_ATTRIBUTE__(guarded_by(x))

//用于指针和智能指针
#define PT_GUARDED_BY(x) \
  THREAD_ANNOTATION_ATTRIBUTE__(pt_guarded_by(x))

// __VA_ARGS__ :将左边宏中 .. 的内容原样抄写在右边 __VA_ARGS__ 所在的位置;
//在...之前获得锁
#define ACQUIRED_BEFORE(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(acquired_before(__VA_ARGS__))

//在...之后获得锁
#define ACQUIRED_AFTER(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(acquired_after(__VA_ARGS__))

//REQUIRES 声明调用线程必须拥有对指定的 capability 具有独占访问权。可以指定多个 capabilities。
// 函数/方法在访问资源时，必须先上锁，再调用函数，然后再解锁(注意，不是在函数内解锁)
#define REQUIRES(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(requires_capability(__VA_ARGS__))

// REQUIRES_SHARED 功能与 REQUIRES 相同，但是可以共享访问
#define REQUIRES_SHARED(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(requires_shared_capability(__VA_ARGS__))


//ACQUIRE 表示一个函数/方法需要持有一个 capability，但并不释放这个 capability。
// 调用者在调用被 ACQUIRE 修饰的函数/方法时，要确保没有持有任何 capability，
// 同时在函数/方法结束时会持有一个 capability(加锁的过程发生在函数体内)
#define ACQUIRE(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(acquire_capability(__VA_ARGS__))

//ACQUIRE_SHARED 与 ACQUIRE 的功能是类似的，但持有的是共享的 capability
#define ACQUIRE_SHARED(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(acquire_shared_capability(__VA_ARGS__))

//RELEASE 和 RELEASE_SHARED 与 ACQUIRE 和 ACQUIRE_SHARED 正相反，它们表示调用方在调用该函数/方法时需要先持有锁，
// 而当函数执行结束后会释放锁(释放锁的行为发生在函数体内)
#define RELEASE(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(release_capability(__VA_ARGS__))

#define RELEASE_SHARED(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(release_shared_capability(__VA_ARGS__))

//ACQUIRE 和 ACQUIRE_SHARED 的尝试版本，第一个参数是 bool，true 代表成功，false 代表失败
#define TRY_ACQUIRE(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(try_acquire_capability(__VA_ARGS__))

#define TRY_ACQUIRE_SHARED(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(try_acquire_shared_capability(__VA_ARGS__))

//EXCLUDES 用于显式声明函数/方法不应该持有某个特定的 capability。
// 由于 mutex 的实现通常是不可重入的，因此 EXCLUDES 通常被用来预防死锁
#define EXCLUDES(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(locks_excluded(__VA_ARGS__))

//ASSERT_* 表示在运行时检测调用线程是否持有 capability
#define ASSERT_CAPABILITY(x) \
  THREAD_ANNOTATION_ATTRIBUTE__(assert_capability(x))

#define ASSERT_SHARED_CAPABILITY(x) \
  THREAD_ANNOTATION_ATTRIBUTE__(assert_shared_capability(x))
  
//RETURN_CAPABILITY 通常用于修饰那些被当作 capability getter 的函数，
// 这些函数会返回 capability 的引用或指针
#define RETURN_CAPABILITY(x) \
  THREAD_ANNOTATION_ATTRIBUTE__(lock_returned(x))

//NO_THREAD_SAFETY_ANALYSIS 表示关闭某个函数/方法的 TSA 检测，通常只用于两种情况：
// 1，该函数/方法可以被做成非线程安全；2、函数/方法太过复杂，TSA 无法进行检测
#define NO_THREAD_SAFETY_ANALYSIS \
  THREAD_ANNOTATION_ATTRIBUTE__(no_thread_safety_analysis)

// End of thread safety annotations }


#ifdef CHECK_PTHREAD_RETURN_VALUE

#ifdef NDEBUG
__BEGIN_DECLS
extern void __assert_perror_fail (int errnum,
                                  const char *file,
                                  unsigned int line,
                                  const char *function)
    noexcept __attribute__ ((__noreturn__));
__END_DECLS
#endif

#define MCHECK(ret) ({ __typeof__ (ret) errnum = (ret);         \
                       if (__builtin_expect(errnum != 0, 0))    \
                         __assert_perror_fail (errnum, __FILE__, __LINE__, __func__);})

#else  // CHECK_PTHREAD_RETURN_VALUE

#define MCHECK(ret) ({ __typeof__ (ret) errnum = (ret);         \
                       assert(errnum == 0); (void) errnum;})

#endif // CHECK_PTHREAD_RETURN_VALUE





#endif  // MUDUO_BASE_MUTEX_H