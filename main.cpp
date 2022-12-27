#include "JDM.h"

JCLASS ConsoleGameExample : JPUBLIC JWINDOW {

JPRIVATE:
JPUBLIC:
    ConsoleGameExample() : JWINDOW("ConsoleGameExample", 140, 100, 5, 5) { }
    JBOOL onUserCreate() { JRETURN JTRUE; }
    JBOOL onUserUpdate() {
        Clear(BLANK, BG_BLACK);
        JRETURN JTRUE;
    }
};

JINT main()
{
    srand(std::time(0));
    JMS<ConsoleGameExample>()->Start();
    JRETURN JFALSE;
}
