#include "JDM.hpp"

JCLASS ConsoleExample : JPUBLIC JWINDOW {
JPRIVATE:
    JINT MapWidth = 20;
    JINT MapHeight = 20;

    JINT NodeSize = 6;
    JINT NodePadd = 1;

    JBOOL ConnectionDiag = JFALSE;
    JDM::Node *Nodes = nullptr;
    JDM::Node *NodeStart = nullptr;
    JDM::Node *NodeEnd = nullptr;

JPUBLIC:
    ConsoleExample() : JWINDOW("ConsoleExample", 120, 120, 6, 6) { }
    JBOOL onUserCreate() {
        MapWidth = GetWidth() / NodeSize;
        MapHeight = GetHeight() / NodeSize;
        Nodes = JNEW JDM::Node[MapWidth * MapHeight];
        SetupNode(MapWidth, MapHeight, Nodes);
        NodeStart = &Nodes[(MapHeight / 2) * MapWidth + 1];
        NodeEnd = &Nodes[(MapHeight / 2) * MapWidth + MapWidth - 2];
        Solve_AStar(MapWidth, MapHeight, Nodes, NodeStart, NodeEnd);
        JRETURN JTRUE;
    }

    JBOOL onUserUpdate() {
        Clear(BLANK, BG_BLACK);

        JINT MouseX = GetMouseX();
        JINT MouseY = GetMouseY();

        JIF (keyboard.Keys[Keys::J_MOUSE_LEFT].isReleased) {
            JIF (MouseX / NodeSize >= 0 && MouseX / NodeSize < MapWidth)
                JIF (MouseY / NodeSize >= 0 && MouseY / NodeSize < MapHeight) {
                    JINT Index = GetMouseIndex(NodeSize, MapWidth);
                    JIF (keyboard.Keys[Keys::J_SHIFT].isHeld) {
                        NodeStart = &Nodes[Index];
                        Nodes[Index].Obstacle = JFALSE;
                    }
                    JELSE JIF (keyboard.Keys[Keys::J_CTRL].isHeld) {
                        NodeEnd = &Nodes[Index];
                        Nodes[Index].Obstacle = JFALSE;
                    }
                    JELSE JIF (&Nodes[Index] != NodeStart && &Nodes[Index] != NodeEnd) 
                        Nodes[Index].Obstacle = !Nodes[Index].Obstacle;
                    JDM::Solve_AStar(MapWidth, MapHeight, Nodes, NodeStart, NodeEnd);
                }
        }
        JIF (keyboard.Keys[Keys::J_PKEY].isReleased) {
            ConnectionDiag = !ConnectionDiag;
            JDM::GetConnection(MapWidth, MapHeight, Nodes, ConnectionDiag);
            JDM::Solve_AStar(MapWidth, MapHeight, Nodes, NodeStart, NodeEnd);
        }

        JFOR (JINT y = 0; y < MapHeight; y++)
            JFOR (JINT x = 0; x < MapWidth; x++) {
                JINT Index = GetIndex(x, y, MapWidth);
                JIF (&Nodes[Index] == NodeStart) 
                    DrawBox({NodeSize, NodeSize, JSTATICC<JFLOAT>(x * NodeSize),  JSTATICC<JFLOAT>(y * NodeSize)},
                        PIXEL_SOLID, FG_GREEN);
                JELSE JIF (&Nodes[Index] == NodeEnd) 
                    DrawBox({NodeSize, NodeSize, JSTATICC<JFLOAT>(x * NodeSize),  JSTATICC<JFLOAT>(y * NodeSize)},
                        PIXEL_SOLID, FG_RED);
                JELSE
                    DrawBox({NodeSize - (NodePadd * 2), NodeSize - (NodePadd * 2),
                        NodePadd + JSTATICC<JFLOAT>(x * NodeSize),
                        NodePadd + JSTATICC<JFLOAT>(y * NodeSize)},
                        PIXEL_SOLID, (Nodes[Index].Obstacle) ? FG_RED : ((Nodes[Index].Visited) ? FG_DARK_CYAN : FG_DARK_BLUE));
            }

        Drawer::DisplayPath(JTHIS, NodeEnd, NodeSize);
        JRETURN JTRUE;
    }
};

JINT main() {
    JDM::SetRandomSeed();
    JMS<ConsoleExample>()->Start();
    JRETURN JFALSE;
}
