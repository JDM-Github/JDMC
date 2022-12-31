#define JGETMOUSEPOS JTRUE
#include "JDM.hpp"

JCLASS Pacman {
JPUBLIC:
    JWSTR PacmanDesign[5];
    JFLOAT x = 10.f, y = 15.f;
    JINT DIndex = 1;
    JINT Speed = 5;

    JCHAR DirectionX = 'N';
    JCHAR DirectionY = 'N';
    JINT targetX, targetY;

JPUBLIC:
    Pacman() {
        PacmanDesign[0] += L" 666 \n";
        PacmanDesign[0] += L"66666\n";
        PacmanDesign[0] += L"66666\n";
        PacmanDesign[0] += L"66666\n";
        PacmanDesign[0] += L" 666 \n";

        PacmanDesign[1] += L"     \n";
        PacmanDesign[1] += L"6   6\n";
        PacmanDesign[1] += L"66 66\n";
        PacmanDesign[1] += L"66666\n";
        PacmanDesign[1] += L" 666 \n";

        PacmanDesign[2] += L" 666 \n";
        PacmanDesign[2] += L"  666\n";
        PacmanDesign[2] += L"   66\n";
        PacmanDesign[2] += L"  666\n";
        PacmanDesign[2] += L" 666 \n";

        PacmanDesign[3] += L" 666 \n";
        PacmanDesign[3] += L"666  \n";
        PacmanDesign[3] += L"66   \n";
        PacmanDesign[3] += L"666  \n";
        PacmanDesign[3] += L" 666 \n";

        PacmanDesign[4] += L" 666 \n";
        PacmanDesign[4] += L"66666\n";
        PacmanDesign[4] += L"66 66\n";
        PacmanDesign[4] += L"6   6\n";
        PacmanDesign[4] += L"     \n";
    }
};

JCLASS Ghost {
JPUBLIC:
    JFLOAT x = 10.f, y = 9.f;
    JBOOL Moving = JFALSE;
    JINT DIndex = 0;
    JINT Speed = 4 + (rand() % 2);
    JBOOL isDead = JFALSE;
    JFLOAT Respawn = 3;

    JCHAR DirectionX = 'N';
    JCHAR DirectionY = 'N';
    JINT targetX, targetY;
    Color ghostColor;
    JWSTR GhostDesign[3];

JPUBLIC:
    Ghost(Color gColor) : ghostColor(gColor) {
        GhostDesign[0] += L" aaa \n";
        GhostDesign[0] += L"a7a7a\n";
        GhostDesign[0] += L"aaaaa\n";
        GhostDesign[0] += L"aaaaa\n";
        GhostDesign[0] += L"a a a\n";

        GhostDesign[1] += L" aaa \n";
        GhostDesign[1] += L"aaaaa\n";
        GhostDesign[1] += L"aaaaa\n";
        GhostDesign[1] += L"aaaaa\n";
        GhostDesign[1] += L"a a a\n";

        GhostDesign[2] += L"     \n";
        GhostDesign[2] += L" F F \n";
        GhostDesign[2] += L" F F \n";
        GhostDesign[2] += L"     \n";
        GhostDesign[2] += L"     \n";
    }

};

