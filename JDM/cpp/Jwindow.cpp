#include "Jwindow.h"

void Window::Clear(const int16_t Width, const int16_t Height, const wchar_t Character)
{
    for (int i = 0; i < ((Height == -1) ? ScreenHeight : Height); i++)
        for (int j = 0; j < ((Width == -1) ? ScreenWidth : Width); j++)
            Screen[i * ScreenWidth + j] = Character;
}

void Window::handlekeyPress(float ElapseTime)
{
    if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
    {
        keyPressA(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'B') & 0x8000)
    {
        keyPressB(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'C') & 0x8000)
    {
        keyPressC(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
    {
        keyPressD(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'E') & 0x8000)
    {
        keyPressE(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'F') & 0x8000)
    {
        keyPressF(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'G') & 0x8000)
    {
        keyPressG(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'H') & 0x8000)
    {
        keyPressH(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'I') & 0x8000)
    {
        keyPressI(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'J') & 0x8000)
    {
        keyPressJ(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'K') & 0x8000)
    {
        keyPressK(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'L') & 0x8000)
    {
        keyPressL(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'M') & 0x8000)
    {
        keyPressM(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'N') & 0x8000)
    {
        keyPressN(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'O') & 0x8000)
    {
        keyPressO(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'P') & 0x8000)
    {
        keyPressP(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'Q') & 0x8000)
    {
        keyPressQ(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'R') & 0x8000)
    {
        keyPressR(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
    {
        keyPressS(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'T') & 0x8000)
    {
        keyPressT(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'U') & 0x8000)
    {
        keyPressU(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'V') & 0x8000)
    {
        keyPressV(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
    {
        keyPressW(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'X') & 0x8000)
    {
        keyPressX(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'Y') & 0x8000)
    {
        keyPressY(ElapseTime);
        keyPressMS = keyPressValue;
    }
    if (GetAsyncKeyState((unsigned short)'Z') & 0x8000)
    {
        keyPressZ(ElapseTime);
        keyPressMS = keyPressValue;
    }
}