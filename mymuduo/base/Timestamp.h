#ifndef MUDUO_BASE_TIMESTAMP_H
#define MUDUO_BASE_TIMESTAMP_H

#include <boost/operators.hpp>

#include "mymuduo/base/Type.h"
#include "mymuduo/base/copyable.h"

namespace mymuduo {
class TimeStamp : public mymuduo::copyable,
                  public boost::equality_comparable<TimeStamp>,
                  // bool operator==(const T&,const T&);派生类必须实现
                  // bool operator!=(const T&,const T&);
                  public boost::less_than_comparable<TimeStamp>
// bool operator<(const T&,const T&); 派生类必须实现
// bool operator>(const T&,const T&);
// bool operator<=(const T&,const T&);
// bool operator>=(const T&,const T&);
{
 public:
  TimeStamp() : microSecondsSinceEpoch_(0) {}

  explicit TimeStamp(int64_t microSecondsSinceEpochArg)
      : microSecondsSinceEpoch_(microSecondsSinceEpochArg) {}

  void swap(TimeStamp& that) {
    std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
  }

  string toSting() const;
  string toFormattedString(bool showMicroseconds = true) const;

  bool valid() const { return microSecondsSinceEpoch_ > 0; }

  int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }
  time_t secondsSinceEpoch() const {
    return static_cast<time_t>(microSecondsSinceEpoch_ /
                               kMicroSecondsPerSecond);
  }

  static TimeStamp now();

  static TimeStamp invalid() { return TimeStamp(); }

  static TimeStamp fromUnixTime(time_t t) { return fromUnixTime(t, 0); };

  static TimeStamp fromUnixTime(time_t t, int microseconds) {
    return TimeStamp(static_cast<int64_t>(t) * kMicroSecondsPerSecond +
                     microseconds);
    // static_cast
    // ①用于类层次结构中基类（父类）和 派生类 （子类）之间指针或引用的转换。
    // 进行上行转换（把派生类的指针或引用转换成基类表示）是安全的；
    // 进行下行转换（把基类指针或引用转换成派生类表示）时，由于没有动态类型检查，所以是不安全的。
    // ②用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。这种转换的安全性也要开发人员来保证。
    // ③把空指针转换成目标类型的空指针。
    // ④把任何类型的表达式转换成void类型。
    // 注意：static_cast不能转换掉expression的const、volatile、或者__unaligned属性。
  }

  static const int kMicroSecondsPerSecond = 1000 * 1000;

 private:
  int64_t microSecondsSinceEpoch_;
};

inline bool operator<(TimeStamp lhs, TimeStamp rhs) {
  return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator==(TimeStamp lhs, TimeStamp rhs) {
  return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

inline double timeDifference(TimeStamp high, TimeStamp low) {
  int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
  return static_cast<double>(diff) / TimeStamp::kMicroSecondsPerSecond;
}

inline TimeStamp addTime(TimeStamp timestamp, double seconds) {
  int64_t delta =
      static_cast<int64_t>(seconds * TimeStamp::kMicroSecondsPerSecond);
  return TimeStamp(timestamp.microSecondsSinceEpoch() + delta);
}

}  // namespace mymuduo

#endif  // MUDUO_BASE_TIMESTAMP_H