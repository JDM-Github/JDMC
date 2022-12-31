#include <fstream>
#include <algorithm>
#include "Jenums.hpp"

#define PI 3.14159265358979323846
#define PHI 1.618

JNAMESPACE JDM {
    JCONSTEXPR JBOOL collide_point(JCFLOAT x, JCFLOAT y, JCINT width, JCINT height, JCFLOAT x1, JCFLOAT y1) {
        JRETURN(x <= x1 && x1 < x + width && y <= y1 && y1 < y + height);
    }
    JCONSTEXPR JBOOL collide_point(JCFLOAT x, JCFLOAT y, JCINT width, JCINT height, JDM::Pos2D MousePosition) {
        JRETURN(x <= MousePosition.X && MousePosition.X < x + width && y <= MousePosition.Y && MousePosition.Y < y + height);
    }
    JCONSTEXPR JBOOL collide_box(JCFLOAT x1, JCFLOAT y1, JCINT width1, JCINT height1,
                             JCFLOAT x2, JCFLOAT y2, JCINT width2, JCINT height2) {
        JIF(x1 + width1 < x2) JRETURN JFALSE;
        JIF(x1 > x2 + width2) JRETURN JFALSE;
        JIF(y1 + height1 < y2) JRETURN JFALSE;
        JIF(y1 > y2 + height2) JRETURN JFALSE;
        JRETURN JTRUE;
    }
    JBOOL checkExist(JCSTR &file)
    {
        std::ifstream ifile;
        ifile.open(file);
        JBOOL isExist = (ifile) ? JTRUE : JFALSE;
        ifile.close();
        JRETURN isExist;
    }

    JCONSTEXPR JVOID Negative(JFLOAT &Value) { Value = std::abs(Value) * -1; }
    JCONSTEXPR JVOID Negative(JINT &Value) { Value = std::abs(Value) * -1; }
    JCONSTEXPR JVOID Positive(JFLOAT &Value) { Value = std::abs(Value); }
    JCONSTEXPR JVOID Positive(JINT &Value) { Value = std::abs(Value); }
    JCONSTEXPR JFLOAT RetNegative(JFLOAT &Value) { JRETURN std::abs(Value) * -1; }
    JCONSTEXPR JINT RetNegative(JINT &Value) { JRETURN std::abs(Value) * -1; }
    JCONSTEXPR JFLOAT RetPositive(JFLOAT &Value) { JRETURN std::abs(Value); }
    JCONSTEXPR JINT RetPositive(JINT &Value) { JRETURN std::abs(Value); }

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

    
};

