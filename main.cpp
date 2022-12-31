#include "JDM.hpp"

JCLASS ConsoleExample : JPUBLIC JWINDOW {
JPRIVATE:
JPUBLIC:
    ConsoleExample() : JWINDOW("ConsoleExample", 105, 120, 5, 5) { }
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
