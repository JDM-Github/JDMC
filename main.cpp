#include "JDM.h"

JCLASS ConsoleExample : JPUBLIC JWINDOW {

JPRIVATE:
JPUBLIC:
    ConsoleExample() : JWINDOW("ConsoleExample", 100, 80, 10, 10) { }
    JBOOL onUserCreate() {
        JRETURN JTRUE;
    }

    JBOOL onUserUpdate() {
        Clear(BLANK, BG_BLACK);
        JRETURN JTRUE;
    }
};

JINT main()
{
    srand(std::time(JNONE));
    JMS<ConsoleExample>()->Start();
    JRETURN JFALSE;
}
