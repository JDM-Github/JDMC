#include "Jwindow.h"

JWINDOW::JWINDOW(JCCHAR *Title, JCSHORT Width, JCSHORT Height, JCSHORT fontWidth, JCSHORT fontHeight)
    : WTitle(Title), ScreenWidth(std::min(Width, (JSHORT)(JSWMAX / fontWidth))), ScreenHeight(std::min(Height, (JSHORT)(JSHMAX / fontHeight)))
{
    this->originalConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    this->hConsoleI = GetStdHandle(STD_INPUT_HANDLE);
    this->bufferInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    assert(SetConsoleActiveScreenBuffer(this->hConsole));
    assert(this->SetupWindow());

#if JEDITABLE
    GetConsoleMode(this->hConsoleI, &this->PrevMode);
    SetConsoleMode(this->hConsoleI, ENABLE_EXTENDED_FLAGS | (this->PrevMode & ~ENABLE_QUICK_EDIT_MODE));
#endif
    SetConsoleWindowSize(this->hConsole, ScreenWidth, ScreenHeight, fontWidth, fontHeight);
    ShowScrollBar(GetConsoleWindow(), SB_VERT, JFALSE);

    GetConsoleCursorInfo(this->hConsole, &this->CursorInfo);
    this->CursorInfo.dwSize = 0;
    this->CursorInfo.bVisible = JFALSE;
    SetConsoleCursorInfo(this->hConsole, &this->CursorInfo);
    GetConsoleScreenBufferInfoEx(this->hConsole, &bufferInfo);
    this->Screen = new CHAR_INFO[ScreenWidth * ScreenHeight];
}

JWINDOW::~JWINDOW()
{
    Clear();
    SetConsoleWindowSize(this->originalConsole, 120, 50, 6, 10);
    SetConsoleActiveScreenBuffer(this->originalConsole);
    WriteConsoleOutputW(this->originalConsole, this->Screen, {this->GetWidth(), this->GetHeight()}, {0, 0}, &this->screenBufferCorners);
    ShowScrollBar(GetConsoleWindow(), SB_VERT, JTRUE);
    SetConsoleCursorPosition(this->originalConsole, {0, 0});
    SetConsoleMode(this->hConsoleI, this->PrevMode);

    this->CursorInfo.bVisible = JTRUE;
    SetConsoleCursorInfo(this->hConsole, &this->CursorInfo);
    SetConsoleTextAttribute(this->originalConsole, FG_WHITE | BG_BLACK);
    delete[] this->Screen;
}

JVOID JWINDOW::SetConsoleWindowSize(HANDLE console, JCSHORT Width, JCSHORT Height, JCSHORT FontWidth, JCSHORT FontHeight)
{
    this->screenBufferCorners = {0, 0, 1, 1};
    SetConsoleWindowInfo(console, JTRUE, &this->screenBufferCorners);
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

    this->screenBufferCorners = {0, 0, (JSHORT)(Width - 1), (JSHORT)(Height - 1)};
    assert(SetConsoleWindowInfo(console, JTRUE, &this->screenBufferCorners));
}

JVOID JWINDOW::Start()
{
    assert(this->onUserCreate());
    srand(std::time(0));
    this->timePoint1 = std::chrono::system_clock::now();
    this->timePoint2 = std::chrono::system_clock::now();
    while (this->Running)
        this->Running = this->gameLoop();
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
    this->timePoint2 = std::chrono::system_clock::now();
    std::chrono::duration<JFLOAT> elapseTime = this->timePoint2 - this->timePoint1;
    this->timePoint1 = this->timePoint2;

    this->ElapseTime = elapseTime.count();
    if (this->onUserUpdate(this->ElapseTime))
    {
#if JGETMOUSEPOS
        GetCursorPos(&this->MousePos);
        ScreenToClient(GetConsoleWindow(), &this->MousePos);
#endif
        this->keyboard.update();
#if JESCTOEXIT
        if (keyboard.Keys[Keys::J_ESC].isReleased)
            return JFALSE;
#endif
        JWCHAR updater[256];
        swprintf(updater, 256, L"JDMC: JDMaster Console Framework:    %s - FPS: %4.2f",
                 this->WTitle.c_str(),
                 (JSHOWFPS) ? 1.0 / this->ElapseTime : 0);
        SetConsoleTitleW(updater);
        WriteConsoleOutputW(this->hConsole, this->Screen, {this->GetWidth(), this->GetHeight()}, {0, 0}, &this->screenBufferCorners);
        return JTRUE;
    }
    return JFALSE;
}

