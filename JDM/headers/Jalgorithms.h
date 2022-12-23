#include "Jtypedef.h"

namespace JDM
{
    constexpr JBOOL collide_point(JCFLOAT x, JCFLOAT y, JCINT width, JCINT height, JCFLOAT x1, JCFLOAT y1)
    {
        return (x <= x1 && x1 <= x + width && y <= y1 && y1 <= y + height);
    }
    constexpr JBOOL collide_box(JCFLOAT x1, JCFLOAT y1, JCINT width1, JCINT height1,
                                JCFLOAT x2, JCFLOAT y2, JCINT width2, JCINT height2)
    {
        if (x1 + width1 < x2)
            return JFALSE;
        if (x1 > x2 + width2)
            return JFALSE;
        if (y1 + height1 < y2)
            return JFALSE;
        if (y1 > y2 + height2)
            return JFALSE;
        return JTRUE;
    }
};