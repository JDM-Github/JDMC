#include "JDM.h"

using namespace std;

class WWindow : public Window
{
public:
    char dir = 'N';
    int playerWidth;
    int playerHeight;

    float playerX;
    float playerY;

    bool inAir = false;
    bool gameOver = false;

    float playerSpeed = 25;
    float playerAccel = 0.f;
    float playerVel = 0.f;

    float gravity = 120.f;
    float Eaccelaration[100] = {0};
    float Evelocity[100] = {0};

    float cameraX = 0, cameraY = 0;

    wstring map;
    wstring spike;
    wstring Gletter;
    wstring Aletter;
    wstring Mletter;
    wstring Eletter;
    wstring Oletter;
    wstring Vletter;
    wstring Rletter;

    vector<char> blockType;
    vector<int> blockW;
    vector<int> blockH;
    vector<float> blockX;
    vector<float> blockY;

public:
    WWindow(const char *Title, uint16_t Width, uint16_t Height, uint8_t fontSize)
        : Window(Title, Width, Height, fontSize) { keyPressValue = 0; }

    void onUserCreate()
    {
        playerWidth = playerHeight = 10;
        playerX = (ScreenWidth / 2.0 - playerWidth / 2.0);
        playerY = 0.9 * ScreenHeight - playerHeight;

        map += L"                                                  ";
        map += L"                                                  ";
        map += L"      S                                           ";
        map += L"      #B#                      S                  ";
        map += L" SS  S      S                 #B#             S   ";
        map += L" #BBB#     #B#                               #B#  ";
        map += L"                    S    #B#           S          ";
        map += L"              #     #BB#             #BBB#        ";
        map += L"              #B#S        SSS#B#SSSSSSSSSSSSSSSS  ";
        map += L"##################################################";

        spike += L"          \n";
        spike += L"          \n";
        spike += L"    ^^    \n";
        spike += L"   ^^^^   \n";
        spike += L"  ^^^^^^  \n";
        spike += L" ^^^^^^^^ \n";
        spike += L"^^^^^^^^^^\n";
        spike += L"^^^^^^^^^^\n";
        spike += L"^^^^^^^^^^\n";
        spike += L"^^^^^^^^^^\n";

        Gletter += L"          \n";
        Gletter += L" ######## \n";
        Gletter += L" #      # \n";
        Gletter += L" #        \n";
        Gletter += L" #        \n";
        Gletter += L" #   #### \n";
        Gletter += L" #      # \n";
        Gletter += L" #      # \n";
        Gletter += L" ######## \n";
        Gletter += L"          \n";

        Aletter += L"          \n";
        Aletter += L" ######## \n";
        Aletter += L" #      # \n";
        Aletter += L" #      # \n";
        Aletter += L" #      # \n";
        Aletter += L" ######## \n";
        Aletter += L" #      # \n";
        Aletter += L" #      # \n";
        Aletter += L" #      # \n";
        Aletter += L"          \n";

        Mletter += L"          \n";
        Mletter += L" #      # \n";
        Mletter += L" ##    ## \n";
        Mletter += L" # #  # # \n";
        Mletter += L" #  ##  # \n";
        Mletter += L" #      # \n";
        Mletter += L" #      # \n";
        Mletter += L" #      # \n";
        Mletter += L" #      # \n";
        Mletter += L"          \n";

        Eletter += L"          \n";
        Eletter += L" ######## \n";
        Eletter += L" #        \n";
        Eletter += L" #        \n";
        Eletter += L" #####    \n";
        Eletter += L" #        \n";
        Eletter += L" #        \n";
        Eletter += L" #        \n";
        Eletter += L" ######## \n";
        Eletter += L"          \n";

        Oletter += L"          \n";
        Oletter += L" ######## \n";
        Oletter += L" #      # \n";
        Oletter += L" #      # \n";
        Oletter += L" #      # \n";
        Oletter += L" #      # \n";
        Oletter += L" #      # \n";
        Oletter += L" #      # \n";
        Oletter += L" ######## \n";
        Oletter += L"          \n";

        Vletter += L"          \n";
        Vletter += L" #      # \n";
        Vletter += L" #      # \n";
        Vletter += L" #      # \n";
        Vletter += L" #      # \n";
        Vletter += L" #      # \n";
        Vletter += L"  #    #  \n";
        Vletter += L"   #  #   \n";
        Vletter += L"    ##    \n";
        Vletter += L"          \n";

        Rletter += L"          \n";
        Rletter += L" #######  \n";
        Rletter += L" #      # \n";
        Rletter += L" #      # \n";
        Rletter += L" #      # \n";
        Rletter += L" #######  \n";
        Rletter += L" #     #  \n";
        Rletter += L" #      # \n";
        Rletter += L" #      # \n";
        Rletter += L"          \n";

        for (int py = 0; py < 10; py++)
            for (int px = 0; px < 50; px++)
            {
                if (map[py * 50 + px] != L' ')
                {
                    blockType.push_back(map[py * 50 + px]);
                    blockW.push_back(9);
                    blockH.push_back(9);
                    blockX.push_back(px * 10);
                    blockY.push_back(py * 10);
                }
            }
    }

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
            if (blockType[i] == L'S')
            {
                if (collide_box(*EX, *EY + *vel * ElapseTime, width, height, blockW[i] - 2, blockH[i] - 4, blockX[i] - cameraX + 1, blockY[i] + 1 - cameraY + 4))
                {
                    gameOver = true;
                    return;
                }
            }
            else if (collide_box(*EX, *EY + *vel * ElapseTime, width, height, blockW[i], blockH[i], blockX[i] - cameraX, blockY[i] + 1 - cameraY))
            {
                if (collide_box(*EX, *EY + *vel * ElapseTime, width, height, blockW[i], 1, blockX[i] - cameraX, blockY[i] + 1 - cameraY + blockH[i] + 1))
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

    void keyPressJ(float ElapseTime)
    {
        if (!inAir && !gameOver)
        {
            inAir = true;
            playerVel = -(gravity / 1.5);
        }
    }
    void keyPressA(float ElapseTime)
    {
        if (!gameOver)
        {
            if (cameraX < -(ScreenWidth / 2.0))
                return;
            for (int i = 0; i < blockW.size(); i++)
            {
                if (blockType[i] == L'S')
                {
                    if (collide_box(playerX, playerY, playerWidth, playerHeight, blockW[i] - 2, blockH[i], blockX[i] - (cameraX - playerSpeed * ElapseTime) + 1, blockY[i] + 1 - cameraY))
                        gameOver = true;
                }
                else if (collide_box(playerX, playerY, playerWidth, playerHeight, blockW[i], blockH[i], blockX[i] - (cameraX - playerSpeed * ElapseTime), blockY[i] + 1 - cameraY))
                    return;
            }
            cameraX -= playerSpeed * ElapseTime;
            dir = 'L';
        }
    }

    void keyPressD(float ElapseTime)
    {
        if (!gameOver)
        {
            for (int i = 0; i < blockW.size(); i++)
                if (blockType[i] == L'S')
                {
                    if (collide_box(playerX, playerY, playerWidth, playerHeight, blockW[i] - 2, blockH[i], blockX[i] - (cameraX + playerSpeed * ElapseTime) + 1, blockY[i] + 1 - cameraY))
                        gameOver = true;
                }
                else if (collide_box(playerX, playerY, playerWidth, playerHeight, blockW[i], blockH[i], blockX[i] - (cameraX + playerSpeed * ElapseTime), blockY[i] + 1 - cameraY))
                    return;
            cameraX += playerSpeed * ElapseTime;
            dir = 'R';
        }
    }

    wchar_t getBlockType(wchar_t typeB)
    {
        switch (typeB)
        {
        case L'#':
            return S1;
        case L'B':
            return S4;
        }
    }

    void onUserUpdate(float ElapseTime)
    {
        Clear();
        applyGravity(ElapseTime, &playerVel, &playerAccel, &playerX, &playerY, playerWidth, playerHeight, dir, &inAir);
        DrawBox(playerWidth, playerHeight, playerX, playerY);

        for (int i = 0; i < blockW.size(); i++)
        {
            if (blockType[i] == L'S')
                DrawString(blockX[i] - cameraX, blockY[i] - cameraY, spike, 1);
            else
                DrawBox(blockW[i] + 1, blockH[i] + 1, blockX[i] - cameraX, blockY[i] - cameraY, getBlockType(blockType[i]));
        }

        if (gameOver)
        {
            DrawString((ScreenWidth / 2.0) - 5 - (4 * 10), 10, Gletter);
            DrawString((ScreenWidth / 2.0) - 5 - (3 * 10), 10, Aletter);
            DrawString((ScreenWidth / 2.0) - 5 - (2 * 10), 10, Mletter);
            DrawString((ScreenWidth / 2.0) - 5 - (1 * 10), 10, Eletter);

            DrawString((ScreenWidth / 2.0) + 5 + (0 * 10), 10, Oletter);
            DrawString((ScreenWidth / 2.0) + 5 + (1 * 10), 10, Vletter);
            DrawString((ScreenWidth / 2.0) + 5 + (2 * 10), 10, Eletter);
            DrawString((ScreenWidth / 2.0) + 5 + (3 * 10), 10, Rletter);
        }
    }
};

int main(int argv, char **argc)
{
    WWindow *window = new WWindow("Test", 150, 100, 5);
    window->run();
    return 0;
}
