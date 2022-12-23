#pragma once

#include "Jinclude.h"
#include "JkeyBoard.h"

class JWINDOW
{
private:
    JCSHORT ScreenWidth, ScreenHeight;
    JBOOL Running = JTRUE;

    JCSTR WTitle;
    HANDLE originalConsole;
    HANDLE hConsole;
    HANDLE hConsoleI;
    SMALL_RECT screenBufferCorners;
    CONSOLE_SCREEN_BUFFER_INFOEX bufferInfo;

#if JEDITABLE
    DWORD PrevMode;
#endif
    CONSOLE_CURSOR_INFO CursorInfo;
    JTIMEPOINT timePoint1;
    JTIMEPOINT timePoint2;

protected:
    KeyBoard keyboard = KeyBoard();

public:
#if JGETMOUSEPOS
    POINT MousePos;
#endif
    CHAR_INFO *Screen;
    JFLOAT ElapseTime;

public:
    JVOID Start();
    JVOID SetColorIndex(JCSHORT Index, PixelRGB rgb);

    JVOID Draw(JCFLOAT x, JCFLOAT y, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawString(JCFLOAT x, JCFLOAT y, JCWSTR &str, JCBOOL AlphaR = JFALSE);
    JVOID DrawString(JCFLOAT x, JCFLOAT y, JCWCHAR str[], JCBOOL AlphaR = JFALSE);

    JVOID DrawCString(JCFLOAT x, JCFLOAT y, JCWSTR &str, JCBOOL AlphaR = JFALSE);
    JVOID DrawHorizontal(JCFLOAT x, JCFLOAT y, JCINT Width, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawVertical(JCFLOAT x, JCFLOAT y, JCINT Height, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawLine(JCFLOAT x1, JCFLOAT y1, JCFLOAT x2, JCFLOAT y2, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawTriangle(JCFLOAT x1, JCFLOAT y1, JCFLOAT x2, JCFLOAT y2, JCFLOAT x3, JCFLOAT y3, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawBox(JCINT width, JCINT height, JCFLOAT x, JCFLOAT y, JCSHORT Character = S1, JCSHORT Color = (FG_LWHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);

protected:
    JWINDOW(JCCHAR *Title, JCSHORT Width, JCSHORT Height, JCSHORT fontWidth = 5, JCSHORT fontHeight = 5);
    ~JWINDOW();
    virtual JBOOL onUserUpdate(JCFLOAT ElapseTime) = 0;
    virtual JBOOL onUserCreate() = 0;
    constexpr inline JSHORT GetWidth() { return this->ScreenWidth; }
    constexpr inline JSHORT GetHeight() { return this->ScreenHeight; }
    JVOID Clear(JCSHORT Character = S0, JCSHORT Color = (FG_BLACK | BG_BLACK));

private:
    JVOID SetConsoleWindowSize(HANDLE console, JCSHORT Width, JCSHORT Height, JCSHORT FontWidth, JCSHORT FontHeight);
    JBOOL gameLoop();
    constexpr inline Color getColor(JCSHORT Index) const
    {
        switch (Index)
        {
        case L'0':
            return FG_BLACK;
        case L'1':
            return FG_BLUE;
        case L'2':
            return FG_GREEN;
        case L'3':
            return FG_AQUA;
        case L'4':
            return FG_RED;
        case L'5':
            return FG_PURPLE;
        case L'6':
            return FG_YELLOW;
        case L'7':
            return FG_WHITE;
        case L'8':
            return FG_GRAY;
        case L'9':
            return FG_LBLUE;
        case L'A':
            return FG_LGREEN;
        case L'B':
            return FG_LAQUA;
        case L'C':
            return FG_LRED;
        case L'D':
            return FG_LPURPLE;
        case L'E':
            return FG_LYELLOW;
        default:
            return FG_LWHITE;
        }
    }
};