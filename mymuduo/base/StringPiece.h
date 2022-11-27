#ifndef MUDUO_BASE_STRINGPIECE_H
#define MUDUO_BASE_STRINGPIECE_H

#include <string.h>
#include<string>
#include <iosfwd>

#include "mymuduo/base/Type.h"

namespace mymuduo {

class StringArg {
 public:
    StringArg(const char* str):str_(str){}
    StringArg(const string& str):str_(str.c_str()){}

    const char* c_str() const { return str_;}
    //1、只允许在类的非静态成员函数后面加const；(加到非成员函数 或 静态成员后面会产生编译错);
    //2、后面加的const其实是对隐含传入参数this指向类对象的修饰，即 *this  是被const修饰，
    //那this所指向的类对象的成员都是不允许被修改的；
    //（备注：有何友人认为const修饰的是this指针，那么不能改变的就是this指针本身，
    //而不是this指针指向的成员，其实这个const修饰的是this和(*this),下面代码有详细解释）
    //3、唯一的例外是对于mutable修饰的成员。
    //4、加了const的成员函数可以被非const对象和const对象调用，
    //但不加const的成员函数只能被非const对象调用

private:
    const char* str_;
};

}  // namespace mymuduo
#endif  // MUDUO_BASE_STRINGPIECE_H