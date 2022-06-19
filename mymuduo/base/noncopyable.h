#ifndef MUDUO_BASE_NONCOPYABLE_H
#define MUDUO_BASE_NONCOPYABLE_H
#include <vector>
using namespace std;

namespace mymuduo {

class noncopyable {
 public:
  noncopyable(const noncopyable&) = delete;  //防止隐式转换
  void operator=(const noncopyable&) = delete;

 protected:
  /* data */
  noncopyable(/* args */) = default; //生成默认构造函数
  ~noncopyable() = default;

};

}  // namespace mymuduo

#endif  // MUDUO_BASE_NONCOPYABLE_H