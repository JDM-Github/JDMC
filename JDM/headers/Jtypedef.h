#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <list>
#include <set>
#include <stack>
#include <queue>
#include <chrono>

#define JTRUE 1
#define JFALSE 0

#if AUTONAMESPACE
using namespace JDM;
using namespace std;
#endif

void typedef JVOID;
bool typedef JBOOL;
short typedef JSHORT;
int typedef JINT;
long typedef JLONG;
long long typedef JLLONG;
float typedef JFLOAT;
double typedef JDOUBLE;
char typedef JCHAR;
wchar_t typedef JWCHAR;

std::string typedef JSTR;
std::wstring typedef JWSTR;
template <class T>
JWSTR JTOWSTR(T Expression) { return std::to_wstring(Expression); }
template <class T>
JSTR JTOSTR(T Expression) { return std::to_wstring(Expression); }

template <class T>
using JUP = std::unique_ptr<T>;
template <class T, typename... Args>
JUP<T> JUS(Args... arguments) { return std::make_unique<T>(arguments...); }
template <class T>
using JSP = std::shared_ptr<T>;
template <class T, typename... Args>
JSP<T> JMS(Args... arguments) { return std::make_shared<T>(arguments...); }

template <class T>
using JVECTOR = std::vector<T>;
template <class T>
using JSET = std::set<T>;
template <class T>
using JSTACK = std::stack<T>;
template <class T>
using JQUEUE = std::queue<T>;
template <class T>
using JLIST = std::list<T>;

std::chrono::_V2::system_clock::time_point typedef JTIMEPOINT;

const bool typedef JCBOOL;
const short typedef JCSHORT;
const int typedef JCINT;
const long typedef JCLONG;
const long long typedef JCLLONG;
const float typedef JCFLOAT;
const double typedef JCDOUBLE;
const char typedef JCCHAR;
const wchar_t typedef JCWCHAR;

const std::string typedef JCSTR;
const std::wstring typedef JCWSTR;
