// #include "JDM.hpp"

// JINT BlockSize = 4;
// JCINT MapWidth = 20;
// JCINT MapHeight = 20;

// JCLASS PixelCanvas{
// JPUBLIC:
//     JWSTR Canvas;
//     JINT width, height;

// JPUBLIC:
//     PixelCanvas(JINT Width, JINT Height)
//     : width(Min(Width, MapWidth)), height(Min(Height, MapHeight)) {
//         JFOR(JINT y = 0; y < height; y++) 
//             JFOR(JINT x = 0; x < width; x++) 
//                 Canvas += 0xF;
//     }
//     JINT GetItem(JINT x, JINT y) { JRETURN Canvas[x + y * width]; }
//     JVOID SetItem(JINT x, JINT y, JINT Value) { Canvas[x + y * width] = Value; }
// };

// JCLASS FontMaker : JPUBLIC JWINDOW {
// JPRIVATE:
//     JSTRUCT Navigator {
//         JFLOAT X, Y, Duration = 0.3;
//         JINT CurrenIndex = 0;
//         JWSTR Design[2] = {(
//             L"44   44\n"
//             L"4     4\n"
//             L"       \n"
//             L"       \n"
//             L"       \n"
//             L"4     4\n"
//             L"44   44\n"
//         ), (
//             L"       \n"
//             L" 44 44 \n"
//             L" 4   4 \n"
//             L"       \n"
//             L" 4   4 \n"
//             L" 44 44 \n"
//             L"       \n"
//         )};
//     };

//     JBOOL isShift = JFALSE;
//     JWSTR ArrowLeft;
//     JWSTR ArrowRight;

//     JINT CurrentCWidth = 6;
//     JINT CurrentCHeight = 6;
//     JINT CurrentCanvas = 0;

//     Navigator navigator = {0, 0};
//     JVECTOR<JSP<PixelCanvas>> AllCanvas;

// JPUBLIC:
//     FontMaker() : JWINDOW("FontMaker", (BlockSize * MapWidth) + 22 + (5 * BlockSize) + 2, (BlockSize * MapHeight) + 10, 5, 5) { }
//     JBOOL onUserCreate() {
//         ArrowLeft += L"  F  \n";        ArrowRight += L"  F  \n";
//         ArrowLeft += L" FF  \n";        ArrowRight += L"  FF \n";
//         ArrowLeft += L"FFFFF\n";        ArrowRight += L"FFFFF\n";
//         ArrowLeft += L"FFFFF\n";        ArrowRight += L"FFFFF\n";
//         ArrowLeft += L" FF  \n";        ArrowRight += L"  FF \n";
//         ArrowLeft += L"  F  \n";        ArrowRight += L"  F  \n";
//         AllCanvas.reserve(100);
//         SetAllCanvas();
//         JRETURN JTRUE;
//     }

//     JVOID SetAllCanvas() {
//         JFOR(JINT i = 0; i < 80; i++) { AllCanvas.push_back(JMS<PixelCanvas>(CurrentCWidth, CurrentCHeight)); }
//     }

//     JBOOL onUserUpdate() {
//         Clear(BLANK, BG_BLACK);

//         JIF(keyboard.Keys[Keys::J_SHIFT].isPressed) isShift = (isShift + 1) % 2;
//         JIF(keyboard.Keys[Keys::J_DKEY].isPressed && navigator.X + 1 < AllCanvas[CurrentCanvas]->width) navigator.X++;
//         JIF(keyboard.Keys[Keys::J_AKEY].isPressed && navigator.X > 0) navigator.X--;
//         JIF(keyboard.Keys[Keys::J_SKEY].isPressed && navigator.Y + 1 < AllCanvas[CurrentCanvas]->height) navigator.Y++;
//         JIF(keyboard.Keys[Keys::J_WKEY].isPressed && navigator.Y > 0) navigator.Y--;
//         JIF(keyboard.Keys[Keys::J_SPACEBAR].isHeld) AllCanvas[CurrentCanvas]->SetItem(navigator.X, navigator.Y, (isShift) ? 0 : 0xF);

//         JIF(keyboard.Keys[Keys::J_LEFTKEY].isPressed) CurrentCanvas = ((CurrentCanvas > 0) ? (CurrentCanvas - 1) : (AllCanvas.size() - 1));
//         JIF(keyboard.Keys[Keys::J_RIGHTKEY].isPressed) CurrentCanvas = (CurrentCanvas + 1) % 80;

//         JFLOAT StartX = 3.f;
//         JFLOAT StartY = 7.f;
//         DrawCString({StartX, JSTATICC<JFLOAT>((GetHeight() / 2 - 3))}, ArrowLeft, JTRUE);
//         DrawCString({GetWidth() - StartX - 5, JSTATICC<JFLOAT>(GetHeight() / 2 - 3)}, ArrowRight, JTRUE);

//         DrawBox({BlockSize * MapWidth + 2, BlockSize * MapHeight + 2, (StartX + 8) - 1, StartY - 1}, PIXEL_SOLID, FG_DARK_GRAY, JTRUE);
//         JFLOAT MidX = (MapWidth - AllCanvas[CurrentCanvas]->width) / 2.f;
//         JFLOAT MidY = (MapHeight - AllCanvas[CurrentCanvas]->height) / 2.f;
//         JFOR(JINT y = 0; y < AllCanvas[CurrentCanvas]->height; y++) {
//             JFOR(JINT x = 0; x < AllCanvas[CurrentCanvas]->width; x++) {
//                 DrawBox({BlockSize, BlockSize, (StartX + 8) + (x + MidX) * BlockSize, StartY + (y + MidY) * BlockSize},
//                     PIXEL_SOLID, AllCanvas[CurrentCanvas]->Canvas[x + y * AllCanvas[CurrentCanvas]->width], JTRUE);
//             }
//         }
//         navigator.Duration -= ElapseTime;
//         JIF (navigator.Duration <= 0) {
//             navigator.Duration = 0.3;
//             navigator.CurrenIndex++;
//         }
//         JIF (navigator.CurrenIndex % 2)
//             Drawer::DrawBoxHollow(JTHIS, {BlockSize + 2, BlockSize + 2, (StartX + 8) + (navigator.X + MidX) * BlockSize - 1, StartY + (navigator.Y + MidY) * BlockSize - 1},
//                               1, PIXEL_SOLID, FG_RED, JTRUE);
//         JELSE Drawer::DrawBoxHollow(JTHIS, {BlockSize, BlockSize, (StartX + 8) + (navigator.X + MidX) * BlockSize, StartY + (navigator.Y + MidY) * BlockSize},
//                               1, PIXEL_SOLID, FG_RED, JTRUE);

//         DrawBox({5 * BlockSize + 2, 5 * BlockSize + 2, StartX + 8 + (BlockSize * MapWidth + 2) - 1, StartY - 1}, PIXEL_SOLID, FG_WHITE, JTRUE);

//         JRETURN JTRUE;
//     }
// };

// JINT main() {
//     srand(std::time(JNONE));
//     JMS<FontMaker>()->Start();
//     JRETURN JFALSE;
// }
