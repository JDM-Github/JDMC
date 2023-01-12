#include "JDM.hpp"

JCLASS ShadowCasting : JPUBLIC JWINDOW {
JPRIVATE:

    JDM::Cell *World;
    JINT WorldWidth = 20;
    JINT WorldHeight = 20;
    JINT BlockWidth = 3;

    JVECTOR<JDM::Edges> VectorEdges;
    JVECTOR<tuple<JFLOAT, JFLOAT, JFLOAT>> VectorVisibilityPolygonPoints;

JPUBLIC:
    ShadowCasting() : JWINDOW("ShadowCasting", 60, 60, 10, 10) { }
    JBOOL onUserCreate() {
        World = JNEW JDM::Cell[WorldWidth * WorldHeight];
        JFOR(JINT y = 1; y < WorldHeight; y++) 
        JFOR(JINT x = 1; x < WorldWidth; x++) {
            JIF ((x == 1 && y < WorldHeight - 1) || (y == 1 && x < WorldWidth - 1)
              || (x == WorldWidth - 2 && y < WorldHeight - 1) || (y == WorldHeight - 2 && x < WorldWidth - 1)) 
                World[y * WorldWidth + x].Exist = JTRUE;
        }
        JRETURN JTRUE;
    }

    JVOID CalculateVisibilityPolygon(JFLOAT OX, JFLOAT OY, JFLOAT Radius) {

        VectorVisibilityPolygonPoints.clear();
        JFOR (JAUTO &E1 : VectorEdges) {
            JFOR(JINT i = 0; i < 2; i++) {
                JFLOAT RDX, RDY;
                RDX = (i == 0 ? E1.SX : E1.EX) - OX;
                RDY = (i == 0 ? E1.SY : E1.EY) - OY;
                JFLOAT BaseAngle = atan2f(RDY, RDX);
                JFLOAT Angle = 0;

                JBOOL Valid = JFALSE;
                JFLOAT Min_T1 = INFINITY;
                JFLOAT Min_PX = 0, Min_PY = 0, Min_Angle = 0;

                JFOR(JINT j = 0; j < 3; j++) {
                    JIF(j == 0) Angle = BaseAngle - 0.001f;
                    JIF(j == 1) Angle = BaseAngle;
                    JIF(j == 2) Angle = BaseAngle + 0.001f;

                    RDX = Radius * cosf(Angle);
                    RDY = Radius * sinf(Angle);

                    JFOR (JAUTO &E2 : VectorEdges) {
                        JFLOAT SDX = E2.EX - E2.SX;
                        JFLOAT SDY = E2.EY - E2.SY;

                        JIF (fabs(SDX - RDX) > 0.f && fabs(SDY - RDY) > 0.f) {
                            JFLOAT T2 = (RDX * (E2.SY - OY) + (RDY * (OX - E2.SX))) / (SDX * RDY - SDY * RDX);
                            JFLOAT T1 = (E2.SX + SDX * T2 - OX) / RDX;

                            JIF (T1 > 0 && T2 >= 0 && T2 <= 1.f) {
                                JIF (T1 < Min_T1){
                                    Min_T1 = T1;
                                    Min_PX = OX + RDX * T1;
                                    Min_PY = OY + RDY * T1;
                                    Min_Angle = atan2f(Min_PY - OY, Min_PX - OX);
                                    Valid = JTRUE;
                                }
                            }
                        }
                    }
                    JIF (Valid) VectorVisibilityPolygonPoints.push_back({Min_Angle, Min_PX, Min_PY});
                }
            }
        }
        sort(
            VectorVisibilityPolygonPoints.begin(),
            VectorVisibilityPolygonPoints.end(),
            [&](JCONST tuple<JFLOAT, JFLOAT, JFLOAT> &T1, JCONST tuple<JFLOAT, JFLOAT, JFLOAT> &T2) {
                JRETURN get<0>(T1) < get<0>(T2); 
            });
    }

    JBOOL onUserUpdate() {
        Clear(BLANK, BG_BLACK);
        JINT MouseX = GetMouseX();
        JINT MouseY = GetMouseY();

        JIF (keyboard.Keys[Keys::J_MOUSE_LEFT].isReleased) {
            JINT Index = (MouseY / BlockWidth) * WorldWidth + (MouseX / BlockWidth);
            World[Index].Exist = !World[Index].Exist;
        }

        JFLOAT XVALUE = MouseX;
        JFLOAT YVALUE = MouseY;

        ConvertTileMapToPolyMap(VectorEdges, World, 0, 0, WorldWidth, WorldHeight, BlockWidth, WorldWidth);
        JIF (keyboard.Keys[Keys::J_MOUSE_RIGHT].isHeld)
            CalculateVisibilityPolygon(XVALUE, YVALUE, 1000.f);

        JAUTO IT = unique(
          VectorVisibilityPolygonPoints.begin(),
          VectorVisibilityPolygonPoints.end(),
          [&](JCONST tuple<JFLOAT, JFLOAT, JFLOAT> &T1, JCONST tuple<JFLOAT, JFLOAT, JFLOAT> &T2) {
                JRETURN fabs(get<1>(T1) - get<1>(T2)) < 0.1f && fabs(get<2>(T1) - get<2>(T2)) < 0.1f; 
            });

        JIF (keyboard.Keys[Keys::J_MOUSE_RIGHT].isHeld) {
            JIF (VectorVisibilityPolygonPoints.size() > 1) {
                JFOR(JINT i = 0; i < VectorVisibilityPolygonPoints.size() - 1; i++) {
                    DrawTriangle({
                        XVALUE, YVALUE,
                        get<1>(VectorVisibilityPolygonPoints[i]),
                        get<2>(VectorVisibilityPolygonPoints[i]),
                        get<1>(VectorVisibilityPolygonPoints[i + 1]),
                        get<2>(VectorVisibilityPolygonPoints[i + 1]),
                    }, PIXEL_SOLID, FG_GRAY, JTRUE);
                }
                DrawTriangle({
                    XVALUE, YVALUE,
                    get<1>(VectorVisibilityPolygonPoints[VectorVisibilityPolygonPoints.size() - 1]),
                    get<2>(VectorVisibilityPolygonPoints[VectorVisibilityPolygonPoints.size() - 1]),
                    get<1>(VectorVisibilityPolygonPoints[0]),
                    get<2>(VectorVisibilityPolygonPoints[0]),
                }, PIXEL_SOLID, FG_GRAY, JTRUE);
            }
        }

        JFOR(JINT y = 0; y < WorldHeight; y++) 
        JFOR(JINT x = 0; x < WorldWidth; x++) {
            JINT Index = y * WorldWidth + x;
            JIF(World[Index].Exist) {
                DrawBox({BlockWidth, BlockWidth, JSTATICC<JFLOAT>(x * BlockWidth), JSTATICC<JFLOAT>(y * BlockWidth)},
                    PIXEL_SOLID, FG_BLUE, JTRUE);
            }
        }

        DrawString({0, 0}, JTOWSTR(MouseX) + JTOWSTR(MouseY), FG_WHITE, JTRUE);
        JFOR (JAUTO &Edge : VectorEdges) {
            DrawLine({Edge.SX, Edge.SY, Edge.EX, Edge.EY}, PIXEL_SOLID, FG_RED, JTRUE);
            Draw({Edge.SX, Edge.SY}, PIXEL_SOLID, FG_WHITE);
            Draw({Edge.EX, Edge.EY}, PIXEL_SOLID, FG_WHITE);
        }



        JRETURN JTRUE;
    }
};

JINT main() {
    JDM::SetRandomSeed();
    JMS<ShadowCasting>()->Start();
    JRETURN JFALSE;
}
