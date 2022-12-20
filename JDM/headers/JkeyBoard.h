#pragma once
#include "Jinclude.h"

struct KeyState
{
    bool isPressed = false;
    bool isHeld = false;
    bool isReleased = false;
};

constexpr bool isKeyHeld(bool OldState, bool NewState) { return (OldState && NewState); }
constexpr bool isKeyPressed(bool OldState, bool NewState) { return (!OldState && NewState); }
constexpr bool isKeyReleased(bool OldState, bool NewState) { return (OldState && !NewState); }

class KeyBoard
{
public:
    KeyState Keys[256];
    bool KeyOldState[256] = {false};
    bool KeyNewState[256] = {false};

public:
    KeyBoard() {}

    void update()
    {
        for (int i = 0; i < 256; i++)
        {
            KeyNewState[i] = GetAsyncKeyState(i);
            Keys[i].isHeld = isKeyHeld(KeyOldState[i], KeyNewState[i]);
            Keys[i].isPressed = isKeyPressed(KeyOldState[i], KeyNewState[i]);
            Keys[i].isReleased = isKeyReleased(KeyOldState[i], KeyNewState[i]);
            KeyOldState[i] = KeyNewState[i];
        }
    }

    KeyState getState(short index)
    {
        if (index < 0 || index > 255)
            return KeyState();
        return Keys[index];
    }
};
