#pragma once

#include "Jinclude.h"
#include "JkeyBoard.h"

// Main Window
class Window
{

private:
    JCSHORT ScreenWidth, ScreenHeight;
    JBOOL Running = JTRUE;

    JSTR WTitle;
    HANDLE originalConsole;
    HANDLE hConsole;
    HANDLE hConsoleI;
    SMALL_RECT screenBufferCorners;
    DWORD PrevMode;
    CONSOLE_CURSOR_INFO CursorInfo;

    std::chrono::_V2::system_clock::time_point timePoint1;
    std::chrono::_V2::system_clock::time_point timePoint2;

protected:
    KeyBoard keyboard = KeyBoard();

public:
    CHAR_INFO *Screen;
    JFLOAT ElapseTime;

public:
    Window(JCCHAR *Title, JCSHORT Width, JCSHORT Height, JCSHORT fontSize = 5);
    ~Window();

    virtual JBOOL onUserUpdate(JCFLOAT ElapseTime) = 0;
    virtual JBOOL onUserCreate() = 0;

    constexpr JSHORT GetWidth() { return this->ScreenWidth; }
    constexpr JSHORT GetHeight() { return this->ScreenHeight; }

    JVOID SetConsoleWindowSize(HANDLE console, JCSHORT Width, JCSHORT Height, JCSHORT FontWidth, JCSHORT FontHeight);
    JVOID Clear(JCSHORT Character = S0, JCSHORT Color = (FG_BLACK | BG_BLACK));
    JVOID Start();
    JBOOL gameLoop();

    constexpr JBOOL collide_point(JCFLOAT x, JCFLOAT y, JCINT width, JCINT height, JCFLOAT x1, JCFLOAT y1) const
    {
        return (x <= x1 && x1 <= x + width && y <= y1 && y1 <= y + height);
    }
    constexpr JBOOL collide_box(JCFLOAT x1, JCFLOAT y1, JCINT width1, JCINT height1,
                                JCFLOAT x2, JCFLOAT y2, JCINT width2, JCINT height2) const
    {
        if (x1 + width1 < x2)
            return JFALSE;
        if (x1 > x2 + width2)
            return JFALSE;
        if (y1 + height1 < y2)
            return JFALSE;
        if (y1 > y2 + height2)
            return JFALSE;
        return JTRUE;
    }
    Color getColor(JCSHORT Index);
    JVOID Draw(JCFLOAT x, JCFLOAT y, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawString(JCFLOAT x, JCFLOAT y, JCWSTR &str, JCBOOL AlphaR = JFALSE);
    JVOID DrawString(JCFLOAT x, JCFLOAT y, JCWCHAR str[], JCBOOL AlphaR = JFALSE);

    JVOID DrawCString(JCFLOAT x, JCFLOAT y, JCWSTR &str, JCBOOL AlphaR = JFALSE);
    JVOID DrawHorizontal(JCFLOAT x, JCFLOAT y, JCINT Width, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawVertical(JCFLOAT x, JCFLOAT y, JCINT Height, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawLine(JCFLOAT x1, JCFLOAT y1, JCFLOAT x2, JCFLOAT y2, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawTriangle(JCFLOAT x1, JCFLOAT y1, JCFLOAT x2, JCFLOAT y2, JCFLOAT x3, JCFLOAT y3, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);

    JVOID DrawBox(JCINT width, JCINT height, JCFLOAT x, JCFLOAT y, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
};