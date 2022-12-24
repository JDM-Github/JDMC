#include "Jwindow.h"

JWINDOW::JWINDOW(JCCHAR *Title, JCSHORT Width, JCSHORT Height, JCSHORT fontWidth, JCSHORT fontHeight)
    : WTitle(Title), ScreenWidth(std::min(Width, (JSHORT)(JSWMAX / fontWidth))), ScreenHeight(std::min(Height, (JSHORT)(JSHMAX / fontHeight)))
{
    JTHIS->originalConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    JTHIS->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    JTHIS->hConsoleI = GetStdHandle(STD_INPUT_HANDLE);
    JTHIS->bufferInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    assert(SetConsoleActiveScreenBuffer(JTHIS->hConsole));
    assert(JTHIS->SetupWindow());
    MoveWindow(GetConsoleWindow(), 0, 0, 0, 0, JTRUE);

#if JEDITABLE
    GetConsoleMode(JTHIS->hConsoleI, &JTHIS->PrevMode);
    SetConsoleMode(JTHIS->hConsoleI, ENABLE_EXTENDED_FLAGS | (JTHIS->PrevMode & ~ENABLE_QUICK_EDIT_MODE));
#endif
    SetConsoleWindowSize(JTHIS->hConsole, ScreenWidth, ScreenHeight, fontWidth, fontHeight);
    ShowScrollBar(GetConsoleWindow(), SB_VERT, JFALSE);

    GetConsoleCursorInfo(JTHIS->hConsole, &JTHIS->CursorInfo);
    JTHIS->CursorInfo.dwSize = JFALSE;
    JTHIS->CursorInfo.bVisible = JFALSE;
    SetConsoleCursorInfo(JTHIS->hConsole, &JTHIS->CursorInfo);
    GetConsoleScreenBufferInfoEx(JTHIS->hConsole, &bufferInfo);
    JTHIS->Screen = JNEW CHAR_INFO[ScreenWidth * ScreenHeight];
}

JWINDOW::~JWINDOW()
{
    Clear();
    SetConsoleWindowSize(JTHIS->originalConsole, 120, 50, 6, 10);
    SetConsoleActiveScreenBuffer(JTHIS->originalConsole);
    WriteConsoleOutputW(JTHIS->originalConsole, JTHIS->Screen, {JTHIS->GetWidth(), JTHIS->GetHeight()}, {0, 0}, &JTHIS->screenBufferCorners);
    ShowScrollBar(GetConsoleWindow(), SB_VERT, JTRUE);
    SetConsoleCursorPosition(JTHIS->originalConsole, {0, 0});
    SetConsoleMode(JTHIS->hConsoleI, JTHIS->PrevMode);

    JTHIS->CursorInfo.bVisible = JTRUE;
    SetConsoleCursorInfo(JTHIS->hConsole, &JTHIS->CursorInfo);
    SetConsoleTextAttribute(JTHIS->originalConsole, FG_WHITE | BG_BLACK);
    JDELETE[] JTHIS->Screen;
}

JVOID JWINDOW::SetConsoleWindowSize(HANDLE console, JCSHORT Width, JCSHORT Height, JCSHORT FontWidth, JCSHORT FontHeight)
{
    JTHIS->screenBufferCorners = {0, 0, 1, 1};
    SetConsoleWindowInfo(console, JTRUE, &JTHIS->screenBufferCorners);
    assert(SetConsoleScreenBufferSize(console, {Width, Height}));
    assert(SetConsoleActiveScreenBuffer(console));

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = FontWidth;
    cfi.dwFontSize.Y = FontHeight;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Lucida Console");
    assert(SetCurrentConsoleFontEx(console, JFALSE, &cfi));

    JTHIS->screenBufferCorners = {0, 0, (JSHORT)(Width - 1), (JSHORT)(Height - 1)};
    assert(SetConsoleWindowInfo(console, JTRUE, &JTHIS->screenBufferCorners));
}

JVOID JWINDOW::Start()
{
    assert(JTHIS->onUserCreate());
    srand(std::time(0));
    JTHIS->timePoint1 = std::chrono::system_clock::now();
    JTHIS->timePoint2 = std::chrono::system_clock::now();
    JRUNNING(JTHIS->Running)
    JTHIS->Running = JTHIS->gameLoop();
}

