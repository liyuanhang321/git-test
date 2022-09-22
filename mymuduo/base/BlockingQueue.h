#ifndef MUDUO_BASE_BLOCKINGQUEUE_H
#define MUDUO_BASE_BLOCKINGQUEUE_H

#include <assert.h>

#include <deque>

#include "mymuduo/base/Condition.h"
#include "mymuduo/base/Mutex.h"

namespace mymuduo {

template <typename T>
class BlockingQueue : noncopyable {
 public:
  using queue_type = std::deque<T>;

  BlockingQueue() : mutex_(), notEmpty_(mutex_), queue_() {}
void put(const T& x){
    MutexLockGuard lock(mutex_);
    queue_.push_back(x);
    notEmpty_.notify();
}

void put(T&& x){
    MutexLockGuard lock(mutex_);
    queue_.push_back(std::move(x));
    notEmpty_.notify();
}

T take(){
    MutexLockGuard lock(mutex_);
    // always use a while-loop, due to spurious wakeup
    while(queue_.empty()){
        notEmpty_.wait();
    }
    assert(!queue_.empty());
    T front(std::move(queue_.front()));
    queue_.pop_front();
    return front;
}

queue_type drain(){
    std::deque<T> queue;
    {
        MutexLockGuard lock(mutex_);
        queue =std::move(queue_);
        assert(queue_.empty());
    }
    return queue;
}
 private:
  mutable MutexLock mutex_;
  Condition notEmpty_ GUARDED_BY(mutex_);
  queue_type queue_ GUARDED_BY(mutex_);
};

}  // namespace mymuduo

#endif  // MUDUO_BASE_BLOCKINGQUEUE_H