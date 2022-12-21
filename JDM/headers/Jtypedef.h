#pragma once
#include <iostream>
#include <string>

#define JTRUE 1
#define JFALSE 0

void typedef JVOID;

bool typedef JBOOL;
short typedef JSHORT;
int typedef JINT;
long typedef JLONG;
float typedef JFLOAT;
double typedef JDOUBLE;
char typedef JCHAR;
wchar_t typedef JWCHAR;

std::string typedef JSTR;
std::wstring typedef JWSTR;

const bool typedef JCBOOL;
const short typedef JCSHORT;
const int typedef JCINT;
const long typedef JCLONG;
const float typedef JCFLOAT;
const double typedef JCDOUBLE;
const char typedef JCCHAR;
const wchar_t typedef JCWCHAR;

const std::string typedef JCSTR;
const std::wstring typedef JCWSTR;
