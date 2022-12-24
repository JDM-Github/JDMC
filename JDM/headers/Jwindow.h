#pragma once

#ifndef __WINDOWH__
#define __WINDOWH__

#include "Jinclude.h"
#include "JkeyBoard.h"

JCLASS JWINDOW
{
JPRIVATE:
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

JPROTECTED:
    KeyBoard keyboard = KeyBoard();

JPUBLIC:
#if JGETMOUSEPOS
    POINT MousePos;
#endif
    CHAR_INFO *Screen;
    JFLOAT ElapseTime;

JPUBLIC:
    JVOID Start();
    JVOID SetColorIndex(JCSHORT Index, PixelRGB rgb);

    JVOID Draw(JCFLOAT x, JCFLOAT y, JCSHORT Character = S1, JCSHORT Color = (FG_WHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawString(JCFLOAT x, JCFLOAT y, JCWSTR &str, JCBOOL AlphaR = JFALSE);
    JVOID DrawString(JCFLOAT x, JCFLOAT y, JCWCHAR str[], JCBOOL AlphaR = JFALSE);

    JVOID DrawCString(JCFLOAT x, JCFLOAT y, JCWSTR &str, JCBOOL AlphaR = JFALSE);
    JVOID DrawHorizontal(JCFLOAT x, JCFLOAT y, JCINT Width, JCSHORT Character = S1, JCSHORT Color = (FG_WHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawVertical(JCFLOAT x, JCFLOAT y, JCINT Height, JCSHORT Character = S1, JCSHORT Color = (FG_WHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawLine(JCFLOAT x1, JCFLOAT y1, JCFLOAT x2, JCFLOAT y2, JCSHORT Character = S1, JCSHORT Color = (FG_WHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawTriangle(JCFLOAT x1, JCFLOAT y1, JCFLOAT x2, JCFLOAT y2, JCFLOAT x3, JCFLOAT y3, JCSHORT Character = S1, JCSHORT Color = (FG_WHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawBox(JCINT width, JCINT height, JCFLOAT x, JCFLOAT y, JCSHORT Character = S1, JCSHORT Color = (FG_WHITE | BG_BLACK), JCBOOL AlphaR = JFALSE);

JPROTECTED:
    JWINDOW(JCCHAR *Title, JCSHORT Width, JCSHORT Height, JCSHORT fontWidth = 5, JCSHORT fontHeight = 5);
    ~JWINDOW();
    JVIRTUAL JBOOL onUserUpdate(JCFLOAT ElapseTime) = 0;
    JVIRTUAL JBOOL onUserCreate() = 0;
    JCONSTEXPR JSHORT GetWidth() JCONST { JRETURN JTHIS->ScreenWidth; }
    JCONSTEXPR JSHORT GetHeight() JCONST { JRETURN JTHIS->ScreenHeight; }
    JVOID Clear(JCSHORT Character = S0, JCSHORT Color = (FG_BLACK | BG_BLACK));

JPRIVATE:
    JVOID SetConsoleWindowSize(HANDLE console, JCSHORT Width, JCSHORT Height, JCSHORT FontWidth, JCSHORT FontHeight);
    JBOOL SetupWindow();
    JBOOL gameLoop();
    JCONSTEXPR Color getColor(JCSHORT Index) JCONST
    {
        JSWITCH (Index)
        {
        JCASE L'0': JRETURN FG_BLACK;
        JCASE L'1': JRETURN FG_BLUE;
        JCASE L'2': JRETURN FG_GREEN;
        JCASE L'3': JRETURN FG_CYAN;
        JCASE L'4': JRETURN FG_RED;
        JCASE L'5': JRETURN FG_MAGENTA;
        JCASE L'6': JRETURN FG_YELLOW;
        JCASE L'7': JRETURN FG_GRAY;
        JCASE L'8': JRETURN FG_DARK_GRAY;
        JCASE L'9': JRETURN FG_DARK_BLUE;
        JCASE L'A': JRETURN FG_DARK_GREEN;
        JCASE L'B': JRETURN FG_DARK_CYAN;
        JCASE L'C': JRETURN FG_DARK_RED;
        JCASE L'D': JRETURN FG_DARK_MAGENTA;
        JCASE L'E': JRETURN FG_DARK_YELLOW;
        JDEFAULT: JRETURN FG_WHITE;
        }
    }
};

#endif