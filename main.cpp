#include "JDM.h"

JCLASS ConsoleExample : JPUBLIC JWINDOW {
JPRIVATE:


JPUBLIC:
    ConsoleExample() : JWINDOW("Console Example Test", 100, 80, 8, 8) { }
    JBOOL onUserCreate() {
        JRETURN JTRUE;
    }

    JBOOL onUserUpdate() {
        Clear(BLANK, BG_CYAN);
        JFOR(JFLOAT py = JNONE; py < GetHeight(); py++)
            JFOR(JFLOAT px = JNONE; px < GetWidth(); px++)
                Draw({px, py}, PIXEL_SOLID, rand() % 0x10, JTRUE);
        JRETURN JTRUE;
    }
};

JINT main()
{
    JMS<ConsoleExample>()->Start();
    JRETURN JFALSE;
}
