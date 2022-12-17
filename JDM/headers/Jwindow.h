#pragma once

#include "Jinclude.h"

class Window
{
protected:
    bool Running;
    uint16_t ScreenWidth, ScreenHeight;
    HANDLE hConsole;
    HWND console;
    DWORD BytesWritten;
    float keyPressMS;
    float keyPressValue;

public:
    wchar_t *Screen;

public:
    Window(const char *Title, uint16_t Width, uint16_t Height, uint8_t fontSize = 5)
        : ScreenWidth(Width), ScreenHeight(Height)
    {
        keyPressValue = 0.15;
        keyPressMS = keyPressValue;
        Running = true;
        Screen = new wchar_t[ScreenWidth * ScreenHeight];
        hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        console = GetConsoleWindow();

        SetConsoleTitleA(Title);
        SetConsoleActiveScreenBuffer(hConsole);

        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = fontSize;
        cfi.dwFontSize.Y = fontSize;
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;

        std::wcscpy(cfi.FaceName, L"Lucida Console");
        SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
        ShowScrollBar(console, SB_VERT, 0);
        BytesWritten = 0;
    }
    ~Window() { delete[] Screen; }
    virtual void onUserUpdate(float ElapseTime) {}
    virtual void onUserCreate() {}
    constexpr uint16_t getw() { return this->ScreenWidth; }
    constexpr uint16_t geth() { return this->ScreenHeight; }
    void Clear(const int16_t Width = -1, const int16_t Height = -1, const wchar_t Character = PIXEL_NONE);

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

            keyPressMS -= ElapseTime;
            if (keyPressMS <= 0)
                handlekeyPress(ElapseTime);

            WriteConsoleOutputCharacterW(hConsole, Screen, (ScreenWidth * ScreenHeight), {0, 0}, &BytesWritten);
        }
    }

    constexpr bool collide_point(float x1, float y1, int width, int height, const float x, const float y) { return (x1 <= x && x <= x1 + width && y1 <= y && y <= y1 + height); }
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

    constexpr bool collide_boxX(float x1, int width1,
                                const int width, const float x)
    {
        if (x1 + width1 < x)
            return 0;
        if (x1 > x + width)
            return 0;
        return 1;
    }
    constexpr bool collide_boxY(float y1, int height1,
                                const int height, const float y)
    {
        if (y1 + height1 < y)
            return 0;
        if (y1 > y + height)
            return 0;
        return 1;
    }

    void Draw(float x, float y, wchar_t Character = PIXEL_SOLID1, bool AlphaR = 0)
    {
        if (!((int)x >= ScreenWidth || (int)x < 0 || (int)y >= ScreenHeight || (int)y < 0 || (Character == PIXEL_NONE && AlphaR)))
            Screen[(int)y * ScreenWidth + (int)x] = Character;
    }
    void DrawString(float x, float y, std::wstring &str, bool AlphaR = 0)
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
            Draw(x + x_adder, y + y_adder, str[i], AlphaR);
            x_adder++;
        }
    }
    void DrawString(float x, float y, wchar_t str[], bool AlphaR = 0)
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
            Draw(x + x_adder, y + y_adder, str[i], AlphaR);
            x_adder++;
        }
    }
    void DrawHorizontal(float x, float y, int Width, wchar_t Character = PIXEL_SOLID1, bool AlphaR = 0)
    {
        for (int i = (int)x; i < Width; i++)
            Draw(x + i, y, Character, AlphaR);
    }
    void DrawVertical(float x, float y, int Height, wchar_t Character = PIXEL_SOLID1, bool AlphaR = 0)
    {
        for (int i = (int)y; i < Height; i++)
            Draw(x, y + i, Character, AlphaR);
    }
    void DrawBox(int width, int height, float x, float y, wchar_t Character = PIXEL_SOLID1, bool AlphaR = 0)
    {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                Draw(x + j, y + i, Character, AlphaR);
    }

    void handlekeyPress(float ElapseTime);
    virtual void keyPressA(float ElapseTime) {}
    virtual void keyPressB(float ElapseTime) {}
    virtual void keyPressC(float ElapseTime) {}
    virtual void keyPressD(float ElapseTime) {}
    virtual void keyPressE(float ElapseTime) {}
    virtual void keyPressF(float ElapseTime) {}
    virtual void keyPressG(float ElapseTime) {}
    virtual void keyPressH(float ElapseTime) {}
    virtual void keyPressI(float ElapseTime) {}
    virtual void keyPressJ(float ElapseTime) {}
    virtual void keyPressK(float ElapseTime) {}
    virtual void keyPressL(float ElapseTime) {}
    virtual void keyPressM(float ElapseTime) {}
    virtual void keyPressN(float ElapseTime) {}
    virtual void keyPressO(float ElapseTime) {}
    virtual void keyPressP(float ElapseTime) {}
    virtual void keyPressQ(float ElapseTime) {}
    virtual void keyPressR(float ElapseTime) {}
    virtual void keyPressS(float ElapseTime) {}
    virtual void keyPressT(float ElapseTime) {}
    virtual void keyPressU(float ElapseTime) {}
    virtual void keyPressV(float ElapseTime) {}
    virtual void keyPressW(float ElapseTime) {}
    virtual void keyPressX(float ElapseTime) {}
    virtual void keyPressY(float ElapseTime) {}
    virtual void keyPressZ(float ElapseTime) {}
};
