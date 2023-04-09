#include "JDM.hpp"

JCLASS ConsoleExample : JPUBLIC JWINDOW {
JPRIVATE:

JPUBLIC:
    ConsoleExample() : JWINDOW("ConsoleExample", 100, 100, 5, 5) { }
    JBOOL onUserCreate() {
        JRETURN JTRUE;
    }
    JBOOL onUserUpdate() {
        Clear(BLANK, BG_BLACK);
        JRETURN JTRUE;
    }
};

JINT main() {
    JDM::SetRandomSeed();
    JMS<ConsoleExample>()->Start();
    JRETURN JFALSE;
}