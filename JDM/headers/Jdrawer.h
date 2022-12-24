#pragma once

#include "Jwindow.h"

JNAMESPACE JDM
{
    JCLASS Drawer{

    JPUBLIC:
            JSTATIC JVOID DrawBoxHollow(JWINDOW * window, JCINT width, JCINT height, JCFLOAT x, JCFLOAT y, JCINT thickness, JCSHORT Character = S1, JCSHORT Color = (FG_WHITE | BG_BLACK), JCBOOL AlphaR = JFALSE){
            JFOR(JINT px = x; px < width; px++)
            JFOR(JINT py = y; py < y + thickness; py++)
            window->Draw(px, py, Character, Color, AlphaR);

            JFOR(JINT px = x; px < width; px++)
            JFOR(JINT py = y + height - 1; py > y + height - 1 - thickness; py--)
            window->Draw(px, py, Character, Color, AlphaR);

            JFOR(JINT py = y; py < height; py++)
            JFOR(JINT px = x; px < x + thickness; px++)
            window->Draw(px, py, Character, Color, AlphaR);

            JFOR(JINT py = x; py < height; py++)
            JFOR(JINT px = x + width - 1; px > x + width - 1 - thickness; px--)
            window->Draw(px, py, Character, Color, AlphaR);
}

    JSTATIC JVOID DrawCircle(JWINDOW *window, JCFLOAT x, JCFLOAT y, JCINT radius, JCSHORT Character = S1, JCSHORT Color = (FG_WHITE | BG_BLACK), JCBOOL AlphaR = JFALSE)
    {
        JFOR(JINT h = 0; h < radius * 2; h++)
        JFOR(JINT w = 0; w < radius * 2; w++)
        {
            JINT dx = radius - w;
            JINT dy = radius - h;
            JIF(!((dx * dx) + (dy * dy) >= (radius * radius)))
            window->Draw(x + dx, y + dy, Character, Color, AlphaR);
        }
    }
    }
;
}
;