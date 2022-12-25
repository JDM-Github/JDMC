#pragma once

#include "Jwindow.h"

JNAMESPACE JDM {
    JCLASS Drawer {
    JPUBLIC:
            JSTATIC JVOID DrawBoxHollow(JWINDOW * window, JCONST JDM::SizePosDF SizePosition, JCINT thickness,
                        JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE) {
                JFOR(JINT px = SizePosition.X; px < SizePosition.X + SizePosition.Width; px++)
                    JFOR(JINT py = SizePosition.Y; py < SizePosition.Y + thickness; py++)
                        window->Draw({JSTATICC<JFLOAT>(px), JSTATICC<JFLOAT>(py)}, Character, Color, AlphaR);
                JFOR(JINT px = SizePosition.X; px < SizePosition.X + SizePosition.Width; px++)
                    JFOR(JINT py = SizePosition.Y + SizePosition.Height - 1; py > SizePosition.Y + SizePosition.Height - 1 - thickness; py--)
                        window->Draw({JSTATICC<JFLOAT>(px), JSTATICC<JFLOAT>(py)}, Character, Color, AlphaR);
                JFOR(JINT py = SizePosition.Y; py < SizePosition.Y + SizePosition.Height; py++)
                    JFOR(JINT px = SizePosition.X; px < SizePosition.X + thickness; px++)
                        window->Draw({JSTATICC<JFLOAT>(px), JSTATICC<JFLOAT>(py)}, Character, Color, AlphaR);
                JFOR(JINT py = SizePosition.Y; py < SizePosition.Y + SizePosition.Height; py++)
                    JFOR(JINT px = SizePosition.X + SizePosition.Width - 1; px > SizePosition.X + SizePosition.Width - 1 - thickness; px--)
                        window->Draw({JSTATICC<JFLOAT>(px), JSTATICC<JFLOAT>(py)}, Character, Color, AlphaR);
            }
            JSTATIC JVOID DrawCircle(JWINDOW *window, JCONST JDM::Pos2F Position, JCINT radius,
                JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE) {
                JFOR(JINT h = JNONE; h < radius * 2; h++)
                    JFOR(JINT w = JNONE; w < radius * 2; w++) {
                        JINT dx = radius - w;
                        JINT dy = radius - h;
                        JIF(!((dx * dx) + (dy * dy) >= (radius * radius)))
                            window->Draw({Position.X + dx, Position.Y + dy}, Character, Color, AlphaR);
                    }
            }
    };
};