JVOID JWINDOW::Clear(JCSHORT Character, JCSHORT Color)
{
    for (JSHORT i = 0; i < this->GetHeight(); i++)
        for (JSHORT j = 0; j < this->GetWidth(); j++)
        {
            this->Screen[i * this->GetWidth() + j].Char.UnicodeChar = Character;
            this->Screen[i * this->GetWidth() + j].Attributes = Color;
        }
}
JVOID JWINDOW::SetColorIndex(JCSHORT Index, PixelRGB rgb)
{
    this->bufferInfo.ColorTable[Index] = RGB(rgb.R, rgb.G, rgb.B);
    this->bufferInfo.ColorTable[Index];
    SetConsoleScreenBufferInfoEx(this->hConsole, &this->bufferInfo);
}
JVOID JWINDOW::DrawString(JCFLOAT x, JCFLOAT y, JCWSTR &str, JCBOOL AlphaR)
{
    JSHORT x_adder = 0, y_adder = 0;
    for (JSHORT i = 0; i < str.size(); i++)
    {
        if (str[i] == L'\n')
        {
            x_adder = 0;
            y_adder++;
            continue;
        }
        this->Draw(x + x_adder, y + y_adder, str[i], (FG_WHITE | FG_BLACK), AlphaR);
        x_adder++;
    }
}

JVOID JWINDOW::DrawCString(JCFLOAT x, JCFLOAT y, JCWSTR &str, JCBOOL AlphaR)
{
    JSHORT x_adder = 0, y_adder = 0;
    for (JSHORT i = 0; i < str.size(); i++)
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
        this->Draw(x + x_adder - 1, y + y_adder, S1, (this->getColor(str[i]) | BG_BLACK));
    }
}

JVOID JWINDOW::DrawString(JCFLOAT x, JCFLOAT y, JCWCHAR str[], JCBOOL AlphaR)
{
    JSHORT x_adder = 0, y_adder = 0;
    for (JSHORT i = 0; str[i]; i++)
    {
        if (str[i] == L'\n')
        {
            x_adder = 0;
            y_adder++;
            continue;
        }
        this->Draw(x + x_adder, y + y_adder, str[i], (FG_WHITE | BG_BLACK), AlphaR);
        x_adder++;
    }
}

JVOID JWINDOW::DrawHorizontal(JCFLOAT x, JCFLOAT y, JCINT Width, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    for (JINT i = (JINT)x; i < Width; i++)
        this->Draw(x + i, y, Character, color, AlphaR);
}

JVOID JWINDOW::DrawVertical(JCFLOAT x, JCFLOAT y, JCINT Height, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    for (JINT i = (JINT)y; i < Height; i++)
        this->Draw(x, y + i, Character, color, AlphaR);
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
    for (JINT i = 0; i < numberSample; i++)
    {
        this->Draw(xCurrent, yCurrent, Character, color, AlphaR);
        xCurrent += (x1 > x2) ? -samplePX : samplePX;
        yCurrent += (y1 > y2) ? -samplePY : samplePY;
    }
}

JVOID JWINDOW::DrawTriangle(JCFLOAT x1, JCFLOAT y1, JCFLOAT x2, JCFLOAT y2, JCFLOAT x3, JCFLOAT y3, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    this->DrawLine(x1, y1, x2, y2, Character, color, AlphaR);
    this->DrawLine(x2, y2, x3, y3, Character, color, AlphaR);
    this->DrawLine(x3, y3, x1, y1, Character, color, AlphaR);
}

JVOID JWINDOW::DrawBox(JCINT width, JCINT height, JCFLOAT x, JCFLOAT y, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    for (JINT i = 0; i < height; i++)
        for (JINT j = 0; j < width; j++)
            this->Draw(x + j, y + i, Character, color, AlphaR);
}

JVOID JWINDOW::Draw(JCFLOAT x, JCFLOAT y, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    if ((JINT)x >= 0 && (JINT)x < this->GetWidth() && (JINT)y >= 0 && (JINT)y < this->GetHeight())
    {
        if (AlphaR && Character == S0)
            return;
        this->Screen[this->GetWidth() * (JINT)y + (JINT)x].Char.UnicodeChar = Character;
        this->Screen[this->GetWidth() * (JINT)y + (JINT)x].Attributes = color;
    }
}