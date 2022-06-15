#ifndef MUDUO_BASE_NONCOPYABLE_H
#define MUDUO_BASE_NONCOPYABLE_H
#include <vector>
using namespace std;

std::vector<int> a;
namespace muduo {

class noncopyable {
 public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

 protected:
  /* data */
  noncopyable(/* args */) = default;
  ~noncopyable() = default;
  int a = 1;
  int b = 1;
};

}  // namespace muduo

#endif  // MUDUO_BASE_NONCOPYABLE_H