#pragma once
#include "Jinclude.h"

JSTRUCT KeyState {
    JBOOL isPressed = JFALSE;
    JBOOL isHeld = JFALSE;
    JBOOL isReleased = JFALSE;
};
JCONSTEXPR JBOOL isKeyHeld(JBOOL OldState, JBOOL NewState) { JRETURN(OldState && NewState); }
JCONSTEXPR JBOOL isKeyPressed(JBOOL OldState, JBOOL NewState) { JRETURN(!OldState && NewState); }
JCONSTEXPR JBOOL isKeyReleased(JBOOL OldState, JBOOL NewState) { JRETURN(OldState && !NewState); }
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
