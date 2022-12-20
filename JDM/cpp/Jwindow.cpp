#include "Jwindow.h"

void Window::Clear(const wchar_t Character, short color)
{
    for (int i = 0; i < ScreenHeight; i++)
        for (int j = 0; j < ScreenWidth; j++)
        {
            Screen[i * ScreenWidth + j].Char.UnicodeChar = Character;
            Screen[i * ScreenWidth + j].Attributes = color;
        }
}

Color Window::getColor(wchar_t index)
{
    switch (index)
    {
    case L'1':
        return FG_BLACK;
    case L'2':
        return FG_BLUE;
    case L'3':
        return FG_GREEN;
    case L'4':
        return FG_AQUA;
    case L'5':
        return FG_RED;
    case L'6':
        return FG_PURPLE;
    case L'7':
        return FG_YELLOW;
    case L'8':
        return FG_WHITE;
    case L'9':
        return FG_GRAY;
    case L'A':
        return FG_LBLUE;
    case L'B':
        return FG_LGREEN;
    case L'C':
        return FG_LAQUA;
    case L'D':
        return FG_LRED;
    case L'E':
        return FG_LPURPLE;
    case L'F':
        return FG_LYELLOW;
    default:
        return FG_LWHITE;
    }
}

void Window::DrawString(float x, float y, std::wstring &str, bool AlphaR)
{
    int x_adder = 0, y_adder = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == L'\n')
        {
            x_adder = 0;
            y_adder++;
            continue;
        }
        Draw(x + x_adder, y + y_adder, str[i], (FG_LWHITE | FG_BLACK), AlphaR);
        x_adder++;
    }
}

void Window::DrawCString(float x, float y, std::wstring &str, bool AlphaR)
{
    int x_adder = 0, y_adder = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == L'\n')
        {
            x_adder = 0;
            y_adder++;
            continue;
        }
        x_adder++;
        if (AlphaR && str[i] == L' ')
            continue;
        Draw(x + x_adder - 1, y + y_adder, S1, (getColor(str[i]) | BG_BLACK));
    }
}

void Window::DrawString(float x, float y, wchar_t str[], bool AlphaR)
{
    int x_adder = 0, y_adder = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == L'\n')
        {
            x_adder = 0;
            y_adder++;
            continue;
        }
        Draw(x + x_adder, y + y_adder, str[i], (FG_LWHITE | BG_BLACK), AlphaR);
        x_adder++;
    }
}

void Window::DrawHorizontal(float x, float y, int Width, wchar_t Character, short color, bool AlphaR)
{
    for (int i = (int)x; i < Width; i++)
        Draw(x + i, y, Character, color, AlphaR);
}

void Window::DrawVertical(float x, float y, int Height, wchar_t Character, short color, bool AlphaR)
{
    for (int i = (int)y; i < Height; i++)
        Draw(x, y + i, Character, color, AlphaR);
}

void Window::DrawLine(float x1, float y1, float x2, float y2, short Character, short color, bool AlphaR)
{
    float xCurrent = x1;
    float yCurrent = y1;

    // Get Distant
    float xDistant = (x1 > x2) ? (x1 - x2) : (x2 - x1);
    float yDistant = (y1 > y2) ? (y1 - y2) : (y2 - y1);

    // Pythagoream
    float distance = std::sqrt(xDistant * xDistant + yDistant * yDistant);
    // float approxTD = std::round(distance);

    // Get MAX Sample
    int numberSample = std::max(xDistant, yDistant);

    // Get The Delta of SAMPLE
    float samplePX = xDistant / numberSample;
    float samplePY = yDistant / numberSample;
    for (int i = 0; i < numberSample; i++)
    {
        Draw(xCurrent, yCurrent, Character, color, AlphaR);
        xCurrent += (x1 > x2) ? -samplePX : samplePX;
        yCurrent += (y1 > y2) ? -samplePY : samplePY;
    }
}

void Window::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, wchar_t Character, short color, bool AlphaR)
{
    DrawLine(x1, y1, x2, y2, Character, color, AlphaR);
    DrawLine(x2, y2, x3, y3, Character, color, AlphaR);
    DrawLine(x3, y3, x1, y1, Character, color, AlphaR);
}

void Window::DrawBox(int width, int height, float x, float y, short Character, short color, bool AlphaR)
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            Draw(x + j, y + i, Character, color, AlphaR);
}

void Window::Draw(float x, float y, short Character, short color, bool AlphaR)
{
    if ((int)x >= 0 && (int)x < ScreenWidth && (int)y >= 0 && (int)y < ScreenHeight)
    {
        if (AlphaR && Character == S0)
            return;
        Screen[ScreenWidth * (int)y + (int)x].Char.UnicodeChar = Character;
        Screen[ScreenWidth * (int)y + (int)x].Attributes = color;
    }
}