#include "JDM.h"

JCLASS SnakeAI : JPUBLIC JWINDOW {
JPRIVATE:

    JSTRUCT Apple { JINT X, Y; };
    JENUM AllMove { NONE, LEFT, RIGHT, UP, DOWN };
    JSTRUCT SnakeBody {
        JFLOAT X, Y, OX, OY;
        AllMove OM, CM;
        JBOOL Moving;
    };

    JINT Score = 0;
    JBOOL GameStart = JFALSE;
    AllMove OldMove;
    JFLOAT SnakeSpeed = 0.000;
    JCFLOAT CSnakeSpeed = 0.000;
    SnakeBody SnakeHead = {2, 7, 2, 7, NONE, NONE, JFALSE};
    JVECTOR<SnakeBody> SnakeTail;

    Apple CurrentApple;
    JWSTR SnakeHeadDesign;
    JWSTR SnaketailDesign;
    JWSTR AppleDesign;
    JINT MapWidth = 20;
    JINT MapHeight = 20;
    JINT AllMapSize = 400;
    JVECTOR<JVECTOR<INT>> HamiltonianCycle;

JPUBLIC:
    SnakeAI() : JWINDOW("Snake AI", 140, 100, 5, 5) {}
    JBOOL onUserCreate() {
        CurrentApple = {rand() % MapWidth, rand() % MapHeight};
        HamiltonianCycle = {
            {0x184, 0x183, 0x17E, 0x17D, 0X17C, 0X17B, 0X17A, 0X177, 0X176, 0X15B, 0x15A, 0x159, 0x140, 0x13F, 0X12E, 0X12D, 0X11C, 0X11B, 0X118, 0X117},
            {0x185, 0x182, 0x17F, 0x0CC, 0X0CD, 0X0CE, 0X179, 0X178, 0X175, 0X15C, 0x157, 0x158, 0x141, 0x13E, 0X12F, 0X12C, 0X11D, 0X11A, 0X119, 0X116},
            {0x186, 0x181, 0x180, 0x0CB, 0X0CA, 0X0CF, 0X172, 0X173, 0X174, 0X15D, 0x156, 0x155, 0x142, 0x13D, 0X130, 0X12B, 0X11E, 0X113, 0X114, 0X115},
            {0x187, 0x188, 0x005, 0x006, 0X0C9, 0X0D0, 0X171, 0X170, 0X16F, 0X15E, 0x153, 0x154, 0x143, 0x13C, 0X131, 0X12A, 0X11F, 0X112, 0X111, 0X110},
            {0x18A, 0x189, 0x004, 0x007, 0X0C8, 0X0D1, 0X16C, 0X16D, 0X16E, 0X15F, 0x152, 0x151, 0x144, 0x13B, 0X132, 0X129, 0X120, 0X10D, 0X10E, 0X10F},
            {0x18B, 0x18C, 0x003, 0x008, 0X0C7, 0X0D2, 0X16B, 0X16A, 0X169, 0X160, 0x14F, 0x150, 0x145, 0x13A, 0X133, 0X128, 0X121, 0X10C, 0X10B, 0X10A},
            {0x18E, 0x18D, 0x002, 0x009, 0X0C6, 0X0D3, 0X166, 0X167, 0X168, 0X161, 0x14E, 0x14D, 0x146, 0x139, 0X134, 0X127, 0X122, 0X107, 0X108, 0X109},
            {0x18F, 0x000, 0x001, 0x00A, 0X0C5, 0X0D4, 0X165, 0X164, 0X163, 0X162, 0x14B, 0x14C, 0x147, 0x138, 0X135, 0X126, 0X123, 0X106, 0X105, 0X104},
            {0x010, 0x00F, 0x00E, 0x00B, 0X0C4, 0X0D5, 0X0D6, 0X0D7, 0X0D8, 0X0D9, 0x14A, 0x149, 0x148, 0x137, 0X136, 0X125, 0X124, 0X101, 0X102, 0X103},
            {0x011, 0x012, 0x00D, 0x00C, 0X0C3, 0X0C2, 0X0C1, 0X0C0, 0X0BF, 0X0DA, 0x0EF, 0x0F0, 0x0F1, 0x0F2, 0X0F3, 0X0F4, 0X0F5, 0X100, 0X05F, 0X05E},
            {0x014, 0x013, 0x01E, 0x01F, 0X07E, 0X07F, 0X080, 0X081, 0X0BE, 0X0DB, 0x0EE, 0x0ED, 0x0EC, 0x0EB, 0X0AC, 0X0AB, 0X0F6, 0X0FF, 0X060, 0X05D},
            {0x015, 0x01C, 0x01D, 0x020, 0X07D, 0X084, 0X083, 0X082, 0X0BD, 0X0DC, 0x0E7, 0x0E8, 0x0E9, 0x0EA, 0X0AD, 0X0AA, 0X0F7, 0X0FE, 0X061, 0X05C},
            {0x016, 0x01B, 0x022, 0x021, 0X07C, 0X085, 0X088, 0X089, 0X0BC, 0X0DD, 0x0E6, 0x0E5, 0x0B0, 0x0AF, 0X0AE, 0X0A9, 0X0F8, 0X0FD, 0X062, 0X05B},
            {0x017, 0x01A, 0x023, 0x024, 0X07B, 0X086, 0X087, 0X08A, 0X0BB, 0X0DE, 0x0DF, 0x0E4, 0x0B1, 0x0A2, 0X0A3, 0X0A8, 0X0F9, 0X0FC, 0X063, 0X05A},
            {0x018, 0x019, 0x026, 0x025, 0X07A, 0X079, 0X08C, 0X08B, 0X0BA, 0X0B9, 0x0E0, 0x0E3, 0x0B2, 0x0A1, 0X0A4, 0X0A7, 0X0FA, 0X0FB, 0X064, 0X059},
            {0x029, 0x028, 0x027, 0x03A, 0X03B, 0X078, 0X08D, 0X092, 0X093, 0X0B8, 0x0E1, 0x0E2, 0x0B3, 0x0A0, 0X0A5, 0X0A6, 0X067, 0X066, 0X065, 0X058},
            {0x02A, 0x031, 0x032, 0x039, 0X03C, 0X077, 0X08E, 0X091, 0X094, 0X0B7, 0x0B6, 0x0B5, 0x0B4, 0x09F, 0X09E, 0X09D, 0X068, 0X055, 0X056, 0X057},
            {0x02B, 0x030, 0x033, 0x038, 0X03D, 0X076, 0X08F, 0X090, 0X095, 0X096, 0x097, 0x098, 0x099, 0x09A, 0X09B, 0X09C, 0X069, 0X054, 0X051, 0X050},
            {0x02C, 0x02F, 0x034, 0x037, 0X03E, 0X075, 0X074, 0X073, 0X072, 0X071, 0x070, 0x06F, 0x06E, 0x06D, 0X06C, 0X06B, 0X06A, 0X053, 0X052, 0X04F},
            {0x02D, 0x02E, 0x035, 0x036, 0X03F, 0X040, 0X041, 0X042, 0X043, 0X044, 0x045, 0x046, 0x047, 0x048, 0X049, 0X04A, 0X04B, 0X04C, 0X04D, 0X04E}
        };

        SnakeHeadDesign += L"0000\n";
        SnakeHeadDesign += L"0220\n";
        SnakeHeadDesign += L"0220\n";
        SnakeHeadDesign += L"0000\n";

        SnaketailDesign += L"0000\n";
        SnaketailDesign += L"0330\n";
        SnaketailDesign += L"0330\n";
        SnaketailDesign += L"0000\n";

        AppleDesign += L"0000\n";
        AppleDesign += L"0440\n";
        AppleDesign += L"0440\n";
        AppleDesign += L"0000\n";
        JRETURN JTRUE;
    }

    JINT GetCurrentPosition(JFLOAT X, JFLOAT Y) {
        JIF(X >= 0 && X < MapWidth && Y >= 0 && Y < MapHeight)
            JRETURN HamiltonianCycle[JSTATICC<JINT>(Y)][JSTATICC<JINT>(X)];
        JRETURN - 1;
    }
    JVOID AddSnakeTail() {
        SnakeBody snakeTail = {JSTATICC<JFLOAT>(CurrentApple.X), JSTATICC<JFLOAT>(CurrentApple.Y), JSTATICC<JFLOAT>(CurrentApple.X), JSTATICC<JFLOAT>(CurrentApple.Y), NONE, NONE, JFALSE};
        SnakeTail.push_back(snakeTail);
    }

    JBOOL CheckIfApple(JINT CPos, JINT TPos) {
        JINT CPosition = GetCurrentPosition(CurrentApple.X, CurrentApple.Y);
        JIF(CPosition == TPos) JRETURN JTRUE;
        JFOR(JAUTO Snake : SnakeTail) {
            JINT SPos = GetCurrentPosition(Snake.X, Snake.Y);
            JIF(TPos == SPos) JRETURN JFALSE;
        }
        JFOR(CPos++; CPos < TPos; CPos++)
            JIF(CPosition == CPos) JRETURN JFALSE;
        JRETURN JTRUE;
    }

    AllMove GetMove()
    {
        JVECTOR<JINT> Move;
        JVECTOR<AllMove> AllMoveV;
        JINT CPosition = GetCurrentPosition(SnakeHead.X, SnakeHead.Y);
        JINT LPos = GetCurrentPosition(SnakeHead.X - 1, SnakeHead.Y);
        JINT RPos = GetCurrentPosition(SnakeHead.X + 1, SnakeHead.Y);
        JINT UPos = GetCurrentPosition(SnakeHead.X, SnakeHead.Y - 1);
        JINT DPos = GetCurrentPosition(SnakeHead.X, SnakeHead.Y + 1);

        JIF (SnakeTail.size() < 40) {
            JIF(((LPos > CPosition) || LPos == 0)  && CheckIfApple(CPosition, LPos) && SnakeHead.CM != RIGHT) {
                Move.push_back(LPos);
                AllMoveV.push_back(LEFT);
            }
            JIF(((RPos > CPosition) || RPos == 0)  && CheckIfApple(CPosition, RPos) && SnakeHead.CM != LEFT) {
                Move.push_back(RPos);
                AllMoveV.push_back(RIGHT);
            }
            JIF(((UPos > CPosition) || UPos == 0)  && CheckIfApple(CPosition, UPos) && SnakeHead.CM != DOWN) {
                Move.push_back(UPos);
                AllMoveV.push_back(UP);
            }
            JIF(((DPos > CPosition) || DPos == 0)  && CheckIfApple(CPosition, DPos) && SnakeHead.CM != UP) {
                Move.push_back(DPos);
                AllMoveV.push_back(DOWN);
            }
            JIF (Move.size() == 0) JRETURN NONE;
            JFOR(JINT i = 0; i < Move.size(); i++) JIF(Move[i] == GetCurrentPosition(CurrentApple.X, CurrentApple.Y)) JRETURN AllMoveV[i];

            JINT MaxValue = Move[0];
            AllMove MaxMove = AllMoveV[0];
            JFOR(JINT i = 0; i < Move.size(); i++) {
                JIF(MaxValue <= Move[i]) {
                    MaxValue = Move[i];
                    MaxMove = AllMoveV[i];
                }
            }
            JRETURN MaxMove;
        } JELSE {
            JIF(LPos == CPosition + 1 || (LPos == 0 && CPosition == 399)) JRETURN LEFT;
            JIF(RPos == CPosition + 1 || (RPos == 0 && CPosition == 399)) JRETURN RIGHT;
            JIF(UPos == CPosition + 1 || (UPos == 0 && CPosition == 399)) JRETURN UP;
            JIF(DPos == CPosition + 1 || (DPos == 0 && CPosition == 399)) JRETURN DOWN;
            JRETURN NONE;
        }
    }

    JVOID MoveSnake(SnakeBody &snake)
    {
        SnakeHead.OM = SnakeHead.CM;
        SnakeHead.CM = GetMove();
        snake.OX = snake.X;
        snake.OY = snake.Y;
        JSWITCH (SnakeHead.CM)
        {
            JCASE LEFT: snake.X -= 1; JBREAK;
            JCASE RIGHT : snake.X += 1; JBREAK;
            JCASE UP : snake.Y -= 1; JBREAK;
            JCASE DOWN : snake.Y += 1; JBREAK;
            JDEFAULT: JBREAK;
        }
        JFOR(JINT i = 0; i < SnakeTail.size(); i++) {
            SnakeTail[i].OX = SnakeTail[i].X;
            SnakeTail[i].OY = SnakeTail[i].Y;
            SnakeTail[i].X = (i == 0) ? SnakeHead.OX : SnakeTail[i-1].OX;
            SnakeTail[i].Y = (i == 0) ? SnakeHead.OY : SnakeTail[i-1].OY;
        }
    }

    JBOOL onUserUpdate() {
        Clear(BLANK, BG_BLACK);
        JFLOAT XPosition = 30;
        JFLOAT YPosition = 10;
        SnakeSpeed -= ElapseTime;
        JIF (SnakeSpeed <= 0 && GameStart && Score < 395) {
            SnakeSpeed = CSnakeSpeed;
            MoveSnake(SnakeHead);
        }
        JIF (keyboard.Keys[Keys::J_SPACEBAR].isHeld) GameStart = JTRUE;
        JINT CAPosition = GetCurrentPosition(CurrentApple.X, CurrentApple.Y);
        JINT CSPosition = GetCurrentPosition(SnakeHead.X, SnakeHead.Y);
        JIF (CAPosition == CSPosition)
        {
            AddSnakeTail();
            JWHILE (JTRUE) {
                JBOOL Cont = JTRUE;
                CurrentApple.X = rand() % MapWidth;
                CurrentApple.Y = rand() % MapHeight;
                JFOR(JAUTO Snake : SnakeTail)
                    JIF(Snake.X == CurrentApple.X && Snake.Y == CurrentApple.Y) {
                        Cont = JFALSE;
                        JBREAK;
                    }
                JIF (Cont) JBREAK;
            }
            Score++;
        }
        DrawBox({MapWidth * 4, MapHeight * 4, XPosition, YPosition}, PIXEL_SOLID);
        DrawCString({XPosition + CurrentApple.X * 4, YPosition + CurrentApple.Y * 4}, AppleDesign, JTRUE);
        DrawCString({XPosition + SnakeHead.X * 4, YPosition + SnakeHead.Y * 4}, SnakeHeadDesign, JTRUE);

        JFOR(JAUTO Snake : SnakeTail) {
            DrawCString({XPosition + Snake.X * 4, YPosition + Snake.Y * 4}, SnaketailDesign, JTRUE);
        }
        DrawString({0, 0}, L"Snake Position: " + JTOWSTR(GetCurrentPosition(SnakeHead.X, SnakeHead.Y)), JTRUE);
        DrawString({0, 1}, L"Snake Position: " + JTOWSTR(GetCurrentPosition(CurrentApple.X, CurrentApple.Y)), JTRUE);

        JRETURN JTRUE;
    }
};

JINT main()
{
    srand(std::time(0));
    JMS<SnakeAI>()->Start();
    JRETURN JFALSE;
}
