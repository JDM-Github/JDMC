# JDMC 1.2

### This is my framework when doing Console Games.

#### Inspired by [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine)

```c++
// Creating Console Window
#include "JDM.hpp"

JCLASS ConsoleExample : JPUBLIC JWINDOW {
JPRIVATE:
    JINT MapWidth = 20;
    JINT MapHeight = 20;
    JDM::Cell *Map;
    JVECTOR<JDM::Edges> VectorEdges;

JPUBLIC:
    ConsoleExample() : JWINDOW("ConsoleExample", 100, 100, 5, 5) { }
    JBOOL onUserCreate() {
        Map = JNEW JDM::Cell[MapWidth * MapHeight];
        JRETURN JTRUE;
    }

    JBOOL onUserUpdate() {
        Clear(BLANK, BG_BLACK);
        JIF (keyboard.Keys[Keys::J_MOUSE_LEFT].isReleased) {
            JINT Index = GetMouseIndex(5, MapWidth);
            Map[Index].Exist = !Map[Index].Exist;
        }

        ConvertTileMapToPolyMap(VectorEdges, Map, 0, 0, MapWidth, MapHeight, 5, MapWidth);
        Drawer::DisplayEdges(JTHIS, VectorEdges);

        JRETURN JTRUE;
    }
};

JINT main() {
    JDM::SetRandomSeed();
    JMS<ConsoleExample>()->Start();
    JRETURN JFALSE;
}


```
