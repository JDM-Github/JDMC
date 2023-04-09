#pragma once

#include "Jwindow.hpp"

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
            JSTATIC JVOID DrawBoxHollowWH(JWINDOW * window, JCONST JDM::SizePosDF SizePosition, JCINT thicknessW, JCINT thicknessH,
                        JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE) {
                JFOR(JINT px = SizePosition.X; px < SizePosition.X + SizePosition.Width; px++)
                    JFOR(JINT py = SizePosition.Y; py < SizePosition.Y + thicknessH; py++)
                        window->Draw({JSTATICC<JFLOAT>(px), JSTATICC<JFLOAT>(py)}, Character, Color, AlphaR);
                JFOR(JINT px = SizePosition.X; px < SizePosition.X + SizePosition.Width; px++)
                    JFOR(JINT py = SizePosition.Y + SizePosition.Height - 1; py > SizePosition.Y + SizePosition.Height - 1 - thicknessH; py--)
                        window->Draw({JSTATICC<JFLOAT>(px), JSTATICC<JFLOAT>(py)}, Character, Color, AlphaR);
                JFOR(JINT py = SizePosition.Y; py < SizePosition.Y + SizePosition.Height; py++)
                    JFOR(JINT px = SizePosition.X; px < SizePosition.X + thicknessW; px++)
                        window->Draw({JSTATICC<JFLOAT>(px), JSTATICC<JFLOAT>(py)}, Character, Color, AlphaR);
                JFOR(JINT py = SizePosition.Y; py < SizePosition.Y + SizePosition.Height; py++)
                    JFOR(JINT px = SizePosition.X + SizePosition.Width - 1; px > SizePosition.X + SizePosition.Width - 1 - thicknessW; px--)
                        window->Draw({JSTATICC<JFLOAT>(px), JSTATICC<JFLOAT>(py)}, Character, Color, AlphaR);
            }
            JSTATIC JVOID DrawBoxHollowHV(JWINDOW * window, JCONST JDM::SizePosDF SizePosition, JCINT LEFT, JCINT RIGHT, JCINT UP, JCINT DOWN, 
                        JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE) {
                JFOR(JINT px = SizePosition.X; px < SizePosition.X + SizePosition.Width; px++)
                    JFOR(JINT py = SizePosition.Y; py < SizePosition.Y + UP; py++)
                        window->Draw({JSTATICC<JFLOAT>(px), JSTATICC<JFLOAT>(py)}, Character, Color, AlphaR);
                JFOR(JINT px = SizePosition.X; px < SizePosition.X + SizePosition.Width; px++)
                    JFOR(JINT py = SizePosition.Y + SizePosition.Height - 1; py > SizePosition.Y + SizePosition.Height - 1 - DOWN; py--)
                        window->Draw({JSTATICC<JFLOAT>(px), JSTATICC<JFLOAT>(py)}, Character, Color, AlphaR);
                JFOR(JINT py = SizePosition.Y; py < SizePosition.Y + SizePosition.Height; py++)
                    JFOR(JINT px = SizePosition.X; px < SizePosition.X + RIGHT; px++)
                        window->Draw({JSTATICC<JFLOAT>(px), JSTATICC<JFLOAT>(py)}, Character, Color, AlphaR);
                JFOR(JINT py = SizePosition.Y; py < SizePosition.Y + SizePosition.Height; py++)
                    JFOR(JINT px = SizePosition.X + SizePosition.Width - 1; px > SizePosition.X + SizePosition.Width - 1 - LEFT; px--)
                        window->Draw({JSTATICC<JFLOAT>(px), JSTATICC<JFLOAT>(py)}, Character, Color, AlphaR);
            }
            JSTATIC JVOID DrawCircle(JWINDOW *window, JCONST JDM::Pos2F Position, JCINT radius,
                JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE) {
                JFOR(JINT h = JNONE; h < radius * 2; h++)
                    JFOR(JINT w = JNONE; w < radius * 2; w++) {
                        JINT dx = radius - w;
                        JINT dy = radius - h;
                        JIF(!((dx * dx) + (dy * dy) >= (radius * radius)))
                            window->Draw({Position.X + radius + dx - 1, Position.Y + radius + dy - 1}, Character, Color, AlphaR);
                    }
            }
            JSTATIC JVOID DrawHallowCircle(JWINDOW *window, JCONST JDM::Pos2F Position, JCINT radius, JINT Thickness,
                JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE) {
                JFOR(JINT h = JNONE; h < radius * 2; h++)
                    JFOR(JINT w = JNONE; w < radius * 2; w++) {
                        JINT dx = radius - w;
                        JINT dy = radius - h;
                        JIF(!((dx * dx) + (dy * dy) >= (radius * radius)) &&
                            !((dx * dx) + (dy * dy) <= ((radius - Thickness) * (radius - Thickness))))
                            window->Draw({Position.X + radius + dx - 1, Position.Y + radius + dy - 1}, Character, Color, AlphaR);
                    }
            }
            JSTATIC JVOID DrawColoredHallowCircle(JWINDOW *window, JCONST JDM::Pos2F Position, JCINT radius, JINT Thickness,
                JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT OutColor =  (JDM::FG_WHITE | JDM::BG_BLACK), JCSHORT Color = (JDM::FG_GRAY | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE) {
                JFOR(JINT h = JNONE; h < radius * 2; h++)
                    JFOR(JINT w = JNONE; w < radius * 2; w++) {
                        JINT dx = radius - w;
                        JINT dy = radius - h;
                        JIF(!((dx * dx) + (dy * dy) >= (radius * radius)))
                            window->Draw({Position.X + radius + dx - 1, Position.Y + radius + dy - 1}, Character, Color, AlphaR);
                        JIF(!((dx * dx) + (dy * dy) >= (radius * radius)) &&
                            !((dx * dx) + (dy * dy) <= ((radius - Thickness) * (radius - Thickness))))
                            window->Draw({Position.X + radius + dx - 1, Position.Y + radius + dy - 1}, Character, OutColor, AlphaR);
                    }
            }
            JSTATIC JVOID DisplayEdges(JWINDOW *window, JVECTOR<JDM::Edges> VectorEdges, JCSHORT Color1 = JDM::FG_WHITE, JCSHORT Color2 = JDM::FG_RED) {
                JFOR (JAUTO &Edge : VectorEdges) {
                    window->DrawLine({Edge.SX, Edge.SY, Edge.EX, Edge.EY}, PIXEL_SOLID, Color2, JTRUE);
                    window->Draw({Edge.SX, Edge.SY}, PIXEL_SOLID, Color1);
                    window->Draw({Edge.EX, Edge.EY}, PIXEL_SOLID, Color1);
                }
            }
            JSTATIC JVOID DisplayPath(JWINDOW *window, JDM::Node *NodeEnd, JINT NodeSize) {
                JIF (NodeEnd != nullptr) {
                JDM::Node *P = NodeEnd;
                JWHILE (P->Parent != nullptr) {
                    window->DrawLine({JSTATICC<JFLOAT>(P->X * NodeSize) + NodeSize/2, JSTATICC<JFLOAT>(P->Y * NodeSize) + NodeSize/2,
                          JSTATICC<JFLOAT>((P->Parent->X) * NodeSize) + NodeSize/2, JSTATICC<JFLOAT>((P->Parent->Y) * NodeSize) + NodeSize/2},
                         PIXEL_SOLID, FG_YELLOW);
                    window->DrawLine({JSTATICC<JFLOAT>(P->X * NodeSize) + NodeSize/2, JSTATICC<JFLOAT>(P->Y * NodeSize) + NodeSize/2 - 1,
                          JSTATICC<JFLOAT>((P->Parent->X) * NodeSize) + NodeSize/2, JSTATICC<JFLOAT>((P->Parent->Y) * NodeSize) + NodeSize/2 - 1},
                         PIXEL_SOLID, FG_YELLOW);
                    P = P->Parent;
                }
            }
        }
    };
};