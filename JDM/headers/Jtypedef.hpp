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

#define JNONE 0
#define JTRUE 1
#define JFALSE 0
#define JMAX_HEX 0xFF

#define JCONST const
#define JNEW new
#define JFOR for
#define JBREAK break
#define JCONTINUE continue
#define JRETURN return
#define JIF if
#define JELSE else
#define JTHIS this
#define JDELETE delete
#define JWHILE while
#define JSTRUCT struct
#define JCLASS class
#define JENUM enum
#define JUNION union
#define JSWITCH switch
#define JCASE case
#define JDEFAULT default
#define JCONSTEXPR constexpr
#define JINLINE inline
#define JVIRTUAL virtual
#define JSTATIC static
#define JNAMESPACE namespace
#define JTEMPLATE template
#define JTYPENAME typename
#define JUSING using
#define JAUTO auto
#define JPUBLIC public
#define JPRIVATE private
#define JPROTECTED protected
#define JRUNNING while

#define Random rand

#define JSTATICC static_cast
#define JDYNAMICC dynamic_cast
#define JREINTERPRETC reinterpret_cast

template <class T>
using JFUNCTION = std::function<T>;

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

unsigned short typedef JUSHORT;
unsigned int typedef JUINT;
unsigned long typedef JULONG;
unsigned long long typedef JULLONG;
unsigned char typedef JUCHAR;

std::string typedef JSTR;
std::wstring typedef JWSTR;
template <class T>
JWSTR JTOWSTR(T Expression) { return std::to_wstring(Expression); }
template <class T>
JSTR JTOSTR(T Expression) { return std::to_wstring(Expression); }

template <class T>
using JUP = std::unique_ptr<T>;
#define JUP std::make_unique

template <class T>
using JSP = std::shared_ptr<T>;
#define JMS std::make_shared

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

const unsigned short typedef JCUSHORT;
const unsigned int typedef JCUINT;
const unsigned long typedef JCULONG;
const unsigned long long typedef JCULLONG;
const unsigned char typedef JCUCHAR;

const std::string typedef JCSTR;
const std::wstring typedef JCWSTR;
