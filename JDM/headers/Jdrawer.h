#pragma once

#include "Jwindow.h"

class Drawer
{

public:
    static void DrawBoxHollow(Window *window, int width, int height, float x, float y, int thickness, wchar_t Character = S1, bool AlphaR = 0)
    {
        for (int px = x; px < width; px++)
            for (int py = y; py < y + thickness; py++)
                window->Draw(px, py, Character, AlphaR);

        for (int px = x; px < width; px++)
            for (int py = y + height - 1; py > y + height - 1 - thickness; py--)
                window->Draw(px, py, Character, AlphaR);

        for (int py = y; py < height; py++)
            for (int px = x; px < x + thickness; px++)
                window->Draw(px, py, Character, AlphaR);

        for (int py = x; py < height; py++)
            for (int px = x + width - 1; px > x + width - 1 - thickness; px--)
                window->Draw(px, py, Character, AlphaR);
    }

    static void DrawCircle(Window *window, float x, float y, int radius, wchar_t Character = S1, bool AlphaR = 0)
    {
        for (int h = 0; h < radius * 2; h++)
            for (int w = 0; w < radius * 2; w++)
            {
                int dx = radius - w;
                int dy = radius - h;
                if (!((dx * dx) + (dy * dy) >= (radius * radius)))
                    window->Draw(x + dx, y + dy, Character, AlphaR);
            }
    }
};
