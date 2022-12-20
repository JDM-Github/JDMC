#include "JDM.h"

using namespace std;

wstring Ubricks =
    (L"5DDDDDD15DD5\n"
     L"D5555551D551\n"
     L"D5555551D551\n"
     L"D5555551D551\n"
     L"D55555511115\n"
     L"D5555551DDD1\n"
     L"D5555551D551\n"
     L"D555551D5551\n"
     L"1115551D5551\n"
     L"D55111D55551\n"
     L"D555D1D55551\n"
     L"511111D11111\n");

wstring blocks =
    (L"588888888881\n"
     L"858888888811\n"
     L"885888888111\n"
     L"888555555111\n"
     L"888555555111\n"
     L"888555555111\n"
     L"888555555111\n"
     L"888555555111\n"
     L"888555555111\n"
     L"881111111511\n"
     L"811111111151\n"
     L"111111111115\n");

wstring secretBox =
    (L" 5555555555 \n"
     L"577777777771\n"
     L"571777777171\n"
     L"577755517771\n"
     L"577511151771\n"
     L"577117751771\n"
     L"577777751771\n"
     L"577775517771\n"
     L"577777777771\n"
     L"571775177171\n"
     L"577777777771\n"
     L"111111111111\n");

wstring bricks =
    (L"888888888888\n"
     L"555551555551\n"
     L"555551555551\n"
     L"111111111111\n"
     L"551555551555\n"
     L"551555551555\n"
     L"111111111111\n"
     L"555551555551\n"
     L"555551555551\n"
     L"111111111111\n"
     L"551555551555\n"
     L"111111111111\n");

wstring cloud1 =
    (L"       11111        \n"
     L"     1100000111     \n"
     L"    100440040001 11 \n"
     L"  110040000040001001\n"
     L"11000000000000000001\n"
     L"10000000000000000001\n"
     L"1000000000000000001 \n"
     L" 110400000040040011 \n"
     L"   11044444044000001\n"
     L"     100000100010011\n"
     L"      11111 111 11  \n");

class Mario
{
public:
    char dir = 'N';
    int width, height;
    float x, y, speed;
    float accel = 0.f, velocity = 0.f;
    bool onAir = false;

    int currentFrame = 0;
    wstring MarioFrame[2];

public:
    Mario()
    {
        MarioFrame[0] += L"   55555    \n";
        MarioFrame[0] += L"  555555555 \n";
        MarioFrame[0] += L"  111FF1F   \n";
        MarioFrame[0] += L" 1F1FFF1FFF \n";
        MarioFrame[0] += L" 1F11FFF1FFF\n";
        MarioFrame[0] += L" 11FFFF1111 \n";
        MarioFrame[0] += L"   FFFFFFF  \n";
        MarioFrame[0] += L" 5552552555 \n";
        MarioFrame[0] += L"555522225555\n";
        MarioFrame[0] += L"FF52F22F25FF\n";
        MarioFrame[0] += L"FFF222222FFF\n";
        MarioFrame[0] += L" 1112222111 \n";
        MarioFrame[0] += L"11111  11111\n";

        MarioFrame[1] += L"    55555   \n";
        MarioFrame[1] += L" 555555555  \n";
        MarioFrame[1] += L"   F1FF111  \n";
        MarioFrame[1] += L" FFF1FFF1F1 \n";
        MarioFrame[1] += L"FFF1FFF11F1 \n";
        MarioFrame[1] += L" 1111FFFF11 \n";
        MarioFrame[1] += L"  FFFFFFF   \n";
        MarioFrame[1] += L" 5552552555 \n";
        MarioFrame[1] += L"555522225555\n";
        MarioFrame[1] += L"FF52F22F25FF\n";
        MarioFrame[1] += L"FFF222222FFF\n";
        MarioFrame[1] += L" 1112222111 \n";
        MarioFrame[1] += L"11111  11111\n";
    }
};

class WWindow : public Window
{
public:
    Mario *mario;
    float cloudCD = 0.5;

    int blockSize = 12;
    int FieldWidth = 120;
    int FieldHeight = 13;

    float cameraX = 0.f;
    float cameraY = 0.f;

    float gravity = 200.f;

    bool gameOver = false;

    vector<int> blockW;
    vector<int> blockH;
    vector<float> blockX;
    vector<float> blockY;
    vector<wchar_t> blockType;

    vector<float> cloudX;
    vector<float> cloudY;
    wstring map;

public:
    WWindow(const char *Title, uint16_t Width, uint16_t Height, uint8_t fontSize)
        : Window(Title, Width, Height, fontSize) { keyPressValue = 0; }

    void applyGravity(float ElapseTime, float *vel, float *accel, float *EX, float *EY, int width, int height, char dir, bool *inAir)
    {
        *accel += gravity * ElapseTime;
        if (*accel >= 30)
            *inAir = true;
        if (*accel >= gravity)
            *accel = gravity;
        *vel += *accel * ElapseTime;
        for (int i = 0; i < blockW.size(); i++)
        {
            if (collide_box(*EX, *EY + *vel * ElapseTime + 1, width, height, blockW[i], blockH[i], blockX[i] - cameraX, blockY[i] + 1 - cameraY))
            {
                if (collide_box(*EX, *EY + *vel * ElapseTime + 1, width, height, blockW[i], 1, blockX[i] - cameraX, blockY[i] + 1 - cameraY + blockH[i] + 1))
                {
                    *accel = gravity / 4;
                    *vel = 0;
                    return;
                }
                *inAir = false;
                *vel /= 2;
                return;
            }
        }
        *EY += *vel * ElapseTime;
    }

