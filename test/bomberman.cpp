#include "JDM.h"

using namespace std;
class WWindow : public Window
{

public:
    int isMoving = false;
    bool isBombed = false;

    int targetX = 1, targetY = 1;
    char dirX = 'N', dirY = 'N';

    float playerSpeed;
    float playerX = 1;
    float playerY = 1;

    int blockSize = 11;
    float blockAdder = 0;

    int fieldWidth = 31;
    int fieldHeight = 21;

    float midX, midY;
    float bombTimer = 3.f;

    int upStop = 0, downStop = 0,
        leftStop = 0, rightStop = 0;

    int bombRange = 2;
    int bombX = 1;
    int bombY = 1;
    wstring map;

    vector<float> VenemyX;
    vector<float> VenemyY;
    vector<int> VtargetX;
    vector<int> VtargetY;
    vector<int> VisMoving;
    vector<char> VdirX;
    vector<char> VdirY;

public:
    WWindow(const char *Title, uint16_t Width, uint16_t Height, uint8_t fontSize)
        : Window(Title, Width, Height, fontSize) { keyPressValue = 0; }

    void onUserCreate()
    {
        playerSpeed = 5;
        midX = (ScreenWidth / 2.0 - blockSize / 2.0);
        midY = (ScreenHeight / 2.0 - blockSize / 2.0);

        map += L"###############################";
        map += L"#                             #";
        map += L"# # # # # # # # # # # # # # # #";
        map += L"#                             #";
        map += L"# # # # # # # # # # # # # # # #";
        map += L"#                             #";
        map += L"# # # # # # # # # # # # # # # #";
        map += L"#                             #";
        map += L"# # # # # # # # # # # # # # # #";
        map += L"#                             #";
        map += L"# # # # # # # # # # # # # # # #";
        map += L"#                             #";
        map += L"# # # # # # # # # # # # # # # #";
        map += L"#                             #";
        map += L"# # # # # # # # # # # # # # # #";
        map += L"#                             #";
        map += L"# # # # # # # # # # # # # # # #";
        map += L"#                             #";
        map += L"# # # # # # # # # # # # # # # #";
        map += L"#                             #";
        map += L"###############################";

        for (int py = 1; py < fieldHeight - 1; py++)
            for (int px = 1; px < fieldWidth - 1; px++)
            {
                if ((py == 1 && px == 1) || (py == 1 && px == 2) || (py == 2 && px == 1))
                    continue;
                if (map[py * fieldWidth + px] == L' ' && (rand() % 2 == 0))
                {
                    if (rand() % 16 == 0)
                    {
                        VenemyX.push_back(px);
                        VenemyY.push_back(py);
                        VtargetX.push_back(px);
                        VtargetY.push_back(py);
                        VisMoving.push_back(0);
                        VdirX.push_back('N');
                        VdirY.push_back('N');
                        continue;
                    }
                    map[py * fieldWidth + px] = L'S';
                }
            }
    }

    void keyPressS(float ElapseTime) { moveEntity(&isMoving, playerX, playerY + 1, &targetX, &targetY, &dirY, 'S'); }
    void keyPressW(float ElapseTime) { moveEntity(&isMoving, playerX, playerY - 1, &targetX, &targetY, &dirY, 'W'); }
    void keyPressD(float ElapseTime) { moveEntity(&isMoving, playerX + 1, playerY, &targetX, &targetY, &dirX, 'D'); }
    void keyPressA(float ElapseTime) { moveEntity(&isMoving, playerX - 1, playerY, &targetX, &targetY, &dirX, 'A'); }

    void moveEntity(int *isMoving, float X, float Y, int *targetX, int *targetY, char *dir, char direction)
    {
        if (*isMoving == false && (int)X >= 0)
            if (map[(int)Y * fieldWidth + (int)X] == L' ' || map[(int)Y * fieldWidth + (int)X] == L'F')
            {
                *targetX = X;
                *targetY = Y;
                *isMoving = 1;
                *dir = direction;
            }
    }
    void movingEntity(float ElapseTime, int *Moving, char *dirX,
                      char *dirY, float *X, float *Y, int targetX, int targetY)
    {
        if (*Moving)
        {
            if (*dirX != 'N')
            {
                *X += (*dirX == 'D') ? (playerSpeed * ElapseTime) : -(playerSpeed * ElapseTime);
                if ((*dirX == 'D') ? (*X >= targetX) : (*X <= targetX))
                {
                    *dirX = 'N';
                    *X = targetX;
                    *Moving = 0;
                }
            }
            else if (*dirY != 'N')
            {
                *Y += (*dirY == 'S') ? (playerSpeed * ElapseTime) : -(playerSpeed * ElapseTime);
                if ((*dirY == 'S') ? (*Y >= targetY) : (*Y <= targetY))
                {
                    *dirY = 'N';
                    *Y = targetY;
                    *Moving = 0;
                }
            }
        }
    }

    void keyPressB(float ElapseTime)
    {
        if (!isBombed)
        {
            bombX = (int)playerX;
            bombY = (int)playerY;
            isBombed = true;
            upStop = downStop = leftStop = rightStop = 0;
        }
    }

