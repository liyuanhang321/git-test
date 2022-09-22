
//C

// C++
#include <iostream>
using namespace std;
string str1;
string tem=str1.substr(0,1);
//----------------------------------------------------
#include <pthread.h>


//----------------------------------------------------
#include <string.h>
//memset
void myzero(void *a, size_t n) { memset(a, 0, n); }
string s;
// s.find('a');


//----------------------------------------------------
#include<unordered_map>
unordered_map<char,int> map;
// __DATE__ 当前日期，一个以 “MMM DD YYYY” 格式表示的字符串常量。

// __TIME__ 当前时间，一个以 “HH:MM:SS” 格式表示的字符串常量。

// __FILE__ 这会包含当前文件名，一个字符串常量。

// __LINE__ 这会包含当前行号，一个十进制常量。

// __STDC__ 当编译器以 ANSI 标准编译时，则定义为 1；判断该文件是不是标准 C 程序。

// __FUNCTION__ 程序预编译时预编译器将用所在的函数名，返回值是字符串;


#include<limits.h>
// INT_MAX //32位最大整数  2^32 -1;
// INT_MIN //32位最小整数  -2^32


#include<vector>
std::vector<int>a;
// a.resize(10); //重新设置大小
//a.emplace_back(10);  //比push_back()更省时间


#include<assert.h>
//assert(int expression) //为假时报警

