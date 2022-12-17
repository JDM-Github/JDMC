#pragma once

#include "Jwindow.h"

class BoxEntity
{
public:
    int width, height;
    float x_pos, y_pos;
    std::wstring design;

public:
    BoxEntity(int w, int h, float x, float y)
        : width(w), height(h), x_pos(x), y_pos(y) { fill_design(); }
    ~BoxEntity() {}

    constexpr bool collide_point(const float x, const float y) { return (x_pos <= x && x <= x_pos + width && y_pos <= y && y <= y_pos + height); }
    constexpr bool collide_box(const int width, const int height, const float x, const float y)
    {
        if (this->x_pos + this->width < x)
            return 0;
        if (this->x_pos > x + width)
            return 0;
        if (this->y_pos + this->height < y)
            return 0;
        if (this->y_pos > y + height)
            return 0;
        return 1;
    }
    void fill_design(wchar_t character = PIXEL_SOLID1)
    {
        this->design.clear();
        for (int r = 0; r < this->height; r++)
            for (int c = 0; c < this->width; c++)
                this->design += character;
    }
    void render(wchar_t *Screen, const uint16_t Width, const uint16_t Height, bool AlphaR = 0)
    {
        int x = (int)this->x_pos;
        int y = (int)this->y_pos;
        for (int r = 0; r < this->height; r++)
            for (int c = 0; c < this->width; c++)
            {
                if (x + c >= Width || x + c < 0 || y + r >= Height || y + r < 0 || (this->design[r * this->width + c] == PIXEL_NONE && AlphaR))
                    continue;
                Screen[((y + r) * Width) + c + x] = this->design[r * this->width + c];
            }
    }
};
