#ifndef MUDUO_BASE_CURRENTTHREAD_H
#define MUDUO_BASE_CURRENTTHREAD_H

#include "mymuduo/base/Type.h"

namespace mymuduo {

namespace CurrentThread {
// __thread是GCC内置的线程局部存储设施。
// _thread变量每一个线程有一份独立实体，各个线程的值互不干扰。
// 可以用来修饰那些带有全局性且值可能变，但是又不值得用全局变量保护的变量。
extern __thread int t_cachedTid;
extern __thread char t_tidString[32];
extern __thread int t_tidStringLength;
extern __thread const char* t_threadName;
void cacheTid();

inline int tid(){
    // 这个指令是gcc引入的，作用是"允许程序员将最有可能执行的分支告诉编译器"。
    // 这个指令的写法为：__builtin_expect(EXP, N)。意思是：EXP==N的概率很大。
    // 此处理解为 t_cachedTid!=0 的概率很大
    if(__builtin_expect(t_cachedTid==0,0)){
        cacheTid();
    }
    return t_cachedTid;
}
//const修饰函数返回值时，函数返回值变为常量，所指向的内容不可改变
inline const char* tidString(){
    return t_tidString;
}

inline int tidStringLength(){
    return t_tidStringLength;
}

inline const char* name(){
    return t_threadName;
}

bool isMainThread();

void sleepUsec(int64_t usec);

string stackTrace(bool demangle);

}  // namespace CurrentThread

}  // namespace mymuduo

#endif