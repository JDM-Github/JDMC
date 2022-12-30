#include "JDM.h"

JCLASS ConsoleExample : JPUBLIC JWINDOW {

JPRIVATE:

    JSTRUCT Piece {JINT Piece, Rotation, X, Y;};

    JBOOL GameOver = JFALSE;
    JBOOL GameStart = JFALSE;
    JWSTR AllPiece[8];
    JWSTR EmptyCellDesign;
    JFLOAT GameSpeed = 0.2;
    JFLOAT GameTrack = 0.2;
    JINT MapWidth = 12;
    JINT MapHeight = 21;
    JINT OverAllScore = 0;
    JINT HolesCreated = 0;
    JINT HolesCreated2 = 0;
    JUCHAR *Field;
    JUCHAR *FieldCopy;

    JINT CPiece = 0;
    JINT CYPosition = 0;
    JINT CRotation = 0;
    JINT CHoles = 0;
    JINT HPiece = 0;
    JINT HYPosition = 0;
    JINT HRotation = 0;
    JINT HHoles = 0;

    Piece CurrentPiece = {0, 0, MapWidth / 2 - 2, -4};
    Piece NextPiece = {0, 0, 0, 0};
    Piece HeldPiece = {7, 0, 0, 0};
    JVECTOR<Color> AllColor;
    JVECTOR<JINT> Lines;

JPUBLIC:
    ConsoleExample() : JWINDOW("ConsoleExample", 96, 100, 7, 7) { }
    JBOOL onUserCreate() {
        Field = JNEW JUCHAR[MapWidth * MapHeight];
        FieldCopy = JNEW JUCHAR[MapWidth * MapHeight];
        JFOR (JINT y = 0; y < MapHeight; y++)
            JFOR (JINT x = 0; x < MapWidth; x++) {
                Field[y * MapWidth + x] = (x == 0 || x == MapWidth - 1 || y == MapHeight - 1) ? 9 : 0;
                FieldCopy[y * MapWidth + x] = (x == 0 || x == MapWidth - 1 || y == MapHeight - 1) ? 9 : 0;
            }

        AllColor.push_back(FG_WHITE);
        AllColor.push_back(FG_CYAN);
        AllColor.push_back(FG_GREEN);
        AllColor.push_back(FG_RED);
        AllColor.push_back(FG_YELLOW);
        AllColor.push_back(FG_MAGENTA);
        AllColor.push_back(FG_BLUE);
        AllColor.push_back(FG_DARK_YELLOW);
        AllColor.push_back(FG_GRAY);
        AllColor.push_back(FG_DARK_GRAY);
    
        AllPiece[0] += L"  X ";
        AllPiece[0] += L"  X ";
        AllPiece[0] += L"  X ";
        AllPiece[0] += L"  X ";

        AllPiece[1] += L"  X ";
        AllPiece[1] += L" XX ";
        AllPiece[1] += L" X  ";
        AllPiece[1] += L"    ";

        AllPiece[2] += L" X  ";
        AllPiece[2] += L" XX ";
        AllPiece[2] += L"  X ";
        AllPiece[2] += L"    ";

        AllPiece[3] += L"    ";
        AllPiece[3] += L" XX ";
        AllPiece[3] += L" XX ";
        AllPiece[3] += L"    ";

        AllPiece[4] += L"  X ";
        AllPiece[4] += L" XX ";
        AllPiece[4] += L"  X ";
        AllPiece[4] += L"    ";

        AllPiece[5] += L"    ";
        AllPiece[5] += L" XX ";
        AllPiece[5] += L"  X ";
        AllPiece[5] += L"  X ";

        AllPiece[6] += L"    ";
        AllPiece[6] += L" XX ";
        AllPiece[6] += L" X  ";
        AllPiece[6] += L" X  ";

        AllPiece[7] += L"    ";
        AllPiece[7] += L"    ";
        AllPiece[7] += L"    ";
        AllPiece[7] += L"    ";

        EmptyCellDesign.append(L"777\n");
        EmptyCellDesign.append(L"777\n");
        EmptyCellDesign.append(L"777\n");
        JRETURN JTRUE;
    }

    JBOOL ScanUp(JINT x, JINT y) {
        JFOR(JINT CurrentY = y; CurrentY >= 0; CurrentY--) {
            JIF(FieldCopy[CurrentY * MapWidth + x] == 0) JCONTINUE;
            JRETURN JTRUE;
        }
        JRETURN JFALSE;
    }
    JBOOL ScanDown(JINT x, JINT y) {
        JFOR(JINT CurrentY = y; CurrentY < MapHeight; CurrentY++) {
            JIF(FieldCopy[CurrentY * MapWidth + x] == 0) JCONTINUE;
            JRETURN JTRUE;
        }
        JRETURN JFALSE;
    }
    JBOOL ScanLeft(JINT x, JINT y) {
        JFOR(JINT CurrentX = x; CurrentX >= 0; CurrentX--) {
            JIF(FieldCopy[CurrentX + MapWidth * y] == 0) JCONTINUE;
            JRETURN JTRUE;
        }
        JRETURN JFALSE;
    }
    JBOOL ScanRight(JINT x, JINT y) {
        JFOR(JINT CurrentX = x; CurrentX < MapWidth; CurrentX++) {
            JIF(FieldCopy[CurrentX + MapWidth * y] == 0) JCONTINUE;
            JRETURN JTRUE;
        }
        JRETURN JFALSE;
    }
    JINT CheckHoles() {
        HolesCreated = 0;
        JFOR(JINT y = 0; y < MapHeight; y++) {
            JFOR(JINT x = 0; x < MapWidth; x++) {
                JIF(FieldCopy[y * MapWidth + x] == 0)
                    JIF(ScanUp(x, y) && ScanDown(x, y) && ScanLeft(x, y) && ScanRight(x, y))
                    HolesCreated++;
            }
        }
        JRETURN HolesCreated;
    }

    JVOID CheckAllMove(JINT Piece, JINT Rotation, JINT CCX, JINT CCY, JINT isCurrent = JTRUE) {
        JVECTOR<JINT> CRV, CXV, CHV;
        JINT MaxHoles = 400, MaxY = -4, CR = Rotation, CX = CCX, CY = CCY;
        JINT Rot = 0;
        JFOR (JINT y = 0; y < MapHeight; y++)
            JFOR (JINT x = 0; x < MapWidth; x++) 
            FieldCopy[y * MapWidth + x] = Field[y * MapWidth + x];

        JFOR(; Rot < 4; Rot++) {
            JFOR(JINT x = 0; x < MapWidth; x++) {
                JFOR(JINT y = -4; y < MapHeight - 1; y++) {
                    JIF(!DoesPieceFit(Piece, Rot, x, y)) {
                        JIF(y < 3) JBREAK;
                        JFOR(JINT X = 0; X < 4; X++) {
                            JFOR(JINT Y = 0; Y < 4; Y++)
                                JIF(AllPiece[Piece][Rotate(X, Y, Rot)] == L'X')
                                FieldCopy[(Y + y - 1) * MapWidth + (X + x)] = Piece + 1;
                        }
                        JVECTOR<JINT> newLine;
                        JFOR(JINT y = 0; y < 4; y++) {
                        JIF(CurrentPiece.Y + y < MapHeight - 1) {
                            JBOOL line = JTRUE;
                            JFOR(JINT x = 1; x < MapWidth - 1; x++)
                                line &= (FieldCopy[(CurrentPiece.Y + y) * MapWidth + x]) != 0;
                                JIF(line) {
                                    JFOR(JINT x = 1; x < MapWidth - 1; x++)
                                    FieldCopy[(CurrentPiece.Y + y) * MapWidth + x] = 8;
                                    newLine.push_back(CurrentPiece.Y + y);
                                }
                            }
                        }
                        JIF (!newLine.empty()) {
                        JFOR (JAUTO &v : Lines) {
                            JFOR (JINT x = 1; x < MapWidth - 1; x++) {
                                JFOR (JINT y = v; y > 0; y--)
                                    FieldCopy[y * MapWidth + x] = FieldCopy[(y - 1) * MapWidth + x];
                                FieldCopy[x] = 0;
                                }
                            }
                        }
                        JIF (MaxY <= y) {
                            MaxY = y;
                            JIF(isCurrent)  CYPosition = MaxY;
                            JELSE HYPosition = MaxY;
                            CHV.push_back(CheckHoles());
                            CRV.push_back(Rot);
                            CXV.push_back(x);
                        }
                        JFOR (JINT y = 0; y < MapHeight; y++)
                            JFOR (JINT x = 0; x < MapWidth; x++) 
                                FieldCopy[y * MapWidth + x] = Field[y * MapWidth + x];
                        JBREAK;  
                    }
                }   
            }
        }
        JINT Size = CHV.size();
        JINT Iterate = ((Size < 5) ? Size : 5);
        JFOR(JINT i = 1; i < Iterate; i++) {
            JIF(CHV[Size - i] < MaxHoles) {
                MaxHoles = CHV[Size - i];
                JIF(isCurrent) {
                    CHoles = MaxHoles;
                    CRotation = CRV[Size - i];
                    CPiece =  CXV[Size - i];
                } JELSE {
                    HHoles = MaxHoles;
                    HRotation = CRV[Size - i];
                    HPiece =  CXV[Size - i];
                }
            }
        }
    }

    JBOOL DoesPieceFit(JINT Piece, JINT Rotation, JINT X, JINT Y) {
        JFOR (JINT x = 0; x < 4; x++)
            JFOR (JINT y = 0; y < 4; y++) {
                JINT pi = Rotate(x, y, Rotation);
                JINT fi = (Y + y) * MapWidth + (X + x);
                JIF (X + x >= 0 && X + x < MapWidth)
                    JIF (Y + y >= 0 && Y + y < MapHeight) {
                        JIF(AllPiece[Piece][pi] == L'X' && Field[fi] != 0)
                            JRETURN JFALSE;
                }
            }
        JRETURN JTRUE;
    }

    JINT Rotate(JINT x, JINT y, JINT Rotation) {
        JSWITCH (Rotation % 4) {
            JCASE 0: JRETURN y * 4 + x;
            JCASE 1: JRETURN 12 + y - (x * 4);
            JCASE 2: JRETURN 15 - (y * 4) - x;
            JCASE 3: JRETURN 3 - y + (x * 4);
        }
        JRETURN 0;
    }

    JINT CalculateScore(JINT NumLines) {
        JSWITCH (NumLines) {
            JCASE 1: JRETURN 40;
            JCASE 2: JRETURN 100;
            JCASE 3: JRETURN 300;
            JCASE 4: JRETURN 1200;
        }
        JRETURN 0;
    }

    JBOOL onUserUpdate() {
        Clear(BLANK, BG_GRAY);
        JIF(keyboard.Keys[Keys::J_PKEY].isPressed) {
            GameStart = JTRUE;
            HeldPiece.Piece = CurrentPiece.Piece;
            HeldPiece.Rotation = CurrentPiece.Rotation;
            CurrentPiece.Piece = NextPiece.Piece;
            CheckAllMove(CurrentPiece.Piece, CurrentPiece.Rotation, CurrentPiece.X, CurrentPiece.Y);
        }
        JIF (!Lines.empty()) {
            std::this_thread::sleep_for(400ms);
            JFOR (JAUTO &v : Lines) {
                JFOR (JINT x = 1; x < MapWidth - 1; x++) {
                    JFOR (JINT y = v; y > 0; y--)
                        Field[y * MapWidth + x] = Field[(y - 1) * MapWidth + x];
                    Field[x] = 0;
                }
            }
            OverAllScore += CalculateScore(Lines.size());
            Lines.clear();
        }
        JELSE JIF (!GameOver && GameStart) {
            std::this_thread::sleep_for(10ms);
            JIF(keyboard.Keys[Keys::J_AKEY].isPressed) {
                JIF(DoesPieceFit(CurrentPiece.Piece, CurrentPiece.Rotation, CurrentPiece.X - 1, CurrentPiece.Y))
                    CurrentPiece.X--;
            }
            JIF(keyboard.Keys[Keys::J_DKEY].isPressed) {
                JIF(DoesPieceFit(CurrentPiece.Piece, CurrentPiece.Rotation, CurrentPiece.X + 1, CurrentPiece.Y))
                    CurrentPiece.X++;
            }
            JIF(keyboard.Keys[Keys::J_SKEY].isHeld) {
                JIF(DoesPieceFit(CurrentPiece.Piece, CurrentPiece.Rotation, CurrentPiece.X, CurrentPiece.Y + 1))
                    CurrentPiece.Y++;
            }
            JIF(keyboard.Keys[Keys::J_SPACEBAR].isPressed) {
                JIF(DoesPieceFit(CurrentPiece.Piece, CurrentPiece.Rotation + 1, CurrentPiece.X, CurrentPiece.Y))
                    CurrentPiece.Rotation++;
            }
            JIF(keyboard.Keys[Keys::J_HKEY].isPressed) {
                JIF(HeldPiece.Piece == 7) {
                    JIF(DoesPieceFit(NextPiece.Piece, CurrentPiece.Rotation, CurrentPiece.X, CurrentPiece.Y)) {
                        HeldPiece.Piece = CurrentPiece.Piece;
                        HeldPiece.Rotation = CurrentPiece.Rotation;
                        CurrentPiece.Piece = NextPiece.Piece;
                    }
                }
                JELSE JIF(DoesPieceFit(HeldPiece.Piece, CurrentPiece.Rotation, CurrentPiece.X, CurrentPiece.Y)) {
                    JINT Temporary = CurrentPiece.Piece;
                    JINT TemporaryR = CurrentPiece.Rotation;
                    CurrentPiece.Piece = HeldPiece.Piece;
                    CurrentPiece.Rotation = HeldPiece.Rotation;
                    HeldPiece.Piece = Temporary;
                    HeldPiece.Rotation = TemporaryR;
                }
            }

            GameSpeed -= ElapseTime;
            JIF(GameSpeed <= 0) {
                GameSpeed = GameTrack;
                JIF(DoesPieceFit(CurrentPiece.Piece, CurrentPiece.Rotation, CurrentPiece.X, CurrentPiece.Y + 1))
                    CurrentPiece.Y++;
                JELSE {
                    GameTrack -=  0.001;
                    JIF(CurrentPiece.Y < 0)  GameOver = JTRUE;
                    JELSE {
                        JFOR (JINT x = 0; x < 4; x++) {
                            JFOR (JINT y = 0; y < 4; y++)
                                JIF (AllPiece[CurrentPiece.Piece][Rotate(x, y, CurrentPiece.Rotation)] == L'X')
                                Field[(CurrentPiece.Y + y) * MapWidth + (CurrentPiece.X + x)] = CurrentPiece.Piece + 1;
                        }
                        // CheckHoles();
                        JFOR(JINT y = 0; y < 4; y++) {
                            JIF(CurrentPiece.Y + y < MapHeight - 1) {
                                JBOOL line = JTRUE;
                                JFOR(JINT x = 1; x < MapWidth - 1; x++)
                                line &= (Field[(CurrentPiece.Y + y) * MapWidth + x]) != 0;
                                JIF(line) {
                                    JFOR(JINT x = 1; x < MapWidth - 1; x++)
                                    Field[(CurrentPiece.Y + y) * MapWidth + x] = 8;
                                    Lines.push_back(CurrentPiece.Y + y);
                                }
                            }
                        }
                        CurrentPiece.X = MapWidth / 2 -2;
                        CurrentPiece.Y = -4;
                        CurrentPiece.Rotation = 0;
                        CurrentPiece.Piece = NextPiece.Piece;
                        NextPiece.Piece = 0;

                        CheckAllMove(CurrentPiece.Piece, CurrentPiece.Rotation, CurrentPiece.X, CurrentPiece.Y);
                        CheckAllMove(HeldPiece.Piece, HeldPiece.Rotation, CurrentPiece.X, CurrentPiece.Y, JFALSE);

                        JIF(CHoles > HHoles) {
                            JINT Temporary = CurrentPiece.Piece;
                            JINT TemporaryR = CurrentPiece.Rotation;
                            CurrentPiece.Piece = HeldPiece.Piece;
                            CurrentPiece.Rotation = HeldPiece.Rotation;
                            HeldPiece.Piece = Temporary;
                            HeldPiece.Rotation = TemporaryR;

                            CurrentPiece.Rotation = HRotation;
                            CurrentPiece.X = HPiece;

                        } JELSE {
                            CurrentPiece.Rotation = CRotation;
                            CurrentPiece.X = CPiece;
                        }

                        // NextPiece.Piece = rand() % 7;
                    }
                }
            }
        }
        JFOR (JINT y = 0; y < MapHeight; y++)
            JFOR (JINT x = 0; x < MapWidth; x++) {
                JIF(Field[y * MapWidth + x] != 0)
                    Drawer::DrawBoxHollow(JTHIS, {5, 5, 23.f + x * 4, 3.f + y * 4}, 1, PIXEL_SOLID, FG_BLACK);
                DrawBox({3, 3, 24.f + x * 4, 4.f + y * 4}, PIXEL_SOLID, (GameOver && Field[y * MapWidth + x] != 0 && Field[y * MapWidth + x] != 9)
                    ? FG_GRAY: AllColor[Field[y * MapWidth + x]]);
            }
        JFOR (JINT x = 0; x < 4; x++)
            JFOR (JINT y = 0; y < 4; y++) {
                JIF((4.f + ((CurrentPiece.Y + y) * 4)) < 4) JCONTINUE;
                JIF(AllPiece[CurrentPiece.Piece][Rotate(x, y, CurrentPiece.Rotation)] == L'X') {
                    Drawer::DrawBoxHollow(JTHIS, {5, 5, 23.f + ((CurrentPiece.X + x) * 4), 3.f + ((CurrentPiece.Y + y) * 4)}, 1, PIXEL_SOLID, FG_BLACK);
                    DrawBox({3, 3, 24.f + ((CurrentPiece.X + x) * 4), 4.f + ((CurrentPiece.Y + y) * 4)}, PIXEL_SOLID, (GameOver) ? FG_GRAY : AllColor[CurrentPiece.Piece + 1]);
                }
            }
            DrawBox({4 * 4 + 1, 4 * 4 + 1, 3.f, 3.f}, PIXEL_SOLID, FG_DARK_GRAY);
            DrawBox({4 * 4 + 1, 4 * 4 + 1, 24.f + (MapWidth * 4) + 3.f, 3.f}, PIXEL_SOLID, FG_DARK_GRAY);
            JFOR(JINT x = 0; x < 4; x++)
            JFOR (JINT y = 0; y < 4; y++) {
                JIF(AllPiece[NextPiece.Piece][Rotate(x, y, NextPiece.Rotation)] == L'X') {
                    Drawer::DrawBoxHollow(JTHIS, {5, 5, 24.f + (MapWidth * 4) + 3.f + x * 4, 3.f + y * 4}, 1, PIXEL_SOLID, FG_BLACK);
                    DrawBox({3, 3, 24.f + (MapWidth * 4) + 4.f + x * 4, 4.f + y * 4}, PIXEL_SOLID, AllColor[NextPiece.Piece + 1]);
                }
                JIF(AllPiece[HeldPiece.Piece][Rotate(x, y, HeldPiece.Rotation)] == L'X') {
                    Drawer::DrawBoxHollow(JTHIS, {5, 5, 3.f + x * 4, 3.f + y * 4}, 1, PIXEL_SOLID, FG_BLACK);
                    DrawBox({3, 3, 4.f + x * 4, 4.f + y * 4}, PIXEL_SOLID, AllColor[HeldPiece.Piece + 1]);
                }
            }
        DrawACString({3, 22}, Alphabet[AlphabetEnum::H], PIXEL_SOLID, FG_WHITE);
        DrawACString({8, 22}, Alphabet[AlphabetEnum::E], PIXEL_SOLID, FG_WHITE);
        DrawACString({12, 22}, Alphabet[AlphabetEnum::L], PIXEL_SOLID, FG_WHITE);
        DrawACString({16, 22}, Alphabet[AlphabetEnum::D], PIXEL_SOLID, FG_WHITE);

        DrawACString({24.f + (MapWidth * 4) + 3, 22}, Alphabet[AlphabetEnum::N], PIXEL_SOLID, FG_WHITE);
        DrawACString({24.f + (MapWidth * 4) + 8, 22}, Alphabet[AlphabetEnum::E], PIXEL_SOLID, FG_WHITE);
        DrawACString({24.f + (MapWidth * 4) + 12, 22}, Alphabet[AlphabetEnum::X], PIXEL_SOLID, FG_WHITE);
        DrawACString({24.f + (MapWidth * 4) + 16, 22}, Alphabet[AlphabetEnum::T], PIXEL_SOLID, FG_WHITE);

        DrawACString({3, JSTATICC<JFLOAT>(GetHeight() - 7)}, Alphabet[AlphabetEnum::S], PIXEL_SOLID, FG_BLACK);
        DrawACString({8, JSTATICC<JFLOAT>(GetHeight() - 7)}, Alphabet[AlphabetEnum::C], PIXEL_SOLID, FG_BLACK);
        DrawACString({13, JSTATICC<JFLOAT>(GetHeight() - 7)}, Alphabet[AlphabetEnum::O], PIXEL_SOLID, FG_BLACK);
        DrawACString({18, JSTATICC<JFLOAT>(GetHeight() - 7)}, Alphabet[AlphabetEnum::R], PIXEL_SOLID, FG_BLACK);
        DrawACString({23, JSTATICC<JFLOAT>(GetHeight() - 7)}, Alphabet[AlphabetEnum::E], PIXEL_SOLID, FG_BLACK);
        DrawACString({27, JSTATICC<JFLOAT>(GetHeight() - 7)}, Alphabet[AlphabetEnum::SIMI_COLOR], PIXEL_SOLID, FG_BLACK);

        JWSTR ScoreInString = JTOWSTR(OverAllScore);
        JINT ScoreIndex = 0;
        JFOR(JINT i = 0; i < 6; i++) {
            JIF(6 - i <= ScoreInString.size()) DrawACString({31.f + i * 5, JSTATICC<JFLOAT>(GetHeight() - 7)},
                Alphabet[AlphabetEnum::N0 + (ScoreInString[ScoreIndex++] - '0')], PIXEL_SOLID, FG_BLACK);
            JELSE DrawACString({31.f + i * 5, JSTATICC<JFLOAT>(GetHeight() - 7)},
                Alphabet[AlphabetEnum::N0], PIXEL_SOLID, FG_BLACK);
        }

        DrawString({0, 0}, JTOWSTR(HolesCreated2), FG_WHITE | BG_DARK_CYAN, JTRUE);

        JRETURN JTRUE;
    }
};

JINT main()
{
    srand(std::time(JNONE));
    JMS<ConsoleExample>()->Start();
    JRETURN JFALSE;
}
