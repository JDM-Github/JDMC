#include "JDM.h"

std::wstring tetromino[7];
const int FieldWidth = 14;
const int FieldHeight = 20;

using namespace std::chrono_literals;

class WWindow : public Window
{
public:
    float gamerate = 0.3;

    unsigned char *Field = nullptr;

    int nextPiece = rand() % 7;
    int currentPiece = rand() % 7;
    int currentRotation = 0;
    int currentX = FieldWidth / 2;
    int currentY = 0;

    bool gameStart = false;
    bool gameOver = false;

    int Score_Integer = 0;
    wchar_t score[50] = L"0";

    std::vector<int> Lines;

public:
    WWindow(const char *Title, uint16_t Width, uint16_t Height, uint8_t fontSize)
        : Window(Title, Width, Height, fontSize) { keyPressValue = 0.15; }

    void onUserCreate()
    {
        Field = new unsigned char[FieldWidth * FieldHeight];
        for (int y = 0; y < FieldHeight; y++)
            for (int x = 0; x < FieldWidth; x++)
                Field[y * FieldWidth + x] = (x == 0 || x == FieldWidth - 1 || y == FieldHeight - 1) ? 9 : 0;

        tetromino[0].append(L"  X ");
        tetromino[0].append(L"  X ");
        tetromino[0].append(L"  X ");
        tetromino[0].append(L"  X ");

        tetromino[1].append(L"  X ");
        tetromino[1].append(L" XX ");
        tetromino[1].append(L" X  ");
        tetromino[1].append(L"    ");

        tetromino[2].append(L" X  ");
        tetromino[2].append(L" XX ");
        tetromino[2].append(L"  X ");
        tetromino[2].append(L"    ");

        tetromino[3].append(L"    ");
        tetromino[3].append(L" XX ");
        tetromino[3].append(L" XX ");
        tetromino[3].append(L"    ");

        tetromino[4].append(L"  X ");
        tetromino[4].append(L" XX ");
        tetromino[4].append(L"  X ");
        tetromino[4].append(L"    ");

        tetromino[5].append(L"    ");
        tetromino[5].append(L" XX ");
        tetromino[5].append(L"  X ");
        tetromino[5].append(L"  X ");

        tetromino[6].append(L"    ");
        tetromino[6].append(L" XX ");
        tetromino[6].append(L" X  ");
        tetromino[6].append(L" X  ");
    }

    int Rotate(int x, int y, int r)
    {
        switch (r % 4)
        {
        case 0:
            return y * 4 + x;
        case 1:
            return 12 + y - (x * 4);
        case 2:
            return 15 - (y * 4) - x;
        case 3:
            return 3 - y + (x * 4);
        }
        return 0;
    }

    int calculateScore(int s)
    {
        switch (s)
        {
        case 1:
            return 10;
        case 2:
            return 25;
        case 3:
            return 50;
        case 4:
            return 80;
        }
    }

    bool doesPieceFit(int TetrisIndex, int Rotation, int x, int y)
    {
        for (int px = 0; px < 4; px++)
            for (int py = 0; py < 4; py++)
            {
                int pi = Rotate(px, py, Rotation);
                int fi = (y + py) * FieldWidth + (x + px);

                if (x + px >= 0 && x + px < FieldWidth)
                    if (y + py >= 0 && y + py < FieldHeight)
                        if (tetromino[TetrisIndex][pi] == L'X' && Field[fi] != 0)
                            return false;
            }
        return true;
    }

    void keyPressG(float ElapseTime)
    {
        if (doesPieceFit(nextPiece, 0, currentX, currentY))
        {
            int temp = currentPiece;
            currentPiece = nextPiece;
            nextPiece = temp;
        }
    }
    void keyPressA(float ElapseTime)
    {
        if (doesPieceFit(currentPiece, currentRotation, currentX - 1, currentY))
            currentX--;
    }
    void keyPressD(float ElapseTime)
    {
        if (doesPieceFit(currentPiece, currentRotation, currentX + 1, currentY))
            currentX++;
    }
    void keyPressX(float ElapseTime)
    {
        for (int y = 1; y < FieldHeight; y++)
            if (doesPieceFit(currentPiece, currentRotation, currentX, currentY + y))
                currentY++;
            else
                break;
    }
    void keyPressS(float ElapseTime)
    {
        gameStart = true;
        if (doesPieceFit(currentPiece, currentRotation, currentX, currentY + 1))
            currentY++;
    }
    void keyPressR(float ElapseTime)
    {
        if (doesPieceFit(currentPiece, currentRotation + 1, currentX, currentY))
            currentRotation++;
    }

