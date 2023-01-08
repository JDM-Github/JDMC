#include "JDM.hpp"

JCINT BlockSize = 4;
JCINT MapWidth = 24;
JCINT MapHeight = 24;

JUSING JNAMESPACE std;
JCLASS PixelCanvas{
JPUBLIC:
    JSTRUCT Navigator {
        JFLOAT X, Y, Duration = 0.3;
        JINT CurrenIndex = 0;
    };
    Navigator navigator = {0, 0};
    JWSTR Canvas;
    JINT width, height;
    JINT IndexNav = 0;

    JVECTOR<JPAIR<JINT, JINT>> AllUndo;
    JVECTOR<JPAIR<JINT, JINT>> AllRedo;

JPUBLIC:
    PixelCanvas(JINT Width, JINT Height)
    : width(Min(Width, MapWidth)), height(Min(Height, MapHeight)) {
        AllUndo.reserve(1000);
        AllRedo.reserve(1000);
        JFOR(JINT y = 0; y < height; y++) 
            JFOR(JINT x = 0; x < width; x++)
            Canvas += 0xF;
    }

    JVOID Undo() {
        JIF (IndexNav > 0) {
            IndexNav--;
            Canvas[AllUndo[IndexNav].first] = AllUndo[IndexNav].second;
            navigator.Y = AllUndo[IndexNav].first / width;
            navigator.X = AllUndo[IndexNav].first % width;
        }
    }
    JVOID Redo() {
        JIF (AllRedo.size() != IndexNav) {
            Canvas[AllRedo[IndexNav].first] = AllRedo[IndexNav].second;
            navigator.Y = AllRedo[IndexNav].first / width;
            navigator.X = AllRedo[IndexNav].first % width;
            IndexNav++;
        }
    }
    JINT GetItem(JINT x, JINT y) { JRETURN Canvas[x + y * width]; }
    JVOID SetItem(JINT x, JINT y, JINT Value) {
        AllUndo.resize(IndexNav);
        AllRedo.resize(IndexNav);
        AllUndo.push_back(JMPAIR(x + y * width, Canvas[x + y * width]));
        AllRedo.push_back(JMPAIR(x + y * width, Value));

        Canvas[x + y * width] = Value;
        IndexNav++;
    }

    JBOOL Save(JCCHAR *FileName) {
        ofstream File(JSTR(FileName) + ".sprt");
        File << "Width: " << width << "\n";
        File << "Height: " << height << "\n";
        File << "Sprite: {\n";
        JFOR (JINT y = 0; y < height; y++) {
            JFOR (JINT x = 0; x < width; x++) {
                File << ConvertItemInHex(Canvas[y * width + x]);
            }
            File << '\n';
        }
        File << "}\n";
        File.close();
    }

    JBOOL Open() {

    }

    JCONSTEXPR JCHAR ConvertItemInHex(JINT Item) {
        JSWITCH (Item) {
            JCASE 0 : JRETURN '0';
            JCASE 1 : JRETURN '1';
            JCASE 2 : JRETURN '2';
            JCASE 3 : JRETURN '3';
            JCASE 4 : JRETURN '4';
            JCASE 5 : JRETURN '5';
            JCASE 6 : JRETURN '6';
            JCASE 7 : JRETURN '7';
            JCASE 8 : JRETURN '8';
            JCASE 9 : JRETURN '9';
            JCASE 0xA : JRETURN 'A';
            JCASE 0xB : JRETURN 'B';
            JCASE 0xC : JRETURN 'C';
            JCASE 0xD : JRETURN 'D';
            JCASE 0xE : JRETURN 'E';
            JCASE 0xF : JRETURN 'F';
            JCASE 0x10 : JRETURN 'S';
        }
    }
};