JCLASS PacmanGame : JPUBLIC JWINDOW {
JPRIVATE:
    JENUM Block{
        NO_UD, NO_UDR, NO_UDL,
        NO_LR, NO_LRU, NO_LRD,
        NO_UL, NO_UR, NO_DR,
        NO_DL, NO_U, NO_D,
        NO_L, NO_R, HAVE_ALL, NO_ALL,
    };

    JBOOL GameStart = JFALSE;
    JBOOL GameOver = JFALSE;

    JWSTR Map;
    JINT MapWidth = 21;
    JINT MapHeight = 21;
    JINT BlockSize = 5;

    JBOOL isPower = JFALSE;
    JFLOAT PowerDuration = 5;

    JWSTR AllBlocks[20];
    JWSTR Foods[2];
    JWSTR Opening;

    JBOOL Moving = JFALSE;
    Pacman pacman = Pacman();
    JVECTOR<JSP<Ghost>> allGhost;

JPUBLIC:
    PacmanGame() : JWINDOW("PacmanGame", 105, 120, 5, 5) { }
    JBOOL onUserCreate() {
        allGhost.push_back(JMS<Ghost>(FG_RED));
        allGhost.push_back(JMS<Ghost>(FG_GREEN));
        allGhost.push_back(JMS<Ghost>(FG_MAGENTA));
        allGhost.push_back(JMS<Ghost>(FG_CYAN));
        Map += L" #########.######### ";
        Map += L" #.................# ";
        Map += L" #B##.###.#.###.##B# ";
        Map += L" #.................# ";
        Map += L" #.##.#.##.##.#.##.# ";
        Map += L" #....#.......#....# ";
        Map += L" ##.#.### # ###.#.## ";
        Map += L" #..#.#       #.#..# ";
        Map += L"##.##.# ## ## #.##.##";
        Map += L"......         ......";
        Map += L"#####.# ## ## #.#####";
        Map += L"    #.#       #.#    ";
        Map += L" ####.# ## ## #.#### ";
        Map += L" #.................# ";
        Map += L" #.##.#########.##.# ";
        Map += L" #B.#.....P.....#.B# ";
        Map += L" ##.###.#####.###.## ";
        Map += L" #...##...#...##...# ";
        Map += L" #.####.#.#.#.####.# ";
        Map += L" #......#...#......# ";
        Map += L" #########.######### ";

        Foods[0] += L" FFF \n";
        Foods[0] += L"FFFFF\n";
        Foods[0] += L"FFFFF\n";
        Foods[0] += L"FFFFF\n";
        Foods[0] += L" FFF \n";

        Foods[1] += L"     \n";
        Foods[1] += L"     \n";
        Foods[1] += L"  7  \n";
        Foods[1] += L"     \n";
        Foods[1] += L"     \n";

        Opening += L"     \n";
        Opening += L"44444\n";
        Opening += L"     \n";
        Opening += L"     \n";
        Opening += L"     \n";

        AllBlocks[0] += L"11111\n";        AllBlocks[1] += L"1111 \n";        AllBlocks[2] += L" 1111\n";
        AllBlocks[0] += L"     \n";        AllBlocks[1] += L"    1\n";        AllBlocks[2] += L"1    \n";
        AllBlocks[0] += L"     \n";        AllBlocks[1] += L"    1\n";        AllBlocks[2] += L"1    \n";
        AllBlocks[0] += L"     \n";        AllBlocks[1] += L"    1\n";        AllBlocks[2] += L"1    \n";
        AllBlocks[0] += L"11111\n";        AllBlocks[1] += L"1111 \n";        AllBlocks[2] += L" 1111\n";

        AllBlocks[3] += L"1   1\n";        AllBlocks[4] += L" 111 \n";        AllBlocks[5] += L"1   1\n";
        AllBlocks[3] += L"1   1\n";        AllBlocks[4] += L"1   1\n";        AllBlocks[5] += L"1   1\n";
        AllBlocks[3] += L"1   1\n";        AllBlocks[4] += L"1   1\n";        AllBlocks[5] += L"1   1\n";
        AllBlocks[3] += L"1   1\n";        AllBlocks[4] += L"1   1\n";        AllBlocks[5] += L"1   1\n";
        AllBlocks[3] += L"1   1\n";        AllBlocks[4] += L"1   1\n";        AllBlocks[5] += L" 111 \n";

        AllBlocks[6] += L" 1111\n";        AllBlocks[7] += L"1111 \n";        AllBlocks[8] += L"    1\n";
        AllBlocks[6] += L"1    \n";        AllBlocks[7] += L"    1\n";        AllBlocks[8] += L"    1\n";
        AllBlocks[6] += L"1    \n";        AllBlocks[7] += L"    1\n";        AllBlocks[8] += L"    1\n";
        AllBlocks[6] += L"1    \n";        AllBlocks[7] += L"    1\n";        AllBlocks[8] += L"    1\n";
        AllBlocks[6] += L"1    \n";        AllBlocks[7] += L"    1\n";        AllBlocks[8] += L"1111 \n";

        AllBlocks[9] += L"1    \n";        AllBlocks[10] += L"11111\n";        AllBlocks[11] += L"     \n";
        AllBlocks[9] += L"1    \n";        AllBlocks[10] += L"     \n";        AllBlocks[11] += L"     \n";
        AllBlocks[9] += L"1    \n";        AllBlocks[10] += L"     \n";        AllBlocks[11] += L"     \n";
        AllBlocks[9] += L"1    \n";        AllBlocks[10] += L"     \n";        AllBlocks[11] += L"     \n";
        AllBlocks[9] += L" 1111\n";        AllBlocks[10] += L"     \n";        AllBlocks[11] += L"11111\n";

        AllBlocks[12] += L"1    \n";        AllBlocks[13] += L"    1\n";        AllBlocks[14] += L" 111 \n";
        AllBlocks[12] += L"1    \n";        AllBlocks[13] += L"    1\n";        AllBlocks[14] += L"1   1\n";
        AllBlocks[12] += L"1    \n";        AllBlocks[13] += L"    1\n";        AllBlocks[14] += L"1   1\n";
        AllBlocks[12] += L"1    \n";        AllBlocks[13] += L"    1\n";        AllBlocks[14] += L"1   1\n";
        AllBlocks[12] += L"1    \n";        AllBlocks[13] += L"    1\n";        AllBlocks[14] += L" 111 \n";

        AllBlocks[15] += L"     \n";
        AllBlocks[15] += L"     \n";
        AllBlocks[15] += L"     \n";
        AllBlocks[15] += L"     \n";
        AllBlocks[15] += L"     \n";

        JRETURN JTRUE;
    }

    Block CheckBlock(JINT x, JINT y) {
        JBOOL UP = (y - 1 >= 0 && GetElements(x, y-1) == '#');
        JBOOL DOWN = (y + 1 < MapHeight && GetElements(x, y+1) == '#');
        JBOOL LEFT = (x - 1 >= 0 && GetElements(x-1, y) == '#');
        JBOOL RIGHT = (x + 1 < MapWidth && GetElements(x+1, y) == '#');

        JIF(UP && DOWN && LEFT && RIGHT) JRETURN NO_ALL;
        JIF (UP) {
            JIF(DOWN && LEFT) JRETURN NO_R;
            JIF(DOWN && RIGHT) JRETURN NO_L;
            JIF(LEFT && RIGHT) JRETURN NO_D;
            JIF(DOWN) JRETURN NO_LR;
            JIF(RIGHT) JRETURN NO_DL;
            JIF(LEFT) JRETURN NO_DR;
            JRETURN NO_LRD;
        }
        JIF (DOWN) {
            JIF(LEFT && RIGHT) JRETURN NO_U;
            JIF(RIGHT) JRETURN NO_UL;
            JIF(LEFT) JRETURN NO_UR;
            JRETURN NO_LRU;
        }
        JIF (LEFT) {
            JIF(RIGHT) JRETURN NO_UD;
            JRETURN NO_UDR;
        }
        JIF (RIGHT) {
            JRETURN NO_UDL;
        }
        JRETURN HAVE_ALL;
    }

    JVOID Render(JWSTR Design, Color color, JFLOAT x, JFLOAT y) {
        JSHORT x_adder = JNONE, y_adder = JNONE;
        JFOR(JSHORT i = JNONE; i < Design.size(); i++) {
            JIF(Design[i] == JDM::NEWLINE) {
                x_adder = JNONE;
                y_adder++;
                JCONTINUE;
            }
            x_adder++;
            JIF(Design[i] == JDM::BLANK) JCONTINUE;
            DrawCycle({((x < 0) ? GetWidth() - std::abs(x) : x) + x_adder - 1,
                       ((y < 0) ? GetHeight() - std::abs(y) : y) + y_adder}, JDM::PIXEL_SOLID, ((Design[i] == L'a')
                ? color : (getColor(Design[i])) | JDM::BG_BLACK));
        }
    }

    JWCHAR GetElements(JINT x, JINT y) { JRETURN Map[x + y * MapWidth]; }
    JVOID SetElements(JINT x, JINT y, JWCHAR Value) { Map[x + y * MapWidth] = Value; }

    JVOID MoveAnimation(JCHAR DirectionX, JCHAR DirectionY, JINT Speed, JFLOAT &x, JFLOAT &y, JINT &DIndex, JBOOL &Moving, JINT targetX, JINT targetY, JBOOL isPacman) {
        JIF (DirectionX != 'N') {
            x += (DirectionX == 'A') ? -Speed * ElapseTime : Speed * ElapseTime;
            JIF ((DirectionX == 'A') ? (x < targetX) : (x > targetX)) {
                x = (targetX < 0) ? MapWidth - 1: targetX % MapWidth;
                JIF(isPacman) {
                    DIndex = (DirectionX == 'A') ? 2 : 3;
                    ResetAndSet();
                } JELSE { DIndex = 0; Moving = JFALSE; }
            }
            JELSE JIF((DirectionX == 'A') ? (x < (targetX + 0.4)) : (x > (targetX - 0.4)))
                DIndex = (!isPacman);
            JELSE JIF ((DirectionX == 'A') ? (x < (targetX + 0.8)) : (x > (targetX - 0.8)))
                DIndex = (isPacman) ? ((DirectionX == 'A') ? 2 : 3) : 0;

        }
        JELSE JIF (DirectionY != 'N') {
            y += (DirectionY == 'W') ? -Speed * ElapseTime : Speed * ElapseTime;
            JIF ((DirectionY == 'W') ? (y < targetY) : (y > targetY)) {
                y = (targetY < 0) ? MapHeight - 1: targetY % MapHeight;
                JIF(isPacman) {
                    DIndex = (DirectionY == 'W') ? 1 : 4;
                    ResetAndSet();
                } JELSE { DIndex = 0; Moving = JFALSE; }
            }
            JELSE JIF((DirectionY == 'W') ? (y < (targetY + 0.4)) : (y > (targetY - 0.4)))
                DIndex = (!isPacman);
            JELSE JIF ((DirectionX == 'W') ? (y < (targetY + 0.8)) : (y > (targetY - 0.8)))
                DIndex = (isPacman) ? ((DirectionY == 'W') ? 1 : 4) : 0;
        }
    }

    JVOID ResetAndSet() {
        Moving = JFALSE;
        JIF (GetElements(JSTATICC<JINT>(pacman.x), JSTATICC<JINT>(pacman.y)) == L'.')
            SetElements(JSTATICC<JINT>(pacman.x), JSTATICC<JINT>(pacman.y), L' ');
        JELSE JIF (GetElements(JSTATICC<JINT>(pacman.x), JSTATICC<JINT>(pacman.y)) == L'B') {
            SetElements(JSTATICC<JINT>(pacman.x), JSTATICC<JINT>(pacman.y), L' ');
            PowerDuration = 5;
            isPower = JTRUE;
        }
    }

    JBOOL CheckUp(JFLOAT x, JFLOAT y) { JRETURN (y - 1 < 0 || GetElements(JSTATICC<JINT>(x), JSTATICC<JINT>(y - 1)) != L'#'); }
    JBOOL CheckDown(JFLOAT x, JFLOAT y) { JRETURN (y + 1 >= MapHeight || GetElements(JSTATICC<JINT>(x), JSTATICC<JINT>(y + 1)) != L'#'); }
    JBOOL CheckLeft(JFLOAT x, JFLOAT y) { JRETURN (x - 1 < 0 || GetElements(JSTATICC<JINT>(x - 1), JSTATICC<JINT>(y)) != L'#'); }
    JBOOL CheckRight(JFLOAT x, JFLOAT y) { JRETURN (x + 1 >= MapWidth || GetElements(JSTATICC<JINT>(x + 1), JSTATICC<JINT>(y)) != L'#'); }

    JBOOL onUserUpdate() {
        Clear(BLANK, BG_BLACK);
        JFLOAT StartX = 0.f, StartY = 10.f;

        JIF(keyboard.Keys[Keys::J_PKEY].isPressed) GameStart = JTRUE;
        JIF(GameStart && !GameOver) {
            JIF (!Moving) {
                JIF (keyboard.Keys[Keys::J_AKEY].isHeld) {
                    JIF (CheckLeft(pacman.x, pacman.y)) {
                        pacman.DirectionX = 'A';
                        pacman.DirectionY = 'N';
                    }
                }
                JELSE JIF (keyboard.Keys[Keys::J_DKEY].isHeld) {
                    JIF (CheckRight(pacman.x, pacman.y)) {
                        pacman.DirectionX = 'D';
                        pacman.DirectionY = 'N';
                    }
                }
                JELSE JIF (keyboard.Keys[Keys::J_WKEY].isHeld) {
                    JIF (CheckUp(pacman.x, pacman.y)) {
                        pacman.DirectionY = 'W';
                        pacman.DirectionX = 'N';
                    }
                }
                JELSE JIF (keyboard.Keys[Keys::J_SKEY].isHeld) {
                    JIF (CheckDown(pacman.x, pacman.y)) {
                        pacman.DirectionY = 'S';
                        pacman.DirectionX = 'N';
                    }
                }

                JIF (pacman.DirectionX == 'A') {
                    JIF (CheckLeft(pacman.x, pacman.y)) {
                        pacman.targetX = pacman.x - 1;
                        Moving = JTRUE;
                        pacman.DIndex = 0;
                    }
                } JELSE JIF (pacman.DirectionX == 'D') {
                    JIF (CheckRight(pacman.x, pacman.y)) {
                        pacman.targetX = pacman.x + 1;
                        Moving = JTRUE;
                        pacman.DIndex = 0;
                    }
                } JELSE JIF (pacman.DirectionY == 'W') {
                    JIF (CheckUp(pacman.x, pacman.y)) {
                        pacman.targetY = pacman.y - 1;
                        Moving = JTRUE;
                        pacman.DIndex = 0;
                    }
                } JELSE JIF (pacman.DirectionY == 'S') {
                    JIF (CheckDown(pacman.x, pacman.y)) {
                        pacman.targetY = pacman.y + 1;
                        Moving = JTRUE;
                        pacman.DIndex = 0;
                    }
                }
            } JELSE MoveAnimation(pacman.DirectionX, pacman.DirectionY, pacman.Speed, pacman.x, pacman.y, pacman.DIndex, Moving, pacman.targetX, pacman.targetY, JTRUE);
        }

        JFOR(JINT y = 0; y < MapHeight; y++) {
            JFOR(JINT x = 0; x < MapWidth; x++) {
                JSWITCH (GetElements(x, y)) {
                    JCASE L'#':
                        DrawCString({StartX + x * BlockSize, StartY + y * BlockSize}, AllBlocks[CheckBlock(x, y)], JTRUE); JBREAK;
                    JCASE L'B': DrawCString({StartX + x * BlockSize, StartY + y * BlockSize}, Foods[0], JTRUE); JBREAK;
                    JCASE L'.': DrawCString({StartX + x * BlockSize, StartY + y * BlockSize}, Foods[1], JTRUE); JBREAK;
                    JCASE L'-': DrawCString({StartX + x * BlockSize, StartY + y * BlockSize}, Opening, JTRUE); JBREAK;
                }
            }
        }
        JFOR (JAUTO ghost : allGhost) {
            JIF (GameStart && !GameOver) {
                JIF(!ghost->Moving && !ghost->isDead) {
                    JVECTOR<JINT> possibleMove;
                    JVECTOR<JINT> allDistance;
                    JIF(CheckUp(ghost->x, ghost->y)) {
                        JINT x = (pacman.x - ghost->x) + (rand() % 2);
                        JINT y = (pacman.y - (ghost->y - 1)) + (rand() % 2);
                        possibleMove.push_back(0);
                        allDistance.push_back((x*x) + (y*y));
                    }
                    JIF(CheckDown(ghost->x, ghost->y)) {
                        JINT x = (pacman.x - ghost->x) + (rand() % 2);
                        JINT y = (pacman.y - (ghost->y + 1)) + (rand() % 2);
                        possibleMove.push_back(1);
                        allDistance.push_back((x*x) + (y*y));
                    }
                    JIF(CheckLeft(ghost->x, ghost->y)) {
                        JINT x = (pacman.x - (ghost->x-1)) + (rand() % 2);
                        JINT y = (pacman.y - ghost->y) + (rand() % 2);
                        possibleMove.push_back(2);
                        allDistance.push_back((x*x) + (y*y));
                    }
                    JIF(CheckRight(ghost->x, ghost->y)) {
                        JINT x = (pacman.x - (ghost->x+1)) + (rand() % 2);
                        JINT y = (pacman.y - ghost->y) + (rand() % 2);
                        possibleMove.push_back(3);
                        allDistance.push_back((x*x) + (y*y));
                    }
                    JINT Index = 0;
                    JINT Smallest = allDistance[0];
                    JFOR(JINT i = 0; i < allDistance.size(); i++) {
                        JIF ((isPower) ? (Smallest < allDistance[i]) : (Smallest > allDistance[i])) {
                            Index = i;
                            Smallest = allDistance[i];
                        }
                    }
                    JSWITCH(possibleMove[Index]) {
                        JCASE 0 :
                            ghost->DirectionY = 'W';
                            ghost->DirectionX = 'N';
                            ghost->targetY = ghost->y - 1;
                            ghost->Moving = JTRUE;
                            JBREAK;
                        JCASE 1 :
                            ghost->DirectionY = 'S';
                            ghost->DirectionX = 'N';
                            ghost->targetY = ghost->y + 1;
                            ghost->Moving = JTRUE;
                            JBREAK;
                        JCASE 2 :
                            ghost->DirectionX = 'A';
                            ghost->DirectionY = 'N';
                            ghost->targetX = ghost->x - 1;
                            ghost->Moving = JTRUE;
                            JBREAK;
                        JCASE 3 :
                            ghost->DirectionX = 'D';
                            ghost->DirectionY = 'N';
                            ghost->targetX = ghost->x + 1;
                            ghost->Moving = JTRUE;
                            JBREAK;
                    }
                }  JELSE MoveAnimation(ghost->DirectionX, ghost->DirectionY, ghost->Speed, ghost->x, ghost->y, ghost->DIndex, ghost->Moving, ghost->targetX, ghost->targetY, JFALSE);
            }
            JINT x = (ghost->x - pacman.x);
            JINT y = (ghost->y - pacman.y);
            JIF(!ghost->isDead && (x * x) + (y * y) <= 0) {
                JIF (isPower) {
                    ghost->DIndex = 2;
                    ghost->isDead = JTRUE;
                    ghost->Respawn = 3;
                } JELSE {
                    pacman.DIndex = 0;
                    pacman.DirectionX = 'N';
                    pacman.DirectionY = 'N';
                    GameOver = JTRUE;
                }
            }
            JIF (ghost->isDead) {
                ghost->DIndex = 2;
                ghost->Respawn -= ElapseTime;
                JIF (ghost->Respawn <= 0) {
                    ghost->isDead = JFALSE;
                    ghost->x = 10.f;
                    ghost->y = 9.f;
                    ghost->DIndex = 0;
                }
            }
            Render(ghost->GhostDesign[ghost->DIndex], ((isPower) ? FG_DARK_CYAN : ghost->ghostColor), StartX + ghost->x * BlockSize, StartY + ghost->y * BlockSize);
        }
        DrawCStringCycle({StartX + pacman.x * BlockSize, StartY + pacman.y * BlockSize}, pacman.PacmanDesign[pacman.DIndex], JTRUE);

        JIF (isPower) {
            PowerDuration -= ElapseTime;
            JIF (PowerDuration <= 0) {
                PowerDuration = 5;
                isPower = JFALSE;
            }
        }

        JRETURN JTRUE;
    }
};

JINT main()
{
    srand(std::time(JNONE));
    JMS<PacmanGame>()->Start();
    JRETURN JFALSE;
}
