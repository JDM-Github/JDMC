// #include <iostream>
// #include <cstdlib>
// #include <Windows.h>
// #include <thread>
// #include <cassert>

// using namespace std;

// void setWindowSize(HANDLE console)
// {
//     SMALL_RECT screenBufferCorners;
//     screenBufferCorners = {0, 0, 1, 1};
//     SetConsoleWindowInfo(console, TRUE, &screenBufferCorners);
//     assert(SetConsoleScreenBufferSize(console, {60, 30}));
//     assert(SetConsoleActiveScreenBuffer(console));

//     CONSOLE_FONT_INFOEX cfi;
//     cfi.cbSize = sizeof(cfi);
//     cfi.nFont = 0;
//     cfi.dwFontSize.X = 10;
//     cfi.dwFontSize.Y = 12;
//     cfi.FontFamily = FF_DONTCARE;
//     cfi.FontWeight = FW_NORMAL;
//     std::wcscpy(cfi.FaceName, L"Lucida Console");
//     assert(SetCurrentConsoleFontEx(console, FALSE, &cfi));
//     screenBufferCorners = {0, 0, 60 - 1, 30 - 1};
//     assert(SetConsoleWindowInfo(console, TRUE, &screenBufferCorners));
//     ShowScrollBar(GetConsoleWindow(), SB_VERT, FALSE);
// }


// void print(HANDLE &handle, int Color, const char* Str) {
//     SetConsoleTextAttribute(handle, Color);
//     cout << Str;
//     SetConsoleTextAttribute(handle, 0xF);
// }

// void printInfo(HANDLE handle)
// {
//     print(handle, 0x3, " > ");
//     print(handle, 0xF, "INFO: ");
// }

// int main()
// {
//     HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//     SetConsoleTitleW(L"JDMC: JDM Console Compiler");
//     setWindowSize(handle);
//     print(handle, 0xF, "\n Compiler Version 1.0\n\n");
//     printInfo(handle);
//     print(handle, 0x2, "Compiling...\n\n");
//     printInfo(handle);
//     print(handle, 0x2, "Command Info ");
//     print(handle, 0x3, "{\n");
//     SetConsoleTextAttribute(handle, 8);
//     system("@make compile");
//     print(handle, 0x3, "\n }\n\n");
//     printInfo(handle);
//     print(handle, 0x2, "Done Compiling...\n\n");
//     printInfo(handle);
//     print(handle, 0x2, "Click to Run...\n\n");
//     SetConsoleTextAttribute(handle, 8);
//     system("@PAUSE");
//     print(handle, 0xF, "\n");
//     printInfo(handle);
//     print(handle, 0x2, "Starting...\n");
//     SetConsoleTextAttribute(handle, 8);
//     system("@make exec");

//     return 0;
// }