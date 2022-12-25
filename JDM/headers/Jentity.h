#pragma once

#include "Jwindow.h"

JCLASS BoxEntity {
JPUBLIC:
    JINT width, height;
    JFLOAT x, y;
    JWSTR StringDesign;
    JWSTR ColorDesign;

JPUBLIC:
    BoxEntity(JCINT w, JCINT h, JCFLOAT px, JCFLOAT py)
        : width(w), height(h), x(px), y(py) { JTHIS->FillDesign(); }
    BoxEntity() : width(10), height(10), x(0), y(0) { JTHIS->FillDesign(); }
    ~BoxEntity() {}

    JCONSTEXPR JBOOL collide_point(JCFLOAT px, JCFLOAT py) JCONST {
        JRETURN(JTHIS->x <= px && px <= JTHIS->x + JTHIS->width && JTHIS->y <= py && py <= JTHIS->y + JTHIS->height); }
    JCONSTEXPR JBOOL collide_box(JCINT width, JCINT height, JCFLOAT px, JCFLOAT py) JCONST {
        JIF(JTHIS->x + JTHIS->width < px) JRETURN JFALSE;
        JIF(JTHIS->x > px + width) JRETURN JFALSE;
        JIF(JTHIS->y + JTHIS->height < py) JRETURN JFALSE;
        JIF(JTHIS->y > py + height) JRETURN JFALSE;
        JRETURN JTRUE;
    }
    JVOID FillDesign(JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK)) {
        JTHIS->StringDesign.clear();
        JTHIS->ColorDesign.clear();
        JFOR(JINT r = JNONE; r < JTHIS->height; r++)
            JFOR(JINT c = JNONE; c < JTHIS->width; c++) {
                JTHIS->StringDesign += Character;
                JTHIS->ColorDesign += Color;
        }
    }
    JVOID Render(JWINDOW *Window, JCBOOL AlphaR = JFALSE) {
        JINT x = (JINT)JTHIS->x;
        JINT y = (JINT)JTHIS->y;
        JFOR(JINT r = JNONE; r < JTHIS->height; r++)
            JFOR(JINT c = JNONE; c < JTHIS->width; c++)
                Window->Draw(x + c, y + r, JTHIS->StringDesign[r * JTHIS->width + c], JTHIS->ColorDesign[r * JTHIS->width + c], AlphaR);
    }
    JVOID RenderC(JWINDOW *Window, JCSHORT Color = JDM::FG_WHITE, JCBOOL AlphaR = JFALSE)
    {
        JINT x = (JINT)JTHIS->x;
        JINT y = (JINT)JTHIS->y;
            JFOR(JINT r = JNONE; r < JTHIS->height; r++)
                JFOR(JINT c = JNONE; c < JTHIS->width; c++)
                    Window->Draw(x + c, y + r, JTHIS->StringDesign[r * JTHIS->width + c], Color, AlphaR);
    }
    JVOID RenderA(JWINDOW *Window, JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE)
    {
        JINT x = (JINT)JTHIS->x;
        JINT y = (JINT)JTHIS->y;
        JFOR(JINT r = JNONE; r < JTHIS->height; r++)
            JFOR(JINT c = JNONE; c < JTHIS->width; c++)
                JIF(JTHIS->StringDesign[r * JTHIS->width + c] != L' ')
                Window->Draw(x + c, y + r, Character, Color, AlphaR);
    }
};
