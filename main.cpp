#include "JDM.h"

JCLASS SpriteEditor : JPUBLIC JWINDOW
{
JPUBLIC:
    SpriteEditor() : JWINDOW("Game", 100, 50, 5, 5) {}
    JBOOL onUserCreate() { JRETURN JTRUE; }
    JBOOL onUserUpdate(JFLOAT ElapseTime)
    {
        Clear(S0, BG_CYAN);
        JRETURN JTRUE;
    } 
};

JINT main()
{
    JMS<SpriteEditor>()->Start();
    JRETURN JFALSE;
}