    void keyPressP(float ElapseTime)
    {
        if (gameOver)
        {
            for (int y = 0; y < FieldHeight; y++)
                for (int x = 0; x < FieldWidth; x++)
                    Field[y * FieldWidth + x] = (x == 0 || x == FieldWidth - 1 || y == FieldHeight - 1) ? 9 : 0;

            gameOver = false;
            Score_Integer = 0;
            currentX = FieldWidth / 2;
            currentY = 0;
            currentRotation = 0;
            currentPiece = rand() % 7;
            nextPiece = rand() % 7;
        }
    }

    void onUserUpdate(float ElapseTime)
    {
        Clear();
        if (!gameOver)
        {
            gamerate -= ElapseTime;
            if (gamerate <= 0 && gameStart)
            {
                gamerate = 0.3;
                if (doesPieceFit(currentPiece, currentRotation, currentX, currentY + 1))
                    currentY++;
                else
                {
                    for (int px = 0; px < 4; px++)
                        for (int py = 0; py < 4; py++)
                            if (tetromino[currentPiece][Rotate(px, py, currentRotation)] == L'X')
                                Field[(currentY + py) * FieldWidth + (currentX + px)] = currentPiece + 1;

                    for (int py = 0; py < 4; py++)
                    {
                        if (currentY + py < FieldHeight - 1)
                        {
                            bool line = true;
                            for (int px = 1; px < FieldWidth - 1; px++)
                                line &= (Field[(currentY + py) * FieldWidth + px]) != 0;

                            if (line)
                            {
                                for (int px = 1; px < FieldWidth - 1; px++)
                                    Field[(currentY + py) * FieldWidth + px] = 8;
                                Lines.push_back(currentY + py);
                            }
                        }
                    }
                    currentX = FieldWidth / 2;
                    currentY = 0;
                    currentRotation = 0;
                    currentPiece = nextPiece;
                    nextPiece = rand() % 7;

                    gameOver = !doesPieceFit(currentPiece, currentRotation, currentX, currentY);
                }
            }
            DrawBox(6, 6, FieldWidth, 0, S4);
            DrawBox(4, 4, FieldWidth + 1, 1, L' ');
            for (int px = 0; px < 4; px++)
                for (int py = 0; py < 4; py++)
                {
                    if (tetromino[currentPiece][Rotate(px, py, currentRotation)] == L'X')
                        Screen[(currentY + py) * ScreenWidth + (currentX + px)] = currentPiece + 65;
                    if (tetromino[nextPiece][Rotate(px, py, 0)] == L'X')
                        Screen[(1 + py) * ScreenWidth + (FieldWidth + 1 + px)] = nextPiece + 65;
                }

            for (int i = 0; i < FieldHeight; i++)
                for (int j = 0; j < FieldWidth; j++)
                    Draw(j, i, L" ABCDEFG=█"[Field[i * FieldWidth + j]], 1);

            if (!Lines.empty())
            {
                WriteConsoleOutputCharacterW(hConsole, Screen, (ScreenWidth * ScreenHeight), {0, 0}, &BytesWritten);
                std::this_thread::sleep_for(400ms);

                for (auto &v : Lines)
                {
                    for (int px = 1; px < FieldWidth - 1; px++)
                    {
                        for (int py = v; py > 0; py--)
                            Field[py * FieldWidth + px] = Field[(py - 1) * FieldWidth + px];
                        Field[px] = 0;
                    }
                }
                Score_Integer += calculateScore(Lines.size());
                _snwprintf(score, 50, L"%d", Score_Integer);
                Lines.clear();
            }
            DrawString(FieldWidth, ScreenHeight - 1, score);
        }
        else if (gameStart)
        {
            std::wstring GAMEOVER = (L"                    \n"
                                     L"                    \n"
                                     L"                    \n"
                                     L"  G A M E  O V E R  \n"
                                     L"                    \n"
                                     L"                    \n"
                                     L"                    \n"
                                     L"                    \n"
                                     L"                    \n"
                                     L"     PLAY AGAIN?    \n"
                                     L"                    \n"
                                     L"        EXIT        \n"
                                     L"                    \n"
                                     L"                    \n"
                                     L"                    \n"
                                     L"                    \n"
                                     L"                    \n"
                                     L"                    \n"
                                     L"                    \n"
                                     L"                    \n");
            DrawString(0, 0, GAMEOVER);
        }
    }
};

int main(int argv, char **argc)
{
    srand(std::time(0));
    WWindow *window = new WWindow("Test", 20, 20, 16);
    window->run();
    return 0;
}
