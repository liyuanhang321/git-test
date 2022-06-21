#ifndef MUDUO_BASE_DATE_H
#define MUDUO_BASE_DATE_H

#include "mymuduo/base/Type.h"
#include "mymuduo/base/copyable.h"

struct tm;

namespace mymuduo {
class Date : public mymuduo::copyable {
 public:
  struct YearMonthDay {
    int year;
    int month;
    int day;
  };

  static const int kDaysPerWeek = 7;
  static const int KJulianDayof_1970_01_01;

  Date() : julianDayNumber_(0) {}
  Date(int year, int month, int day);

  explicit Date(int julianDayNum) : julianDayNumber_(julianDayNum) {}

  explicit Date(const struct tm&);

  void swap(Date& that) { std::swap(julianDayNumber_, that.julianDayNumber_); }

  //函数后加const 表示函数体内不能对成员数据做任何改动，否则编译器报错
  bool valid() const { return julianDayNumber_ > 0; }

  string toIsoString() const;

  struct YearMonthDay yearMonthDay() const;

  int year() const { return yearMonthDay().year; }

  int month() const { return yearMonthDay().month; }

  int day() const { return yearMonthDay().day; }

  int weekDay() const { return (julianDayNumber_ + 1) % kDaysPerWeek; }

  int julianDayNumber() const { return julianDayNumber_; }

 private:
  int julianDayNumber_;
};

inline bool operator<(Date x, Date y) {
  return x.julianDayNumber() < y.julianDayNumber();
}

inline bool operator==(Date x, Date y) {
  return x.julianDayNumber() == y.julianDayNumber();
}
}  // namespace mymuduo

#endif