#pragma once
#include "Jinclude.h"

struct KeyState
{
    JBOOL isPressed = JFALSE;
    JBOOL isHeld = JFALSE;
    JBOOL isReleased = JFALSE;
};

constexpr JBOOL isKeyHeld(JBOOL OldState, JBOOL NewState) { return (OldState && NewState); }
constexpr JBOOL isKeyPressed(JBOOL OldState, JBOOL NewState) { return (!OldState && NewState); }
constexpr JBOOL isKeyReleased(JBOOL OldState, JBOOL NewState) { return (OldState && !NewState); }

class KeyBoard
{
public:
    KeyState Keys[256];
    JBOOL KeyOldState[256] = {JFALSE};
    JBOOL KeyNewState[256] = {JFALSE};

public:
    KeyBoard() {}
    JVOID update()
    {
        for (JINT i = 0; i < 256; i++)
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
        if (index < 0 || index > 255)
            return KeyState();
        return Keys[index];
    }
};
