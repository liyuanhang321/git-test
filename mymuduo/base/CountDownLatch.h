#ifndef MUDUO_BASE_COUNTDOWNLATCH_H
#define MUDUO_BASE_COUNTDOWNLATCH_H

#include "mymuduo/base/Condition.h"
#include "mymuduo/base/Mutex.h"

namespace mymuduo
{
class CountDownLatch : noncopyable
{
public:
    explicit CountDownLatch(int count);

    void wait();

    void countDown();
    int getCount() const;
private:
    mutable MutexLock mutex_;
    Condition condition_ GUARDED_BY(mutex_);
    int count_ GUARDED_BY(mutex_);

};
} // namespace mymuduo


#endif  // MUDUO_BASE_COUNTDOWNLATCH_H