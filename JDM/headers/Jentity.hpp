#pragma once

#include <string>
#include "Jwindow.hpp"
#include "Jalgorithms.hpp"

JNAMESPACE JDM { JCLASS BoxEntity {
    JPUBLIC:
        JFUNCTION<JVOID(JWINDOW *window)> hoverFunction = [](JWINDOW *window) {};
        JFUNCTION<JVOID(JWINDOW *window)> RemovehoverFunction = [](JWINDOW *window) {};
        JFUNCTION<JVOID(JWINDOW *window)> touchDownFunction = [](JWINDOW *window) {};
        JFUNCTION<JVOID(JWINDOW *window)> touchUpFunction = [](JWINDOW *window) {};
        JFUNCTION<JVOID(JWINDOW *window)> touchHeldFunction = [](JWINDOW *window) {};
    
        JDM::SizePosDF SPosition;
        JWSTR StringDesign;
        JWSTR ColorDesign;
    
    JPUBLIC:
        BoxEntity(JDM::SizePosDF position) : SPosition(position) { JTHIS->FillDesign(); }
        BoxEntity() : SPosition({18, 18, 0, 0}) { JTHIS->FillDesign(); }
        BoxEntity(JCCHAR *spriteName) : SPosition({18, 18, 0, 0}) { JTHIS->OpenSprite(spriteName); }
        BoxEntity(JDM::Pos2F position, JCCHAR *spriteName) {
            SPosition.X = position.X;
            SPosition.Y = position.Y;
            SPosition.Width = 1;
            SPosition.Height = 1;
            JTHIS->OpenSprite(spriteName);
        }
        ~BoxEntity() {}
        JCONSTEXPR JBOOL collide_point(JCFLOAT px, JCFLOAT py) JCONST { JRETURN JDM::collide_point(SPosition, px, py); }
        JCONSTEXPR JBOOL collide_box(JCONST JDM::SizePosDF position) JCONST { JRETURN JDM::collide_box(SPosition, position); }
    
        JVOID FillDesign(JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK)) {
            JTHIS->StringDesign.clear();
            JTHIS->ColorDesign.clear();
            JFOR(JINT r = JNONE; r < JTHIS->SPosition.Height; r++)
                JFOR(JINT c = JNONE; c < JTHIS->SPosition.Width; c++) {
                    JTHIS->StringDesign += Character;
                    JTHIS->ColorDesign += Color;
            }
        }

        JVOID OpenSprite(JCCHAR *spriteName) {
            std::fstream File(spriteName, std::ios::in);
            assert(File);
            ColorDesign.clear();
            StringDesign.clear();

            JINT LineNav = 0;
            JBOOL CWidth = JFALSE;
            JBOOL CHeight = JFALSE;
            JBOOL Start = JFALSE;
            JINT Navigate = 1;
            JSTR WidthStr;
            JCHAR Character;

        	JWHILE (JTRUE) {
		        File >> Character;
		        JIF (Start && Character == '}') JBREAK;
                JIF (Start && Character != '}') {
                    JIF (Navigate > SPosition.Width) {
                        ColorDesign += '\n'; StringDesign += '\n';
                        SPosition.Height++; Navigate = 1;
                    }
                    ColorDesign += (Character == 'S') ? ' ' : Character;
                    StringDesign += (Character != '\n' && Character != ' ')
                        ? PIXEL_SOLID : Character;
                    Navigate++;
                    JCONTINUE;
                }
                JELSE JIF (Character == '{') {
                    SPosition.Width = std::stoi(WidthStr);
                    SPosition.Height = 1;
                    Start = JTRUE; JCONTINUE;
                }
                JELSE JIF (Character != '\r') {
                    JIF (CWidth || (LineNav == 0 && Character == ':')) {
                        JIF(!CWidth) CWidth = JTRUE;
                        JELSE WidthStr += Character;
                    } JCONTINUE;
                } JELSE {
                    CWidth = JFALSE;
                    LineNav = 1;
                }
                Start = JFALSE;
            }
            File.close();
        }
        JVOID CheckAllFunction(JWINDOW *window) {
            JIF (collide_point(window->ExactMousePos.X, window->ExactMousePos.Y)) {
                hoverFunction(window);
                JIF(window->keyboard.Keys[JDM::Keys::J_MOUSE_LEFT].isPressed) 
                    touchDownFunction(window);
                JIF(window->keyboard.Keys[JDM::Keys::J_MOUSE_LEFT].isHeld) 
                    touchHeldFunction(window);
                JIF(window->keyboard.Keys[JDM::Keys::J_MOUSE_LEFT].isReleased) 
                    touchUpFunction(window);
            } JELSE {
                RemovehoverFunction(window);
            }
        }
        JVOID Render(JWINDOW *Window, JCBOOL AlphaR = JFALSE) {
            JINT x = JSTATICC<JINT>(JTHIS->SPosition.X);
            JINT y = JSTATICC<JINT>(JTHIS->SPosition.Y);
            JFOR(JINT r = JNONE; r < JTHIS->SPosition.Height; r++)
                JFOR(JINT c = JNONE; c < JTHIS->SPosition.Width; c++)
                    Window->Draw({JSTATICC<JFLOAT>(x + c), JSTATICC<JFLOAT>(y + r)}, JTHIS->StringDesign[r * JTHIS->SPosition.Width + c], JTHIS->ColorDesign[r * JTHIS->SPosition.Width + c], AlphaR);
            CheckAllFunction(Window);
        }
        JVOID RenderC(JWINDOW *window, JCBOOL AlphaR = JFALSE) {
            window->DrawCString({SPosition.X, SPosition.Y}, JTHIS->ColorDesign, AlphaR);
            CheckAllFunction(window);
        }
        JVOID RenderS(JWINDOW *Window, JCSHORT Color = JDM::FG_WHITE, JCBOOL AlphaR = JFALSE)
        {
            JINT x = JSTATICC<JINT>(JTHIS->SPosition.X);
            JINT y = JSTATICC<JINT>(JTHIS->SPosition.Y);
                JFOR(JINT r = JNONE; r < JTHIS->SPosition.Height; r++)
                    JFOR(JINT c = JNONE; c < JTHIS->SPosition.Width; c++)
                        Window->Draw({JSTATICC<JFLOAT>(x + c), JSTATICC<JFLOAT>(y + r)}, JTHIS->StringDesign[r * JTHIS->SPosition.Width + c], Color, AlphaR);
            CheckAllFunction(Window);
        }
        JVOID RenderA(JWINDOW *Window, JCSHORT Character = JDM::PIXEL_SOLID, JCSHORT Color = (JDM::FG_WHITE | JDM::BG_BLACK), JCBOOL AlphaR = JFALSE)
        {
            JINT x = JSTATICC<JINT>(JTHIS->SPosition.X);
            JINT y = JSTATICC<JINT>(JTHIS->SPosition.Y);
            JFOR(JINT r = JNONE; r < JTHIS->SPosition.Height; r++)
                JFOR(JINT c = JNONE; c < JTHIS->SPosition.Width; c++)
                    JIF(JTHIS->StringDesign[r * JTHIS->SPosition.Width + c] != L' ')
                    Window->Draw({JSTATICC<JFLOAT>(x + c), JSTATICC<JFLOAT>(y + r)}, Character, Color, AlphaR);
            CheckAllFunction(Window);
        }
    };
}