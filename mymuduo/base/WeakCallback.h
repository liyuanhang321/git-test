#ifndef MUDUO_BASE_WEAKCALLBACK_H
#define MUDUO_BASE_WEAKCALLBACK_H

#include <functional>
#include <memory>

namespace mymuduo {
template <typename CLASS, typename... ARGS>
class WeakCallback { //用于保存一个类的函数和这个类的一个对象(智能指针)
 public:
  WeakCallback(const std::weak_ptr<CLASS>& object,
               const std::function<void(CLASS*, ARGS...)>& function)
      : object_(object), function_(function) {}

  void operator()(ARGS&&... args) const {
    //&&是引用折叠
    // && && -> &&
    // & && -> &
    // & & -> &
    // && & -> &
    std::shared_ptr<CLASS> ptr(object_.lock());
    if (ptr) {
      function_(ptr.get(), std::forward<ARGS>(args)...);
    }
    //  lock为std::weak_pt的成员函数，通过调用lock()函数，
    //  可以将弱引用指针std::weak_ptr提升为std::shared_ptr，
    //  再通过非空判断来确定当前智能指针执行的对象是否存在，如果不为空，则执行相应回调
  }

 private:
  std::weak_ptr<CLASS> object_;
  std::function<void(CLASS*, ARGS...)> function_;
};

template <typename CLASS, typename... ARGS>
WeakCallback<CLASS, ARGS...> makeWeakCallback(
    const std::shared_ptr<CLASS>& object, void (CLASS::*function)(ARGS...)) {
  return WeakCallback<CLASS, ARGS...>(object, function);
}

template <typename CLASS, typename... ARGS>
WeakCallback<CLASS, ARGS...> makeWeakCallback(
    const std::shared_ptr<CLASS>& object,
    void (CLASS::*function)(ARGS...) const) {
  return WeakCallback<CLASS, ARGS...>(object, function);
}

}  // namespace mymuduo

#endif