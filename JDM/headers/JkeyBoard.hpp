#pragma once
#include "Jinclude.hpp"

JCLASS KeyBoard {
JPUBLIC:
    KeyState Keys       [JMAX_HEX+1];
    JBOOL KeyOldState   [JMAX_HEX+1] = {JFALSE};
    JBOOL KeyNewState   [JMAX_HEX+1] = {JFALSE};

JPUBLIC:
    KeyBoard() {}
    JVOID update() {
        JFOR(JINT i = JNONE; i <= JMAX_HEX; i++) {
            KeyNewState[i] = GetAsyncKeyState(i);
            Keys[i].isHeld = isKeyHeld(KeyOldState[i], KeyNewState[i]);
            Keys[i].isPressed = isKeyPressed(KeyOldState[i], KeyNewState[i]);
            Keys[i].isReleased = isKeyReleased(KeyOldState[i], KeyNewState[i]);
            KeyOldState[i] = KeyNewState[i];
        }
    }
    KeyState getState(JCSHORT index) {
        JIF(index < JNONE || index > JMAX_HEX)
        JRETURN KeyState();
        JRETURN Keys[index];
    }
};
