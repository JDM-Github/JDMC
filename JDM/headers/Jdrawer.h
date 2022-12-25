#pragma once

#include "Jwindow.h"

JNAMESPACE JDM {
    JCLASS Drawer {
    JPUBLIC:
            JSTATIC JVOID DrawBoxHollow(JWINDOW * window, JCINT width, JCINT height, JCFLOAT x, JCFLOAT y, JCINT thickness,
                        JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE) {
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
            JSTATIC JVOID DrawCircle(JWINDOW *window, JCFLOAT x, JCFLOAT y, JCINT radius,
                    JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE) {
                JFOR(JINT h = JNONE; h < radius * 2; h++)
                    JFOR(JINT w = JNONE; w < radius * 2; w++) {
                        JINT dx = radius - w;
                        JINT dy = radius - h;
                        JIF(!((dx * dx) + (dy * dy) >= (radius * radius)))
                            window->Draw(x + dx, y + dy, Character, Color, AlphaR);
                    }
            }
    };
};