    void onUserCreate()
    {
        mario = new Mario();
        mario->width = mario->height = blockSize;
        mario->speed = 35;
        mario->x = 24;
        mario->y = ScreenHeight - (blockSize * 3 + 4);

        map += L"                  SSSSSSSSS                                                                                             ";
        map += L"                   SSSSSSS                                                                                              ";
        map += L"                    SSSSS                                                                                               ";
        map += L"                     SSS                                                                                                ";
        map += L"                                                                                                                        ";
        map += L"                                              BAABBB                                                                    ";
        map += L"                                                                                                                        ";
        map += L"                                                                                                                        ";
        map += L"                      SS             BABB     BBBBBB                   S   S                                            ";
        map += L"                     SSSS                                             SS   SS                                           ";
        map += L"                    SSSSSS                                           SSS   SSS                                          ";
        map += L"########################################################################   #############################################";
        map += L"########################################################################   #############################################";

        for (int py = 0; py < FieldHeight; py++)
            for (int px = 0; px < FieldWidth; px++)
            {
                if (map[py * FieldWidth + px] != L' ')
                {
                    blockType.push_back(map[py * FieldWidth + px]);
                    blockW.push_back(blockSize - 1);
                    blockH.push_back(blockSize - 1);
                    blockX.push_back(px * blockSize);
                    blockY.push_back(py * blockSize);
                }
            }

        cloudX.push_back(ScreenWidth);
        cloudY.push_back(10 + (rand() % 40));
    }

    void moveLeft(float ElapseTime)
    {
        for (int i = 0; i < blockW.size(); i++)
        {
            if (collide_box(mario->x - (mario->speed * ElapseTime) - 1, mario->y + 1, mario->width, mario->height, blockW[i], blockH[i], blockX[i] - cameraX, blockY[i] + 1 - cameraY))
                return;
        }
        mario->x -= mario->speed * ElapseTime;
        mario->currentFrame = 1;
        mario->dir = 'L';
    }

    void moveRight(float ElapseTime)
    {
        for (int i = 0; i < blockW.size(); i++)
        {
            if (collide_box(mario->x + (mario->speed * ElapseTime), mario->y + 1, mario->width, mario->height, blockW[i], blockH[i], blockX[i] - cameraX, blockY[i] + 1 - cameraY))
                return;
        }
        mario->x += mario->speed * ElapseTime;
        mario->currentFrame = 0;
        mario->dir = 'R';
    }

    void onUserUpdate(float ElapseTime)
    {
        Clear(L' ', (FG_BLACK | BG_LBLUE));

        applyGravity(ElapseTime, &mario->velocity, &mario->accel, &mario->x, &mario->y, mario->width, mario->height, mario->dir, &mario->onAir);
        if (keyboard.Keys['D'].isHeld)
        {
            // mario->x += mario->speed * ElapseTime;
            moveRight(ElapseTime);
            if (mario->x > ScreenWidth / 2)
            {
                cameraX += mario->speed * ElapseTime;
                mario->x = ScreenWidth / 2;
            }
        }
        else if (keyboard.Keys['A'].isHeld)
            moveLeft(ElapseTime);
        if (keyboard.Keys['J'].isHeld)
        {
            if (!mario->onAir)
            {
                mario->onAir = true;
                mario->velocity = -(gravity / 1.35);
            }
        }

        for (int i = 0; i < cloudX.size(); i++)
        {
            cloudX[i] -= 5 * ElapseTime;
            DrawCString(cloudX[i], cloudY[i], cloud1, 1);
        }
        DrawCString(mario->x, mario->y, mario->MarioFrame[mario->currentFrame], 1);

        for (int py = 0; py < FieldHeight; py++)
            for (int px = 0; px < FieldWidth; px++)
            {
                if (map[py * FieldWidth + px] == L'#')
                    DrawCString(px * blockSize - cameraX, py * blockSize, Ubricks, 1);
                else if (map[py * FieldWidth + px] == L'B')
                    DrawCString(px * blockSize - cameraX, py * blockSize, bricks, 1);
                else if (map[py * FieldWidth + px] == L'S')
                    DrawCString(px * blockSize - cameraX, py * blockSize, blocks, 1);
                else if (map[py * FieldWidth + px] == L'A')
                    DrawCString(px * blockSize - cameraX, py * blockSize, secretBox, 1);
            }

        cloudCD -= ElapseTime;
        if (cloudCD <= 0)
        {
            cloudCD = 6.f;
            cloudX.push_back(ScreenWidth);
            cloudY.push_back(10 + (rand() % 50));
        }
    }
};

int main(int argv, char **argc)
{
    WWindow *window = new WWindow("Mario Game", 180, 156, 4);
    window->run();
    return 0;
}
