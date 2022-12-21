#include "Jwindow.h"

Window::Window(JCCHAR *Title, JCSHORT Width, JCSHORT Height, JCSHORT fontSize)
    : WTitle(Title), ScreenWidth(Width), ScreenHeight(Height)
{
    this->originalConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    this->hConsoleI = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(this->hConsoleI, &this->PrevMode);
    SetConsoleMode(this->hConsoleI, ENABLE_EXTENDED_FLAGS | (this->PrevMode & ~ENABLE_QUICK_EDIT_MODE));
    SetConsoleWindowSize(this->hConsole, Width, Height, fontSize, fontSize);
    ShowScrollBar(GetConsoleWindow(), SB_VERT, JFALSE);

    GetConsoleCursorInfo(this->hConsole, &this->CursorInfo);
    this->CursorInfo.dwSize = 0;
    this->CursorInfo.bVisible = JFALSE;
    SetConsoleCursorInfo(this->hConsole, &this->CursorInfo);
    this->Screen = new CHAR_INFO[Width * Height];
}

Window::~Window()
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
    delete[] this->Screen;
}

JVOID Window::SetConsoleWindowSize(HANDLE console, JCSHORT Width, JCSHORT Height, JCSHORT FontWidth, JCSHORT FontHeight)
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

    this->screenBufferCorners = {0, 0, (short)(Width - 1), (short)(Height - 1)};
    assert(SetConsoleWindowInfo(console, JTRUE, &this->screenBufferCorners));
}

JVOID Window::Start()
{
    assert(this->onUserCreate());
    srand(std::time(0));
    this->timePoint1 = std::chrono::system_clock::now();
    this->timePoint2 = std::chrono::system_clock::now();
    while (this->Running)
        this->Running = this->gameLoop();
}

JBOOL Window::gameLoop()
{
    this->timePoint2 = std::chrono::system_clock::now();
    std::chrono::duration<JFLOAT> elapseTime = this->timePoint2 - this->timePoint1;
    this->timePoint1 = this->timePoint2;

    this->ElapseTime = elapseTime.count();
    if (this->onUserUpdate(this->ElapseTime))
    {
        this->keyboard.update();
        if (keyboard.Keys[Keys::J_ESC].isPressed)
            return JFALSE;

        JWCHAR updater[256];
        swprintf(updater, 256, L"%s - FPS: %3.2f", this->WTitle.c_str(), 1.0 / this->ElapseTime);
        SetConsoleTitleW(updater);
        WriteConsoleOutputW(this->hConsole, this->Screen, {this->GetWidth(), this->GetHeight()}, {0, 0}, &this->screenBufferCorners);
        return JTRUE;
    }
    return JFALSE;
}

JVOID Window::Clear(JCSHORT Character, JCSHORT Color)
{
    for (JSHORT i = 0; i < this->GetHeight(); i++)
        for (JSHORT j = 0; j < this->GetWidth(); j++)
        {
            this->Screen[i * this->GetWidth() + j].Char.UnicodeChar = Character;
            this->Screen[i * this->GetWidth() + j].Attributes = Color;
        }
}

Color Window::getColor(JCSHORT Index)
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

JVOID Window::DrawString(JCFLOAT x, JCFLOAT y, JCWSTR &str, JCBOOL AlphaR)
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
        this->Draw(x + x_adder, y + y_adder, str[i], (FG_LWHITE | FG_BLACK), AlphaR);
        x_adder++;
    }
}

JVOID Window::DrawCString(JCFLOAT x, JCFLOAT y, JCWSTR &str, JCBOOL AlphaR)
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

JVOID Window::DrawString(JCFLOAT x, JCFLOAT y, JCWCHAR str[], JCBOOL AlphaR)
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
        this->Draw(x + x_adder, y + y_adder, str[i], (FG_LWHITE | BG_BLACK), AlphaR);
        x_adder++;
    }
}

JVOID Window::DrawHorizontal(JCFLOAT x, JCFLOAT y, JCINT Width, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    for (JINT i = (JINT)x; i < Width; i++)
        this->Draw(x + i, y, Character, color, AlphaR);
}

JVOID Window::DrawVertical(JCFLOAT x, JCFLOAT y, JCINT Height, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    for (JINT i = (JINT)y; i < Height; i++)
        this->Draw(x, y + i, Character, color, AlphaR);
}

JVOID Window::DrawLine(JCFLOAT x1, JCFLOAT y1, JCFLOAT x2, JCFLOAT y2, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
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

JVOID Window::DrawTriangle(JCFLOAT x1, JCFLOAT y1, JCFLOAT x2, JCFLOAT y2, JCFLOAT x3, JCFLOAT y3, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    this->DrawLine(x1, y1, x2, y2, Character, color, AlphaR);
    this->DrawLine(x2, y2, x3, y3, Character, color, AlphaR);
    this->DrawLine(x3, y3, x1, y1, Character, color, AlphaR);
}

JVOID Window::DrawBox(JCINT width, JCINT height, JCFLOAT x, JCFLOAT y, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    for (JINT i = 0; i < height; i++)
        for (JINT j = 0; j < width; j++)
            this->Draw(x + j, y + i, Character, color, AlphaR);
}

JVOID Window::Draw(JCFLOAT x, JCFLOAT y, JCSHORT Character, JCSHORT color, JCBOOL AlphaR)
{
    if ((JINT)x >= 0 && (JINT)x < this->GetWidth() && (JINT)y >= 0 && (JINT)y < this->GetHeight())
    {
        if (AlphaR && Character == S0)
            return;
        this->Screen[this->GetWidth() * (JINT)y + (JINT)x].Char.UnicodeChar = Character;
        this->Screen[this->GetWidth() * (JINT)y + (JINT)x].Attributes = color;
    }
}