# JDMC 1.0

### This is my framework when doing Console Games.

#### Inspired by [OLCGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine)

```c++
// Creating Console Window
#include "JDM.h"

JCLASS ConsoleExample : JPUBLIC JWINDOW
{
JPUBLIC:
    ConsoleExample() : JWINDOW("Game", 100, 50, 5, 5) {}
    JBOOL onUserCreate() { JRETURN JTRUE; }
    JBOOL onUserUpdate(JFLOAT ElapseTime)
    {
        Clear(S0, BG_CYAN);
        JRETURN JTRUE;
    }
};

JINT main()
{
    JMS<ConsoleExample>()->Start();
    JRETURN JFALSE;
}
```
