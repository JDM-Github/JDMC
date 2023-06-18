#pragma once
#include <ctime>
#include <fstream>
#include <math.h>
#include <cmath>
#include <algorithm>
#include "Jenums.hpp"

#define PI 3.14159265358979323846
#define PHI 1.618

#define NORTH 0
#define SOUTH 1
#define WEST 2
#define EAST 3

JNAMESPACE JDM{

    JSTRUCT Edges { JFLOAT SX, SY, EX, EY; };
    JSTRUCT Cell {
        JINT EdgeId[4];
        JBOOL EdgeExist[4];
        JBOOL Exist = JFALSE;
    };

    JSTRUCT Node {
        JBOOL Obstacle = JFALSE;
        JBOOL Visited = JFALSE;
        JFLOAT GlobalGoal;
        JFLOAT LocalGoal;
        JINT X, Y;
        JVECTOR<Node *> VectorNeighbors;
        Node *Parent;
    };

    JCONSTEXPR JINT GetIndex(JINT x, JINT y, JINT Pitch) { JRETURN x + (y * Pitch); }

    JVOID GetConnection(JINT MapWidth, JINT MapHeight, JDM::Node *Nodes, JBOOL Diagonal = JFALSE) {
        JFOR (JINT y = 0; y < MapHeight; y++)
            JFOR (JINT x = 0; x < MapWidth; x++) {
                JINT Index = JDM::GetIndex(x, y, MapWidth);
                Nodes[Index].VectorNeighbors.clear();
                JIF(y > 0) Nodes[Index].VectorNeighbors.push_back(&Nodes[JDM::GetIndex(x, y - 1, MapWidth)]);
                JIF(x > 0) Nodes[Index].VectorNeighbors.push_back(&Nodes[JDM::GetIndex(x - 1, y, MapWidth)]);
                JIF(y < MapHeight-1) Nodes[Index].VectorNeighbors.push_back(&Nodes[JDM::GetIndex(x, y + 1, MapWidth)]);
                JIF(x < MapWidth-1) Nodes[Index].VectorNeighbors.push_back(&Nodes[JDM::GetIndex(x + 1, y, MapWidth)]);
            
                JIF (Diagonal) {
                    JIF(y > 0 && x > 0) Nodes[Index].VectorNeighbors.push_back(&Nodes[JDM::GetIndex(x - 1, y - 1, MapWidth)]);
                    JIF(y > 0 && x < MapWidth-1) Nodes[Index].VectorNeighbors.push_back(&Nodes[JDM::GetIndex(x + 1, y - 1, MapWidth)]);
                    JIF(y < MapHeight-1 && x > 0) Nodes[Index].VectorNeighbors.push_back(&Nodes[JDM::GetIndex(x - 1, y + 1, MapWidth)]);
                    JIF(y < MapWidth-1 && x < MapWidth - 1) Nodes[Index].VectorNeighbors.push_back(&Nodes[JDM::GetIndex(x + 1, y + 1, MapWidth)]);
                }
            }
    }

    JVOID SetupNode(JINT MapWidth, JINT MapHeight, JDM::Node *Nodes) {
        JFOR (JINT y = 0; y < MapHeight; y++)
            JFOR (JINT x = 0; x < MapWidth; x++) {
                JINT Index = GetIndex(x, y, MapWidth);
                Nodes[Index].X = x;
                Nodes[Index].Y = y;
                Nodes[Index].Visited = JFALSE;
                Nodes[Index].Obstacle = JFALSE;
                Nodes[Index].Parent = nullptr;
            }
        
        JDM::GetConnection(MapWidth, MapHeight, Nodes);
    }

    JVOID Solve_AStar(JINT MapWidth, JINT MapHeight, JDM::Node *Nodes, JDM::Node *NodeStart, JDM::Node *NodeEnd) {
        JFOR (JINT y = 0; y < MapHeight; y++)
            JFOR (JINT x = 0; x < MapWidth; x++) {
                JINT Index = GetIndex(x, y, MapWidth);
                Nodes[Index].Visited = JFALSE;
                Nodes[Index].GlobalGoal = 9999.f;
                Nodes[Index].LocalGoal = 9999.f;
                Nodes[Index].Parent = nullptr;
            }
        JAUTO Distance = [](Node *A, Node *B) { JRETURN sqrtf((A->X - B->X)*(A->X - B->X) + (A->Y - B->Y)*(A->Y - B->Y)); };
        JAUTO Heuristic = [Distance](Node *A, Node *B) { JRETURN Distance(A, B); };

        Node *CurrentNode = NodeStart;
        NodeStart->LocalGoal = 0.f;
        NodeStart->GlobalGoal = Heuristic(NodeStart, NodeEnd);

        JLIST<Node *> ListNotTestedNode;
        ListNotTestedNode.push_back(NodeStart);
        JWHILE (!ListNotTestedNode.empty() && CurrentNode != NodeEnd) {
            ListNotTestedNode.sort([](JCONST Node *Lhs, JCONST Node *Rhs) { JRETURN Lhs->GlobalGoal < Rhs->GlobalGoal; });
            JWHILE (!ListNotTestedNode.empty() && ListNotTestedNode.front()->Visited) ListNotTestedNode.pop_front();

            JIF(ListNotTestedNode.empty()) JBREAK;

            CurrentNode = ListNotTestedNode.front();
            CurrentNode->Visited = JTRUE;

            JFOR (JAUTO NodeNeighbor : CurrentNode->VectorNeighbors) {
                JIF (!NodeNeighbor->Visited && NodeNeighbor->Obstacle == 0)
                    ListNotTestedNode.push_back(NodeNeighbor);
                
                JFLOAT PossibilityLowerGoal = CurrentNode->LocalGoal + Distance(CurrentNode, NodeNeighbor);

                JIF (PossibilityLowerGoal < NodeNeighbor->LocalGoal) {
                    NodeNeighbor->Parent = CurrentNode;
                    NodeNeighbor->LocalGoal = PossibilityLowerGoal;
                    NodeNeighbor->GlobalGoal = NodeNeighbor->LocalGoal + Heuristic(NodeNeighbor, NodeEnd);
                }
            }
        }
    }

    JVOID AddEdge(JVECTOR<JDM::Edges> &VectorEdges, JDM::Cell *World, JINT Index, JINT Dir, JINT RDir, JINT CONSTANT,
        JINT XAdd, JINT YAdd, JINT BWidth, JFLOAT SX, JFLOAT SY, JFLOAT EX, JFLOAT EY) {
        JIF (!World[RDir].Exist) {
            JIF (World[Dir].EdgeExist[CONSTANT]) {
                VectorEdges[World[Dir].EdgeId[CONSTANT]].EX += XAdd;
                VectorEdges[World[Dir].EdgeId[CONSTANT]].EY += YAdd;
                World[Index].EdgeId[CONSTANT] = World[Dir].EdgeId[CONSTANT];
                World[Index].EdgeExist[CONSTANT] = JTRUE;
            } JELSE {
                Edges edge = {SX, SY, EX, EY};
                JINT edgeId = VectorEdges.size();
                VectorEdges.push_back(edge);
                World[Index].EdgeId[CONSTANT] = edgeId;
                World[Index].EdgeExist[CONSTANT] = JTRUE;
            }
        }
    }

    JVOID ConvertTileMapToPolyMap(JVECTOR<JDM::Edges> &VectorEdges, JDM::Cell *World, JINT SX, JINT SY, JINT W, JINT H, JINT BWidth, JINT Pitch) {
        VectorEdges.clear();
        JFOR(JINT x = 0; x < W; x++) 
        JFOR(JINT y = 0; y < H; y++) 
            JFOR(JINT i = 0; i < 4; i++) {
                JINT Index = (y + SY) * Pitch + (x + SX);
                World[Index].EdgeExist[i] = JFALSE;
                World[Index].EdgeId[i] = 0;
            }
        JFOR(JINT x = 1; x < W - 1; x++) 
        JFOR(JINT y = 1; y < H - 1; y++) {
            JINT Index =  (y + SY) * Pitch + (x + SX);
            JINT North =  (y + SY - 1) * Pitch + (x + SX);
            JINT South =  (y + SY + 1) * Pitch + (x + SX);
            JINT West =  (y + SY) * Pitch + (x + SX - 1) ;
            JINT East =  (y + SY) * Pitch + (x + SX + 1);

            JIF (World[Index].Exist) {
                JDM::AddEdge(VectorEdges, World, Index, North, West, WEST, 0, BWidth, BWidth,
                        (SX + x) * BWidth, (SY + y) * BWidth, ((SX + x) * BWidth), ((SY + y) * BWidth) + BWidth);
                JDM::AddEdge(VectorEdges, World, Index, North, East, EAST, 0, BWidth, BWidth,
                        (SX + x + 1) * BWidth, (SY + y) * BWidth, ((SX + x + 1) * BWidth), ((SY + y) * BWidth) + BWidth);
                JDM::AddEdge(VectorEdges, World, Index, West, North, NORTH, BWidth, 0, BWidth,
                        (SX + x) * BWidth, (SY + y) * BWidth, ((SX + x) * BWidth) + BWidth, ((SY + y) * BWidth));
                JDM::AddEdge(VectorEdges, World, Index, West, South, SOUTH, BWidth, 0, BWidth,
                        (SX + x) * BWidth, (SY + y + 1) * BWidth, ((SX + x) * BWidth) + BWidth, ((SY + y + 1) * BWidth));
            }
        }
    }

    JVOID SetRandomSeed() { srand(std::time(JNONE)); }
    JCONSTEXPR JBOOL collide_point(JCONST JDM::SizePosDF position, JCFLOAT x1, JCFLOAT y1) {
        JRETURN(position.X <= x1 && x1 < position.X + position.Width && position.Y <= y1 && y1 < position.Y + position.Height);
    }
    JCONSTEXPR JBOOL collide_point(JCONST JDM::SizePosDF position, JCONST JDM::Pos2D MousePosition) {
        JRETURN(position.X <= MousePosition.X && MousePosition.X < position.X + position.Width
             && position.Y <= MousePosition.Y && MousePosition.Y < position.Y + position.Height);
    }
    JCONSTEXPR JBOOL collide_box(JCONST JDM::SizePosDF firstPosition,
                                 JCONST JDM::SizePosDF secondPosition) {
        JIF(firstPosition.X + firstPosition.Width < secondPosition.X) JRETURN JFALSE;
        JIF(firstPosition.X > secondPosition.X + secondPosition.Width) JRETURN JFALSE;
        JIF(firstPosition.Y + firstPosition.Height < secondPosition.Y) JRETURN JFALSE;
        JIF(firstPosition.Y > secondPosition.Y + secondPosition.Height) JRETURN JFALSE;
        JRETURN JTRUE;
    }
    JBOOL checkExist(JCSTR &file) {
        std::ifstream ifile;
        ifile.open(file);
        JBOOL isExist = (ifile) ? JTRUE : JFALSE;
        ifile.close();
        JRETURN isExist;
    }

    JCONSTEXPR JVOID Reverse(JFLOAT &Value) { Value = Value * 1; }
    JCONSTEXPR JVOID Reverse(JINT &Value) { Value = Value * 1; }
    JCONSTEXPR JVOID Negative(JFLOAT &Value) { Value = std::abs(Value) * -1; }
    JCONSTEXPR JVOID Negative(JINT &Value) { Value = std::abs(Value) * -1; }
    JCONSTEXPR JVOID Positive(JFLOAT &Value) { Value = std::abs(Value); }
    JCONSTEXPR JVOID Positive(JINT &Value) { Value = std::abs(Value); }

    JCONSTEXPR JFLOAT RetReverse(JFLOAT Value) { JRETURN Value * 1; }
    JCONSTEXPR JINT RetReverse(JINT Value) { JRETURN Value * 1; }
    JCONSTEXPR JFLOAT RetNegative(JFLOAT Value) { JRETURN std::abs(Value) * -1; }
    JCONSTEXPR JINT RetNegative(JINT Value) { JRETURN std::abs(Value) * -1; }
    JCONSTEXPR JFLOAT RetPositive(JFLOAT Value) { JRETURN std::abs(Value); }
    JCONSTEXPR JINT RetPositive(JINT Value) { JRETURN std::abs(Value); }

    JTEMPLATE<JCLASS T>
    JFLOAT Max(T maximumValue) { JRETURN maximumValue; }
    JTEMPLATE<JCLASS T, JCLASS ... Args>
    JFLOAT Max(T firstValue, T secondValue, Args... args) {
        JRETURN Max(((firstValue > secondValue) ? firstValue : secondValue), args...);
    }

    JTEMPLATE<JCLASS T>
    T Max(JVECTOR<T> Value) {
        T MaxValue = Value[0];
        JFOR(JINT i = 0; i < Value.size(); i++) {
            JIF(MaxValue < Value[i]) MaxValue = Value[i];
        }
        JRETURN MaxValue;
    }

    JTEMPLATE<JCLASS T>
    JINT MaxIndex(JVECTOR<T> Value) {
        JINT Index = 0;
        T MaxValue = Value[0];
        JFOR(JINT i = 0; i < Value.size(); i++) {
            JIF(MaxValue < Value[i]) {
                Index = i;
                MaxValue = Value[i];
            }
        }
        JRETURN Index;
    }

    JTEMPLATE<JCLASS T>
    JFLOAT Min(T maximumValue) { JRETURN maximumValue; }
    JTEMPLATE<JCLASS T, JCLASS ... Args>
    JFLOAT Min(T firstValue, T secondValue, Args... args) {
        JRETURN Min(((firstValue < secondValue) ? firstValue : secondValue), args...);
    }
    JINT GetVectorIndex(JVECTOR<JINT> &Vector, JINT Key) {
        JVECTOR<JINT>::iterator itr = std::find(Vector.begin(), Vector.end(), Key);
        JRETURN std::distance(Vector.begin(), itr);
    }
    JINT Randint(JINT first, JINT second) { JRETURN first + (Random() % (second + (first * -1))); }
    JFLOAT Randfloat(JINT first, JINT second) {
        JINT FirstValue = (first + (Random() % (second + (first * -1)))) + 1;
        JFLOAT SecondValue = (9.0f / (9 + (Random() % 100)));
        JRETURN FirstValue - SecondValue;
    }

    JTEMPLATE<JCLASS T>
    JBOOL Any(T value) { JRETURN value; }
    JTEMPLATE <JCLASS First, JCLASS ... Args>
    JBOOL Any(First first, Args... args) {
        JIF(first) JRETURN JTRUE;
        JRETURN Any(args...);
    }

    JTEMPLATE<JCLASS T>
    JBOOL All(T value) { JRETURN value; }
    JTEMPLATE <JCLASS First, JCLASS ... Args>
    JBOOL All(First first, Args... args) {
        JIF(first) JRETURN All(args...);
        JRETURN JFALSE;
    }
};

