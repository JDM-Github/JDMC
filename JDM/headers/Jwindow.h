#pragma once

#include "Jinclude.h"
#include "JkeyBoard.h"

class Window
{
protected:
    bool Running;

    std::string WTitle;
    uint16_t ScreenWidth, ScreenHeight;

    HANDLE originalConsole;
    HANDLE hConsole;
    HANDLE hConsoleI;
    HWND console;

    DWORD BytesWritten;
    SMALL_RECT screenBufferCorners;

    float keyPressMS = 0.15;
    float keyPressValue = 0.15;
    KeyBoard keyboard = KeyBoard();

public:
    CHAR_INFO *Screen;

public:
    Window(const char *Title, uint16_t Width, uint16_t Height, uint8_t fontSize = 5)
        : ScreenWidth(Width), ScreenHeight(Height)
    {
        Running = true;
        WTitle = Title;
        screenBufferCorners = {0, 0, 1, 1};
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        hConsoleI = GetStdHandle(STD_INPUT_HANDLE);

        SetConsoleWindowInfo(hConsole, TRUE, &screenBufferCorners);
        assert(SetConsoleScreenBufferSize(hConsole, {(short)Width, (short)Height}));
        assert(SetConsoleActiveScreenBuffer(hConsole));

        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = fontSize;
        cfi.dwFontSize.Y = fontSize;
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;
        std::wcscpy(cfi.FaceName, L"Lucida Console");
        assert(SetCurrentConsoleFontEx(hConsole, FALSE, &cfi));

        ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);

        screenBufferCorners = {0, 0, (short)(Width - 1), (short)(Height - 1)};
        assert(SetConsoleWindowInfo(hConsole, TRUE, &screenBufferCorners));
        Screen = new CHAR_INFO[ScreenWidth * ScreenHeight];
    }
    ~Window()
    {

        delete[] Screen;
    }
    virtual void onUserUpdate(float ElapseTime) = 0;
    virtual void onUserCreate() = 0;
    constexpr uint16_t getw() { return this->ScreenWidth; }
    constexpr uint16_t geth() { return this->ScreenHeight; }
    void Clear(const wchar_t Character = S0, short color = (FG_BLACK | BG_BLACK));

    void run()
    {
        onUserCreate();
        srand(std::time(0));
        auto tp1 = std::chrono::system_clock::now();
        auto tp2 = std::chrono::system_clock::now();
        while (Running)
        {
            tp2 = std::chrono::system_clock::now();
            std::chrono::duration<float> elapseTime = tp2 - tp1;
            tp1 = tp2;
            float ElapseTime = elapseTime.count();
            onUserUpdate(ElapseTime);

            keyboard.update();

            wchar_t updater[256];
            swprintf(updater, 256, L"%s - FPS: %3.2f", WTitle.c_str(), 1.0 / ElapseTime);
            SetConsoleTitleW(updater);
            WriteConsoleOutputW(hConsole, Screen, {(short)ScreenWidth, (short)ScreenHeight}, {0, 0}, &screenBufferCorners);
        }
    }

    constexpr bool collide_point(float x1, float y1, int width, int height, const float x, const float y)
    {
        return (x1 <= x && x <= x1 + width && y1 <= y && y <= y1 + height);
    }
    constexpr bool collide_box(float x1, float y1, int width1, int height1,
                               const int width, const int height, const float x, const float y)
    {
        if (x1 + width1 < x)
            return 0;
        if (x1 > x + width)
            return 0;
        if (y1 + height1 < y)
            return 0;
        if (y1 > y + height)
            return 0;
        return 1;
    }

    Color getColor(wchar_t index);
    void Draw(float x, float y, short Character = S1, short color = (FG_LWHITE | BG_BLACK), bool AlphaR = 0);
    void DrawString(float x, float y, std::wstring &str, bool AlphaR = 0);
    void DrawString(float x, float y, wchar_t str[], bool AlphaR = 0);

    void DrawCString(float x, float y, std::wstring &str, bool AlphaR = 0);
    void DrawHorizontal(float x, float y, int Width, wchar_t Character = S1, short color = (FG_LWHITE | BG_BLACK), bool AlphaR = 0);
    void DrawVertical(float x, float y, int Height, wchar_t Character = S1, short color = (FG_LWHITE | BG_BLACK), bool AlphaR = 0);
    void DrawLine(float x1, float y1, float x2, float y2, short Character = S1, short color = (FG_LWHITE | BG_BLACK), bool AlphaR = 0);
    void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, wchar_t Character = S1, short color = (FG_LWHITE | BG_BLACK), bool AlphaR = 0);

    void DrawBox(int width, int height, float x, float y, short Character = S1, short color = (FG_LWHITE | BG_BLACK), bool AlphaR = 0);
};