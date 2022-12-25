#include "JDM.h"

JCLASS ConsoleExample : JPUBLIC JWINDOW {
JPRIVATE:


JPUBLIC:
    ConsoleExample() : JWINDOW("NAKAMURA", 200, 120, 5, 5) { }
    JBOOL onUserCreate() {
        JRETURN JTRUE;
    }

    JBOOL onUserUpdate(JFLOAT ElapseTime) {
        Clear(BLANK, BG_CYAN);
        JRETURN JTRUE;
    }
};

JINT main()
{
    JMS<ConsoleExample>()->Start();
    JRETURN JFALSE;
}