JBOOL JWINDOW::SetupWindow()
{
#if JSET_COLOR
    SetColorIndex(0x0, COLORINDEX0);
    SetColorIndex(0x1, COLORINDEX1);
    SetColorIndex(0x2, COLORINDEX2);
    SetColorIndex(0x3, COLORINDEX3);
    SetColorIndex(0x4, COLORINDEX4);
    SetColorIndex(0x5, COLORINDEX5);
    SetColorIndex(0x6, COLORINDEX6);
    SetColorIndex(0x7, COLORINDEX7);
    SetColorIndex(0x8, COLORINDEX8);
    SetColorIndex(0x9, COLORINDEX9);
    SetColorIndex(0xA, COLORINDEXA);
    SetColorIndex(0xB, COLORINDEXB);
    SetColorIndex(0xC, COLORINDEXC);
    SetColorIndex(0xD, COLORINDEXD);
    SetColorIndex(0xE, COLORINDEXE);
    SetColorIndex(0xF, COLORINDEXF);
#endif
    return JTRUE;
}

JBOOL JWINDOW::gameLoop()
{
    JTHIS->timePoint2 = std::chrono::system_clock::now();
    std::chrono::duration<JFLOAT> elapseTime = JTHIS->timePoint2 - JTHIS->timePoint1;
    JTHIS->timePoint1 = JTHIS->timePoint2;

    JTHIS->ElapseTime = elapseTime.count();
    JIF(JTHIS->onUserUpdate(JTHIS->ElapseTime))
    {
#if JGETMOUSEPOS
        GetCursorPos(&JTHIS->MousePos);
        ScreenToClient(GetConsoleWindow(), &JTHIS->MousePos);
#endif
        JTHIS->keyboard.update();
#if JESCTOEXIT
        JIF(keyboard.Keys[Keys::J_ESC].isReleased)
        JRETURN JFALSE;
#endif
        JWCHAR updater[256];
        swprintf(updater, 256, L"JDMC: JDMaster Console Framework:    %s - FPS: %4.2f",
                 JTHIS->WTitle.c_str(),
                 (JSHOWFPS) ? 1.0 / JTHIS->ElapseTime : 0);
        SetConsoleTitleW(updater);
        WriteConsoleOutputW(JTHIS->hConsole, JTHIS->Screen, {JTHIS->GetWidth(), JTHIS->GetHeight()}, {0, 0}, &JTHIS->screenBufferCorners);
        JRETURN JTRUE;
    }
    JRETURN JFALSE;
}

JVOID JWINDOW::Clear(JCSHORT Character, JCSHORT Color)
{
    JFOR(JSHORT i = 0; i < JTHIS->GetHeight(); i++)
    JFOR(JSHORT j = 0; j < JTHIS->GetWidth(); j++)
    {
        JTHIS->Screen[i * JTHIS->GetWidth() + j].Char.UnicodeChar = Character;
        JTHIS->Screen[i * JTHIS->GetWidth() + j].Attributes = Color;
    }
}
JVOID JWINDOW::SetColorIndex(JCSHORT Index, PixelRGB rgb)
{
    JTHIS->bufferInfo.ColorTable[Index] = RGB(rgb.R, rgb.G, rgb.B);
    JTHIS->bufferInfo.ColorTable[Index];
    SetConsoleScreenBufferInfoEx(JTHIS->hConsole, &JTHIS->bufferInfo);
}
JVOID JWINDOW::DrawString(JCFLOAT x, JCFLOAT y, JCWSTR &str, JCBOOL AlphaR)
{
    JSHORT x_adder = 0, y_adder = 0;
    JFOR(JSHORT i = 0; i < str.size(); i++)
    {
        JIF(str[i] == L'\n')
        {
            x_adder = 0;
            y_adder++;
            continue;
        }
        JTHIS->Draw(x + x_adder, y + y_adder, str[i], (FG_WHITE | FG_BLACK), AlphaR);
        x_adder++;
    }
}

