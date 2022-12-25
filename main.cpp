#include "JDM.h"

JCLASS ConsoleExample : JPUBLIC JWINDOW {
JPUBLIC:
    ConsoleExample() : JWINDOW("Game", 50, 50, 10, 10) { }
    JBOOL onUserCreate() {
        JRETURN JTRUE;
    }
    JBOOL onUserUpdate(JFLOAT ElapseTime)
    {
        Clear(BLANK, BG_CYAN);
        JIF (keyboard.Keys[Keys::J_AKEY].isHeld)
            DrawBox(10, 10, 0, 0, PIXEL_SOLID, FG_RED, JFALSE);
        JRETURN JTRUE;
    }
};

JINT main()
{
    JMS<ConsoleExample>()->Start();
    JRETURN JFALSE;
}
