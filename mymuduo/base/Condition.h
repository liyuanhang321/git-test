#ifndef MUDUO_BASE_CONDITION_H
#define MUDUO_BASE_CONDITION_H

#include <pthread.h>

#include "mymuduo/base/Mutex.h"

namespace mymuduo {
class Condition {
  explicit Condition(MutexLock &mutex) : mutex_(mutex) {
    MCHECK(pthread_cond_init(&pcond_, NULL));
  }
  ~Condition() { MCHECK(pthread_cond_destroy(&pcond_)); }

  void wait() {
    MutexLock::UnassignGuard ug(mutex_);
    MCHECK(pthread_cond_wait(&pcond_, mutex_.getPthreadMutex()));
  }

  bool waitForSeconds(double seconds);

  void notify() { MCHECK(pthread_cond_signal(&pcond_)); }

  void notifyAll() { MCHECK(pthread_cond_broadcast(&pcond_)); }

 private:
  MutexLock &mutex_;
  pthread_cond_t pcond_;
};
}  // namespace mymuduo

#endif  // MUDUO_BASE_class ConditionCONDITION_H