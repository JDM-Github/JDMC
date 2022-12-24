#include "Jtypedef.h"

JNAMESPACE JDM{
    JCONSTEXPR JBOOL collide_point(JCFLOAT x, JCFLOAT y, JCINT width, JCINT height, JCFLOAT x1, JCFLOAT y1){JRETURN(x <= x1 && x1 <= x + width && y <= y1 && y1 <= y + height);
}
JCONSTEXPR JBOOL collide_box(JCFLOAT x1, JCFLOAT y1, JCINT width1, JCINT height1,
                             JCFLOAT x2, JCFLOAT y2, JCINT width2, JCINT height2)
{
    JIF(x1 + width1 < x2)
    JRETURN JFALSE;
    JIF(x1 > x2 + width2)
    JRETURN JFALSE;
    JIF(y1 + height1 < y2)
    JRETURN JFALSE;
    JIF(y1 > y2 + height2)
    JRETURN JFALSE;
    JRETURN JTRUE;
}
}
;