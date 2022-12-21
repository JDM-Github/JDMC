#pragma once

#include "Jwindow.h"

class BoxEntity
{
public:
    JINT width, height;
    JFLOAT x, y;
    JWSTR StringDesign;
    JWSTR ColorDesign;

public:
    BoxEntity(JCINT w, JCINT h, JCFLOAT px, JCFLOAT py)
        : width(w), height(h), x(px), y(py) { this->FillDesign(); }
    BoxEntity() : width(10), height(10), x(0), y(0) { this->FillDesign(); }
    ~BoxEntity() {}

    constexpr JBOOL collide_point(JCFLOAT px, JCFLOAT py) const { return (this->x <= px && px <= this->x + this->width && this->y <= py && py <= this->y + this->height); }
    constexpr JBOOL collide_box(JCINT width, JCINT height, JCFLOAT px, JCFLOAT py) const
    {
        if (this->x + this->width < px)
            return JFALSE;
        if (this->x > px + width)
            return JFALSE;
        if (this->y + this->height < py)
            return JFALSE;
        if (this->y > py + height)
            return JFALSE;
        return JTRUE;
    }
    JVOID FillDesign(JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK))
    {
        this->StringDesign.clear();
        this->ColorDesign.clear();
        for (int r = 0; r < this->height; r++)
            for (int c = 0; c < this->width; c++)
            {
                this->StringDesign += Character;
                this->ColorDesign += Color;
            }
    }
    JVOID Render(Window *Window, JCBOOL AlphaR = JFALSE)
    {
        JINT x = (JINT)this->x;
        JINT y = (JINT)this->y;
        for (JINT r = 0; r < this->height; r++)
            for (JINT c = 0; c < this->width; c++)
                Window->Draw(x + c, y + r, this->StringDesign[r * this->width + c], this->ColorDesign[r * this->width + c], AlphaR);
    }
};