JVOID JWINDOW::DrawCString(JCFLOAT x, JCFLOAT y, JCWSTR &str, JCBOOL AlphaR)
{
    JSHORT x_adder = 0, y_adder = 0;
    JFOR(JSHORT i = 0; i < str.size(); i++)
    {
        JIF(str[i] == L'\n')
        {
            x_adder = 0;
            y_adder++;
            JCONTINUE;
        }
        x_adder++;
        JIF(AlphaR && str[i] == L' ')
        JCONTINUE;
        JTHIS->Draw(x + x_adder - 1, y + y_adder, S1, (JTHIS->getColor(str[i]) | BG_BLACK));
    }
}

JVOID JWINDOW::DrawString(JCFLOAT x, JCFLOAT y, JCWCHAR str[], JCBOOL AlphaR)
{
    JSHORT x_adder = 0, y_adder = 0;
    JFOR(JSHORT i = 0; str[i]; i++)
    {
        JIF(str[i] == L'\n')
        {
            x_adder = 0;
            y_adder++;
            JCONTINUE;
        }
        JTHIS->Draw(x + x_adder, y + y_adder, str[i], (FG_WHITE | BG_BLACK), AlphaR);
        x_adder++;
    }
}

JVOID JWINDOW::DrawHorizontal(JCFLOAT x, JCFLOAT y, JCINT Width, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    JFOR(JINT i = (JINT)x; i < Width; i++)
    JTHIS->Draw(x + i, y, Character, color, AlphaR);
}

JVOID JWINDOW::DrawVertical(JCFLOAT x, JCFLOAT y, JCINT Height, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    JFOR(JINT i = (JINT)y; i < Height; i++)
    JTHIS->Draw(x, y + i, Character, color, AlphaR);
}

JVOID JWINDOW::DrawLine(JCFLOAT x1, JCFLOAT y1, JCFLOAT x2, JCFLOAT y2, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    JFLOAT xCurrent = x1;
    JFLOAT yCurrent = y1;
    // Get Distant
    JFLOAT xDistant = (x1 > x2) ? (x1 - x2) : (x2 - x1);
    JFLOAT yDistant = (y1 > y2) ? (y1 - y2) : (y2 - y1);
    // Pythagoream
    JFLOAT distance = std::sqrt(xDistant * xDistant + yDistant * yDistant);
    // Get MAX Sample
    JINT numberSample = std::max(xDistant, yDistant);
    // Get The Delta of SAMPLE
    JFLOAT samplePX = xDistant / numberSample;
    JFLOAT samplePY = yDistant / numberSample;
    JFOR(JINT i = 0; i < numberSample; i++)
    {
        JTHIS->Draw(xCurrent, yCurrent, Character, color, AlphaR);
        xCurrent += (x1 > x2) ? -samplePX : samplePX;
        yCurrent += (y1 > y2) ? -samplePY : samplePY;
    }
}

JVOID JWINDOW::DrawTriangle(JCFLOAT x1, JCFLOAT y1, JCFLOAT x2, JCFLOAT y2, JCFLOAT x3, JCFLOAT y3, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    JTHIS->DrawLine(x1, y1, x2, y2, Character, color, AlphaR);
    JTHIS->DrawLine(x2, y2, x3, y3, Character, color, AlphaR);
    JTHIS->DrawLine(x3, y3, x1, y1, Character, color, AlphaR);
}

JVOID JWINDOW::DrawBox(JCINT width, JCINT height, JCFLOAT x, JCFLOAT y, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    JFOR(JINT i = 0; i < height; i++)
    JFOR(JINT j = 0; j < width; j++)
    JTHIS->Draw(x + j, y + i, Character, color, AlphaR);
}

JVOID JWINDOW::Draw(JCFLOAT x, JCFLOAT y, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    JIF((JINT)x >= 0 && (JINT)x < JTHIS->GetWidth() && (JINT)y >= 0 && (JINT)y < JTHIS->GetHeight())
    {
        JIF(AlphaR && Character == S0)
        JRETURN;
        JTHIS->Screen[JTHIS->GetWidth() * (JINT)y + (JINT)x].Char.UnicodeChar = Character;
        JTHIS->Screen[JTHIS->GetWidth() * (JINT)y + (JINT)x].Attributes = color;
    }
}