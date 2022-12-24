#pragma once
#include "Jinclude.h"

JSTRUCT KeyState
{
    JBOOL isPressed = JFALSE;
    JBOOL isHeld = JFALSE;
    JBOOL isReleased = JFALSE;
};

JCONSTEXPR JBOOL isKeyHeld(JBOOL OldState, JBOOL NewState) { JRETURN(OldState && NewState); }
JCONSTEXPR JBOOL isKeyPressed(JBOOL OldState, JBOOL NewState) { JRETURN(!OldState && NewState); }
JCONSTEXPR JBOOL isKeyReleased(JBOOL OldState, JBOOL NewState) { JRETURN(OldState && !NewState); }

JCLASS KeyBoard
{
JPUBLIC:
    KeyState Keys[256];
    JBOOL KeyOldState[256] = {JFALSE};
    JBOOL KeyNewState[256] = {JFALSE};

JPUBLIC:
    KeyBoard() {}
    JVOID update()
    {
        JFOR(JINT i = 0; i < 256; i++)
        {
            KeyNewState[i] = GetAsyncKeyState(i);
            Keys[i].isHeld = isKeyHeld(KeyOldState[i], KeyNewState[i]);
            Keys[i].isPressed = isKeyPressed(KeyOldState[i], KeyNewState[i]);
            Keys[i].isReleased = isKeyReleased(KeyOldState[i], KeyNewState[i]);
            KeyOldState[i] = KeyNewState[i];
        }
    }
    KeyState getState(JCSHORT index)
    {
        JIF(index < 0 || index > 255)
        JRETURN KeyState();
        JRETURN Keys[index];
    }
};
