#ifndef MUDUO_BASE_THREADPOOL_H
#define MUDUO_BASE_THREADPOOL_H

#include <deque>
#include <vector>

#include "mymuduo/base/Condition.h"
#include "mymuduo/base/Mutex.h"
#include "mymuduo/base/Thread.h"
#include "mymuduo/base/Type.h"

namespace mymuduo {

class ThreadPool : noncopyable {
 public:
  typedef std::function<void()> Task;
  explicit ThreadPool(const string& nameArg = string("ThreadPool"));
  ~ThreadPool();

  void setMaxQueueSize(int maxSize) { maxQueueSize_ = maxSize; }
  void setThreadInitCallback(const Task& cb) { threadInitCallback_ = cb; }

  void start(int numThreads);
  void stop();

  const string& name()const {return name_;}
  size_t queueSize()const;

  void run(Task f);

 private:
  bool isFull() const REQUIRES(mutex_);
  void runUnThread();
  Task take();

  mutable MutexLock mutex_;
  Condition notEmpty_ GUARDED_BY(mutex_);
  Condition notFull_ GUARDED_BY(mutex_);
  string name_;
  Task threadInitCallback_;
  std::vector<std::unique_ptr<mymuduo::Thread>> threads_;
  std::deque<Task> queue_ GUARDED_BY(mutex_);
  size_t maxQueueSize_;
  bool running_;
};
}  // namespace mymuduo

#endif  // MUDUO_BASE_THREADPOOL_H