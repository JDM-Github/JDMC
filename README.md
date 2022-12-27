# JDMC 1.0

### This is my framework when doing Console Games.

#### Inspired by [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine)

```c++
// Creating Console Window
#include "JDM.h"

JCLASS ConsoleExample : JPUBLIC JWINDOW {

JPRIVATE:
JPUBLIC:
    ConsoleExample() : JWINDOW("ConsoleExample", 200, 120, 5, 5) { }
    JBOOL onUserCreate() {
        JRETURN JTRUE;
    }

    JBOOL onUserUpdate(JFLOAT ElapseTime) {
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

```