    void keyPressZ(float ElapseTime)
    {
        if (blockSize < 15)
        {
            blockAdder += 30 * ElapseTime;
            blockSize = 8 + (int)blockAdder;
        }
    }
    void keyPressX(float ElapseTime)
    {
        if (blockSize > 1)
        {
            blockAdder -= 30 * ElapseTime;
            blockSize = 8 + (int)blockAdder;
        }
    }
    bool checkBox(int x, int y, wchar_t Character = L'#') { return (map[y * fieldWidth + x] == Character); }
    void onUserUpdate(float ElapseTime)
    {
        Clear();
        movingEntity(ElapseTime, &isMoving, &dirX, &dirY,
                     &playerX, &playerY, targetX, targetY);

        for (int i = 0; i < VenemyX.size(); i++)
        {
            movingEntity(ElapseTime, &VisMoving[i], &VdirX[i], &VdirY[i], &VenemyX[i],
                         &VenemyY[i], VtargetX[i], VtargetY[i]);
            if (!VisMoving[i])
            {
                int move = 1 + (rand() % 4);
                switch (move)
                {
                case 1:
                    moveEntity(&VisMoving[i], VenemyX[i] + 1, VenemyY[i], &VtargetX[i], &VtargetY[i], &VdirX[i], 'D');
                    break;
                case 2:
                    moveEntity(&VisMoving[i], VenemyX[i] - 1, VenemyY[i], &VtargetX[i], &VtargetY[i], &VdirX[i], 'A');
                    break;
                case 3:
                    moveEntity(&VisMoving[i], VenemyX[i], VenemyY[i] + 1, &VtargetX[i], &VtargetY[i], &VdirY[i], 'S');
                    break;
                case 4:
                    moveEntity(&VisMoving[i], VenemyX[i], VenemyY[i] - 1, &VtargetX[i], &VtargetY[i], &VdirY[i], 'W');
                    break;
                }
            }
            DrawBox(blockSize,
                    blockSize, midX + (VenemyX[i] * blockSize) - (playerX * blockSize),
                    midY + (VenemyY[i] * blockSize) - (playerY * blockSize), L'E');
        }

        DrawBox(blockSize, blockSize, midX, midY, L'P');

        if (isBombed)
        {
            bombTimer -= ElapseTime;
            if (bombTimer < 1)
            {
                if (bombTimer <= 0)
                {
                    bombTimer = 3.f;
                    isBombed = false;
                    map[bombY * fieldWidth + bombX] = L' ';
                    for (int u = 1; u <= upStop; u++)
                        map[(bombY - u) * fieldWidth + bombX] = L' ';
                    for (int u = 1; u <= downStop; u++)
                        map[(bombY + u) * fieldWidth + bombX] = L' ';
                    for (int u = 1; u <= rightStop; u++)
                        map[bombY * fieldWidth + bombX + u] = L' ';
                    for (int u = 1; u <= leftStop; u++)
                        map[bombY * fieldWidth + bombX - u] = L' ';
                }
                else
                {
                    map[bombY * fieldWidth + bombX] = L'F';
                    for (int u = 1; u < bombRange; u++)
                    {
                        if (checkBox(bombX, bombY - u))
                            break;
                        else if (upStop == u || checkBox(bombX, bombY - u, L'S'))
                        {
                            map[(bombY - u) * fieldWidth + bombX] = L'F';
                            upStop = u;
                            break;
                        }
                        upStop = u;
                        map[(bombY - u) * fieldWidth + bombX] = L'F';
                    }
                    for (int u = 1; u < bombRange; u++)
                    {
                        if (checkBox(bombX, bombY + u))
                            break;
                        else if (downStop == u || checkBox(bombX, bombY + u, L'S'))
                        {
                            map[(bombY + u) * fieldWidth + bombX] = L'F';
                            downStop = u;
                            break;
                        }
                        downStop = u;
                        map[(bombY + u) * fieldWidth + bombX] = L'F';
                    }
                    for (int u = 1; u < bombRange; u++)
                    {
                        if (checkBox(bombX + u, bombY))
                            break;
                        else if (rightStop == u || checkBox(bombX + u, bombY, L'S'))
                        {
                            map[bombY * fieldWidth + bombX + u] = L'F';
                            rightStop = u;
                            break;
                        }
                        rightStop = u;
                        map[bombY * fieldWidth + bombX + u] = L'F';
                    }
                    for (int u = 1; u < bombRange; u++)
                    {
                        if (checkBox(bombX - u, bombY))
                            break;
                        else if (leftStop == u || checkBox(bombX - u, bombY, L'S'))
                        {
                            map[bombY * fieldWidth + bombX - u] = L'F';
                            leftStop = u;
                            break;
                        }
                        leftStop = u;
                        map[bombY * fieldWidth + bombX - u] = L'F';
                    }
                }
            }
            else
                map[bombY * fieldWidth + bombX] = L'B';
        }

        for (int py = 0; py < fieldHeight; py++)
            for (int px = 0; px < fieldWidth; px++)
                if (map[py * fieldWidth + px] == L'#')
                    DrawBox(blockSize, blockSize, midX + (px * blockSize) - (playerX * blockSize), midY + (py * blockSize) - (playerY * blockSize), S1);
                else if (map[py * fieldWidth + px] == L'S')
                    DrawBox(blockSize, blockSize, midX + (px * blockSize) - (playerX * blockSize), midY + (py * blockSize) - (playerY * blockSize), S4);
                else if (map[py * fieldWidth + px] == L'B')
                    Drawer::DrawCircle(
                        this, (midX + ((int)blockSize / 2)) + (px * blockSize) - (playerX * blockSize),
                        (midY + ((int)blockSize / 2)) + (py * blockSize) - (playerY * blockSize),
                        (int)blockSize / 2 - 1, S3);
                else if (map[py * fieldWidth + px] == L'F')
                    Drawer::DrawCircle(
                        this, (midX + ((int)blockSize / 2)) + (px * blockSize) - (playerX * blockSize),
                        (midY + ((int)blockSize / 2)) + (py * blockSize) - (playerY * blockSize),
                        (int)blockSize / 2, S4);
    }
};

int main(int argv, char **argc)
{
    WWindow *window = new WWindow("Test", 80, 80, 8);
    window->run();
    return 0;
}