JCLASS SpriteMaker : JPUBLIC JWINDOW {
JPRIVATE:
    JFLOAT UndoHold = 0.2;
    JFLOAT RedoHold = 0.2;
    JFLOAT ResizeHold = 0.2;

    JBOOL isShift = JTRUE;
    JBOOL isTab = JFALSE;
    JBOOL isCtrl = JFALSE;
    JINT CurrentCWidth = 24;
    JINT CurrentCHeight = 24;
    JINT CurrentColorX = 0;
    JINT CurrentColorY = 0;

    BoxEntity arrowUp = BoxEntity({7 + 3, 1}, "spriteMaker/ArrowUp.sprt");
    BoxEntity arrowDown = BoxEntity({7 + 15, 1}, "spriteMaker/ArrowDown.sprt");
    BoxEntity arrowLeft = BoxEntity({7 + 27, 1}, "spriteMaker/ArrowLeft.sprt");
    BoxEntity arrowRight = BoxEntity({7 + 39, 1}, "spriteMaker/ArrowRight.sprt");

    PixelCanvas *canvas;

JPUBLIC:
    SpriteMaker() : JWINDOW("SpriteMaker", (BlockSize * MapWidth) + 22 + MapWidth + 2, (BlockSize * MapHeight) + 20, 5, 5) { }
    JBOOL onUserCreate() {
        canvas = JNEW PixelCanvas(CurrentCWidth, CurrentCHeight);

        arrowUp.hoverFunction = std::bind(
            [](SpriteMaker *window) {
                window->arrowUp.SPosition.Y = 0;
            },
            JTHIS);
        arrowUp.RemovehoverFunction = std::bind(
            [](SpriteMaker *window) {
                window->arrowUp.SPosition.Y = 1;
            },
            JTHIS);
        arrowUp.touchHeldFunction = std::bind(
            [](SpriteMaker *window) {
                window->ResizeHold -= window->ElapseTime;
                JIF (window->ResizeHold <= 0 && window->CurrentCHeight <= MapHeight) {
                    window->ResizeHold = 0.15;
                    window->CurrentCHeight += 1;
                    window->ReCreateCanvas();
                }
            },
            JTHIS);
        
        arrowDown.hoverFunction = std::bind(
            [](SpriteMaker *window) {
                window->arrowDown.SPosition.Y = 0;
            },
            JTHIS);
        arrowDown.RemovehoverFunction = std::bind(
            [](SpriteMaker *window) {
                window->arrowDown.SPosition.Y = 1;
            },
            JTHIS);
        arrowDown.touchHeldFunction = std::bind(
            [](SpriteMaker *window) {
                window->ResizeHold -= window->ElapseTime;
                JIF (window->ResizeHold <= 0 && window->CurrentCHeight > 0) {
                    window->ResizeHold = 0.15;
                    window->CurrentCHeight -= 1;
                    window->ReCreateCanvas();
                }
            },
            JTHIS);
        
        arrowLeft.hoverFunction = std::bind(
            [](SpriteMaker *window) {
                window->arrowLeft.SPosition.Y = 0;
            },
            JTHIS);
        arrowLeft.RemovehoverFunction = std::bind(
            [](SpriteMaker *window) {
                window->arrowLeft.SPosition.Y = 1;
            },
            JTHIS);
        arrowLeft.touchHeldFunction = std::bind(
            [](SpriteMaker *window) {
                window->ResizeHold -= window->ElapseTime;
                JIF (window->ResizeHold <= 0 && window->CurrentCWidth > 0) {
                    window->ResizeHold = 0.15;
                    window->CurrentCWidth -= 1;
                    window->ReCreateCanvas();
                }
            },
            JTHIS);
        
        arrowRight.hoverFunction = std::bind(
            [](SpriteMaker *window) {
                window->arrowRight.SPosition.Y = 0;
            },
            JTHIS);
        arrowRight.RemovehoverFunction = std::bind(
            [](SpriteMaker *window) {
                window->arrowRight.SPosition.Y = 1;
            },
            JTHIS);
        arrowRight.touchHeldFunction = std::bind(
            [](SpriteMaker *window) {
                window->ResizeHold -= window->ElapseTime;
                JIF (window->ResizeHold <= 0 && window->CurrentCWidth + 1 <= MapWidth) {
                    window->ResizeHold = 0.15;
                    window->CurrentCWidth += 1;
                    window->ReCreateCanvas();
                }
            },
            JTHIS);
        JRETURN JTRUE;
    }

    JVOID ReCreateCanvas() {
        canvas->navigator.X = 0;
        canvas->navigator.Y = 0;
        canvas->navigator.CurrenIndex = 0;
        canvas->AllUndo.clear();
        canvas->AllRedo.clear();
        canvas->width = Max(1.f, Min(MapWidth, CurrentCWidth));
        canvas->height = Max(1.f, Min(MapHeight, CurrentCHeight));
        CurrentCWidth = canvas->width;
        CurrentCHeight = canvas->height;
        canvas->IndexNav = 0;
        canvas->Canvas.clear();
        JFOR (JINT y = 0; y < canvas->height; y++)
            JFOR (JINT x = 0; x < canvas->width; x++) {
                canvas->Canvas += 0xF;
            }
    }

    JBOOL onUserUpdate() {
        Clear(BLANK, BG_GRAY);

        JIF(keyboard.Keys[Keys::J_CTRL].isHeld) isCtrl = JTRUE;
        JIF(keyboard.Keys[Keys::J_CTRL].isReleased) isCtrl = JFALSE;
        JIF (isCtrl) {
            JIF (keyboard.Keys[Keys::J_ZKEY].isPressed) canvas->Undo();
            JELSE JIF (keyboard.Keys[Keys::J_ZKEY].isHeld) {
                UndoHold -= ElapseTime;
                JIF (UndoHold <= 0) {
                    canvas->Undo();
                    UndoHold = 0.05;
                }
            } JELSE JIF (keyboard.Keys[Keys::J_ZKEY].isReleased) UndoHold = 0.2;
            JIF (keyboard.Keys[Keys::J_SKEY].isPressed) canvas->Save("testSprite");

            JIF (keyboard.Keys[Keys::J_YKEY].isPressed) canvas->Redo();
            JELSE JIF (keyboard.Keys[Keys::J_YKEY].isHeld) {
                RedoHold -= ElapseTime;
                JIF (RedoHold <= 0) {
                    canvas->Redo();
                    RedoHold = 0.05;
                }
            } JELSE JIF (keyboard.Keys[Keys::J_YKEY].isReleased) RedoHold = 0.2;
        } JELSE {

            JIF(keyboard.Keys[Keys::J_SHIFT].isPressed) isShift = (isShift + 1) % 2;
            JIF(keyboard.Keys[Keys::J_TAB].isPressed) isTab = (isTab + 1) % 2;
            JIF(keyboard.Keys[Keys::J_DKEY].isPressed) {
                JIF (!isTab) {
                    JIF (canvas->navigator.X + 1 < canvas->width)
                    canvas->navigator.X++;
                }
                JELSE JIF(CurrentColorX + 1 < 8)
                    CurrentColorX++;
            }
            JIF(keyboard.Keys[Keys::J_AKEY].isPressed) {
                JIF (!isTab) {
                    JIF(canvas->navigator.X > 0)
                    canvas->navigator.X--;
                }
                JELSE JIF(CurrentColorX > 0)
                    CurrentColorX--;
            }
            JIF(keyboard.Keys[Keys::J_SKEY].isPressed) {
                JIF (!isTab) {
                    JIF (canvas->navigator.Y + 1 < canvas->height)
                    canvas->navigator.Y++; 
                }
                JELSE JIF(CurrentColorY + 1 < 2)
                    CurrentColorY++;
            }
            JIF(keyboard.Keys[Keys::J_WKEY].isPressed) {
                JIF (!isTab) {
                    JIF (canvas->navigator.Y > 0)
                    canvas->navigator.Y--;
                }
                JELSE JIF(CurrentColorY > 0)
                    CurrentColorY--;
            }
            JIF(keyboard.Keys[Keys::J_SPACEBAR].isHeld && !isTab) {
                JIF (canvas->GetItem(canvas->navigator.X, canvas->navigator.Y) != ((isShift) ? (CurrentColorX + CurrentColorY * 8) : 0x10))
                    canvas->SetItem(canvas->navigator.X, canvas->navigator.Y, (isShift) ? (CurrentColorX + CurrentColorY * 8) : 0x10);
            }
        }

        JFLOAT StartX = 3.f;
        JFLOAT StartY = 17.f;
        DrawBox({BlockSize * MapWidth + 2, BlockSize * MapHeight + 2, (StartX + 6) - 1, StartY - 1}, PIXEL_SOLID, FG_DARK_GRAY, JTRUE);
        JFLOAT MidX = (MapWidth - canvas->width) / 2.f;
        JFLOAT MidY = (MapHeight - canvas->height) / 2.f;
        JFOR(JINT y = 0; y < canvas->height; y++) {
            JFOR(JINT x = 0; x < canvas->width; x++) {
                JINT Item = canvas->GetItem(x, y);
                DrawBox({BlockSize, BlockSize, (StartX + 6) + (x + MidX) * BlockSize, StartY + (y + MidY) * BlockSize},
                        (Item >= 0x10) ? L' ' : PIXEL_SOLID, (Item >= 0x10) ? 0xF : Item, JTRUE);
            }
        }
        canvas->navigator.Duration -= ElapseTime;
        JIF (canvas->navigator.Duration <= 0) {
            canvas->navigator.Duration = 0.3;
            canvas->navigator.CurrenIndex++;
        }

        DrawBox({MapWidth + 2, MapHeight + 8, StartX + 8 + (BlockSize * MapWidth + 4) - 1, StartY - 1}, PIXEL_SOLID, FG_DARK_GRAY, JTRUE);
        JFOR(JINT y = 0; y < canvas->height; y++) 
            JFOR(JINT x = 0; x < canvas->width; x++) {
                JINT Item = canvas->GetItem(x, y);
                Draw({StartX + 8 + (BlockSize * MapWidth + 4) + x + MidX,
                    StartY + MidY + y}, (Item >= 0x10) ? L' ' : PIXEL_SOLID, (Item >= 0x10) ? 0xF : Item, JTRUE);
            }

        JFOR(JINT y = 0; y < 2; y++)
            JFOR(JINT x = 0; x < 8; x++)
                DrawBox({3, 3, StartX + 8 + (BlockSize * MapWidth + 4) + x * 3, 17.f + MapHeight + y * 3}, PIXEL_SOLID, (x + y * 8), JTRUE);

        JINT SizeNav = (isTab) ? 3 : BlockSize;
        JFLOAT NavX = ((isTab) ? (StartX + 8 + (BlockSize * MapWidth + 4) + CurrentColorX * 3) : ((StartX + 6) + (canvas->navigator.X + MidX) * BlockSize));
        JFLOAT NavY = ((isTab) ? (17.f + MapHeight + CurrentColorY * 3): (StartY + (canvas->navigator.Y + MidY) * BlockSize));
        Drawer::DrawBoxHollow(JTHIS, {SizeNav + ((canvas->navigator.CurrenIndex % 2) ? 2 : 0), SizeNav + ((canvas->navigator.CurrenIndex % 2) ? 2 : 0),
            NavX - ((canvas->navigator.CurrenIndex % 2) ? 1 : 0), NavY - ((canvas->navigator.CurrenIndex % 2) ? 1 : 0)}, 1, PIXEL_SOLID,
            ((isTab || canvas->GetItem(canvas->navigator.X, canvas->navigator.Y) != FG_BLACK) ? FG_BLACK : FG_DARK_GRAY), JTRUE);

        DrawACString({StartX + 8 + (BlockSize * MapWidth + 5), GetHeight() - 8.f},
                     NumberWStr[JSTATICC<JINT>((canvas->navigator.X + 1) / 10)], PIXEL_SOLID, FG_DARK_GRAY);
        DrawACString({StartX + 8 + (BlockSize * MapWidth + 10), GetHeight() - 8.f},
                     NumberWStr[JSTATICC<JINT>(canvas->navigator.X + 1) % 10], PIXEL_SOLID, FG_DARK_GRAY);

        DrawACString({StartX + 8 + (BlockSize * MapWidth + 18), GetHeight() - 8.f},
                     NumberWStr[JSTATICC<JINT>((canvas->navigator.Y + 1) / 10)], PIXEL_SOLID, FG_DARK_GRAY);
        DrawACString({StartX + 8 + (BlockSize * MapWidth + 23), GetHeight() - 8.f},
                     NumberWStr[JSTATICC<JINT>(canvas->navigator.Y + 1) % 10], PIXEL_SOLID, FG_DARK_GRAY);

        arrowUp.RenderC(JTHIS, JTRUE);
        arrowDown.RenderC(JTHIS, JTRUE);
        arrowLeft.RenderC(JTHIS, JTRUE);
        arrowRight.RenderC(JTHIS, JTRUE);

        JRETURN JTRUE;
    }
};

JINT main() {
    JDM::SetRandomSeed();
    JMS<SpriteMaker>()->Start();
    JRETURN JFALSE;
}