#pragma once
#ifndef __WINDOWH__
#define __WINDOWH__

#include "Jinclude.hpp"
#include "Jenums.hpp"
#include "JkeyBoard.hpp"
#include <fstream>

JCLASS JWINDOW {
JPRIVATE:
    JCSHORT ScreenWidth, ScreenHeight;
    JBOOL Running = JTRUE;
    JCSTR WTitle;
    HANDLE originalConsole;
    HANDLE hConsole;
    HANDLE hConsoleI;
    SMALL_RECT screenBufferCorners;
    CONSOLE_SCREEN_BUFFER_INFOEX bufferInfo;
    JCSHORT FontWidth, FontHeight;

    DWORD PrevMode;
    CONSOLE_CURSOR_INFO CursorInfo;
    JTIMEPOINT timePoint1;
    JTIMEPOINT timePoint2;

JPUBLIC:
    KeyBoard keyboard = KeyBoard();
    POINT MousePos;
    JDM::Pos2D ExactMousePos = { 0, 0 };

    CHAR_INFO *Screen;
    JFLOAT ElapseTime;

JPUBLIC:
    JVOID Start();
    JVOID SetColorIndex(JCSHORT Index, JDM::PixelRGB rgb);
    JVOID Draw(JCONST JDM::Pos2F Position, JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawCycle(JCONST JDM::Pos2F Position, JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawCStringCycle(JCONST JDM::Pos2F Position, JCWSTR &str, JCBOOL AlphaR = JFALSE);

    JVOID DrawString(JCONST JDM::Pos2F Position, JCWSTR &str, JCSHORT Color, JCBOOL AlphaR = JFALSE);
    JVOID DrawACString(JCONST JDM::Pos2F Position, JCWSTR &str, JCSHORT Character, JCSHORT Color);
    JVOID DrawString(JCONST JDM::Pos2F Position, JCWCHAR str[], JCSHORT Color, JCBOOL AlphaR = JFALSE);
    JVOID DrawCString(JCONST JDM::Pos2F Position, JCWSTR &str, JCBOOL AlphaR = JFALSE);

    JVOID DrawHorizontal(JCONST JDM::Pos2F Position, JCINT Width, JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawVertical(JCONST JDM::Pos2F Position, JCINT Height, JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawLine(JCONST JDM::Pos4F Position, JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawTriangle(JCONST JDM::Pos6F Position, JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE);
    JVOID DrawBox(JCONST JDM::SizePosDF SizePosition, JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE);

    JVOID GetSpriteString(JWSTR &string, JCCHAR *spriteName) {
        std::fstream File(spriteName, std::ios::in);
        assert(File);
        string.clear();
        JBOOL Start = JFALSE;
        JBOOL CWidth = JFALSE;
        JINT Navigate = 1;
        JSTR WidthStr;
        JCHAR Character;
        JINT LineNav = 0;
        JINT Width = 0;
        JWHILE (JTRUE) {
		    File >> Character;
		    JIF (Start && Character == '}') JBREAK;
            JIF (Start && Character != '}') {
                JIF (Navigate > Width) {
                    string += '\n';
                    Navigate = 1;
                }
                string += (Character == 'S') ? ' ' : Character;
                Navigate++;
                JCONTINUE;
            }
            JELSE JIF (Character == '{') {
                Width = std::stoi(WidthStr);
                Start = JTRUE; JCONTINUE;
            }
            JELSE JIF (Character != '\r') {
                JIF (CWidth || (LineNav == 0 && Character == ':')) {
                    JIF(!CWidth) CWidth = JTRUE;
                    JELSE WidthStr += Character;
                } JCONTINUE;
            } JELSE {
                CWidth = JFALSE;
                LineNav = 1;
            }
            Start = JFALSE;
        }
        File.close();
    }

    JCONSTEXPR JINT GetMouseX() { JRETURN JTHIS->MousePos.x / JTHIS->FontWidth; }
    JCONSTEXPR JINT GetMouseY() { JRETURN JTHIS->MousePos.y / JTHIS->FontHeight; }

    JCONSTEXPR JDM::Color getColor(JCSHORT Index) JCONST {
        JSWITCH (Index) {
            JCASE L'0': JRETURN JDM::FG_BLACK;
            JCASE L'1': JRETURN JDM::FG_BLUE;
            JCASE L'2': JRETURN JDM::FG_GREEN;
            JCASE L'3': JRETURN JDM::FG_CYAN;
            JCASE L'4': JRETURN JDM::FG_RED;
            JCASE L'5': JRETURN JDM::FG_MAGENTA;
            JCASE L'6': JRETURN JDM::FG_YELLOW;
            JCASE L'7': JRETURN JDM::FG_GRAY;
            JCASE L'8': JRETURN JDM::FG_DARK_GRAY;
            JCASE L'9': JRETURN JDM::FG_DARK_BLUE;
            JCASE L'A': JRETURN JDM::FG_DARK_GREEN;
            JCASE L'B': JRETURN JDM::FG_DARK_CYAN;
            JCASE L'C': JRETURN JDM::FG_DARK_RED;
            JCASE L'D': JRETURN JDM::FG_SKIN;
            JCASE L'E': JRETURN JDM::FG_DARK_SKIN;
            JDEFAULT  : JRETURN JDM::FG_WHITE;
        }
    }

JPROTECTED:
    JWINDOW(JCCHAR *Title, JCSHORT Width, JCSHORT Height, JCSHORT fontWidth = 5, JCSHORT fontHeight = 5);
    ~JWINDOW();
    JVIRTUAL JBOOL onUserUpdate() = 0;
    JVIRTUAL JBOOL onUserCreate() = 0;
    JCONSTEXPR JSHORT GetWidth() JCONST { JRETURN JTHIS->ScreenWidth; }
    JCONSTEXPR JSHORT GetHeight() JCONST { JRETURN JTHIS->ScreenHeight; }
    JVOID Clear(JCSHORT Character = JDM::BLANK, JCSHORT Color = (JDM::FG_BLACK | JDM::BG_BLACK));
    JCONSTEXPR JINT GetMouseIndex(JINT BlockWidth, JINT Pitch) { JRETURN (GetMouseY() / BlockWidth) * Pitch + (GetMouseX() / BlockWidth); }

JPRIVATE:
    JVOID SetConsoleWindowSize(HANDLE console, JCSHORT Width, JCSHORT Height, JCSHORT FontWidth, JCSHORT FontHeight);
    JBOOL SetupWindow();
    JBOOL gameLoop();

};

#endif