#pragma once

#include "Jwindow.h"

class Drawer
{

public:
    static JVOID DrawBoxHollow(Window *window, JCINT width, JCINT height, JCFLOAT x, JCFLOAT y, JCINT thickness, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE)
    {
        for (JINT px = x; px < width; px++)
            for (JINT py = y; py < y + thickness; py++)
                window->Draw(px, py, Character, Color, AlphaR);

        for (JINT px = x; px < width; px++)
            for (JINT py = y + height - 1; py > y + height - 1 - thickness; py--)
                window->Draw(px, py, Character, Color, AlphaR);

        for (JINT py = y; py < height; py++)
            for (JINT px = x; px < x + thickness; px++)
                window->Draw(px, py, Character, Color, AlphaR);

        for (JINT py = x; py < height; py++)
            for (JINT px = x + width - 1; px > x + width - 1 - thickness; px--)
                window->Draw(px, py, Character, Color, AlphaR);
    }

    static JVOID DrawCircle(Window *window, JCFLOAT x, JCFLOAT y, JCINT radius, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE)
    {
        for (JINT h = 0; h < radius * 2; h++)
            for (JINT w = 0; w < radius * 2; w++)
            {
                JINT dx = radius - w;
                JINT dy = radius - h;
                if (!((dx * dx) + (dy * dy) >= (radius * radius)))
                    window->Draw(x + dx, y + dy, Character, Color, AlphaR);
            }
    }
};
