#include "JDM.h"

JCLASS SnakeAI : JPUBLIC JWINDOW {

JPRIVATE:
JPUBLIC:
    SnakeAI() : JWINDOW("Snake AI", 140, 100, 5, 5) {}
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
    srand(std::time(0));
    JMS<SnakeAI>()->Start();
    JRETURN JFALSE;
}
