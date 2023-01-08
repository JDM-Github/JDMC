#pragma once
#include <ctime>
#include <fstream>
#include <algorithm>
#include "Jenums.hpp"

#define PI 3.14159265358979323846
#define PHI 1.618

JNAMESPACE JDM{
    JVOID SetRandomSeed() { srand(std::time(JNONE)); }
    JCONSTEXPR JBOOL collide_point(JCONST JDM::SizePosDF position, JCFLOAT x1, JCFLOAT y1) {
        JRETURN(position.X <= x1 && x1 < position.X + position.Width && position.Y <= y1 && y1 < position.Y + position.Height);
    }
    JCONSTEXPR JBOOL collide_point(JCONST JDM::SizePosDF position, JCONST JDM::Pos2D MousePosition) {
        JRETURN(position.X <= MousePosition.X && MousePosition.X < position.X + position.Width
             && position.Y <= MousePosition.Y && MousePosition.Y < position.Y + position.Height);
    }
    JCONSTEXPR JBOOL collide_box(JCONST JDM::SizePosDF firstPosition,
                                 JCONST JDM::SizePosDF secondPosition) {
        JIF(firstPosition.X + firstPosition.Width < secondPosition.X) JRETURN JFALSE;
        JIF(firstPosition.X > secondPosition.X + secondPosition.Width) JRETURN JFALSE;
        JIF(firstPosition.Y + firstPosition.Height < secondPosition.Y) JRETURN JFALSE;
        JIF(firstPosition.Y > secondPosition.Y + secondPosition.Height) JRETURN JFALSE;
        JRETURN JTRUE;
    }
    JBOOL checkExist(JCSTR &file) {
        std::ifstream ifile;
        ifile.open(file);
        JBOOL isExist = (ifile) ? JTRUE : JFALSE;
        ifile.close();
        JRETURN isExist;
    }

    JCONSTEXPR JVOID Reverse(JFLOAT &Value) { Value = Value * 1; }
    JCONSTEXPR JVOID Reverse(JINT &Value) { Value = Value * 1; }
    JCONSTEXPR JVOID Negative(JFLOAT &Value) { Value = std::abs(Value) * -1; }
    JCONSTEXPR JVOID Negative(JINT &Value) { Value = std::abs(Value) * -1; }
    JCONSTEXPR JVOID Positive(JFLOAT &Value) { Value = std::abs(Value); }
    JCONSTEXPR JVOID Positive(JINT &Value) { Value = std::abs(Value); }

    JCONSTEXPR JFLOAT RetReverse(JFLOAT Value) { JRETURN Value * 1; }
    JCONSTEXPR JINT RetReverse(JINT Value) { JRETURN Value * 1; }
    JCONSTEXPR JFLOAT RetNegative(JFLOAT Value) { JRETURN std::abs(Value) * -1; }
    JCONSTEXPR JINT RetNegative(JINT Value) { JRETURN std::abs(Value) * -1; }
    JCONSTEXPR JFLOAT RetPositive(JFLOAT Value) { JRETURN std::abs(Value); }
    JCONSTEXPR JINT RetPositive(JINT Value) { JRETURN std::abs(Value); }

    JTEMPLATE<JCLASS T>
    JFLOAT Max(T maximumValue) { JRETURN maximumValue; }
    JTEMPLATE<JCLASS T, JCLASS ... Args>
    JFLOAT Max(T firstValue, T secondValue, Args... args) {
        JRETURN Max(((firstValue > secondValue) ? firstValue : secondValue), args...);
    }

    JTEMPLATE<JCLASS T>
    JFLOAT Min(T maximumValue) { JRETURN maximumValue; }
    JTEMPLATE<JCLASS T, JCLASS ... Args>
    JFLOAT Min(T firstValue, T secondValue, Args... args) {
        JRETURN Min(((firstValue < secondValue) ? firstValue : secondValue), args...);
    }
    JINT GetVectorIndex(JVECTOR<JINT> &Vector, JINT Key) {
        JVECTOR<JINT>::iterator itr = std::find(Vector.begin(), Vector.end(), Key);
        JRETURN std::distance(Vector.begin(), itr);
    }
    JINT Randint(JINT first, JINT second) { JRETURN first + (Random() % (second + (first * -1))); }
    JFLOAT Randfloat(JINT first, JINT second) {
        JINT FirstValue = (first + (Random() % (second + (first * -1)))) + 1;
        JFLOAT SecondValue = (9.0f / (9 + (Random() % 100)));
        JRETURN FirstValue - SecondValue;
    }

    
};

