#include "JDM.h"

class WWindow : public Window
{
public:
    JWSTR CarDesign[3];
    JFLOAT CarPos = 0.f;
    JFLOAT Distance = 0.f;
    JFLOAT CarSpeed = 0.f;
    JSHORT CarWidth = 14, CarHeight = 7;
    JFLOAT PlayerCurvature = 0.f;
    JFLOAT trackCurvature = 0.f;

    JFLOAT Curvature = 0.f;
    JFLOAT trackDistance = 0.f;
    std::vector<std::pair<JFLOAT, JFLOAT>> VectorTrack;

public:
    WWindow() : Window("Game", 150, 100, 4, 6) {}
    JBOOL onUserCreate()
    {
        VectorTrack.push_back(std::make_pair(0.f, 10.f));
        VectorTrack.push_back(std::make_pair(1.f, 200.f));
        VectorTrack.push_back(std::make_pair(0.f, 400.f));
        VectorTrack.push_back(std::make_pair(-1.f, 400.f));
        VectorTrack.push_back(std::make_pair(0.f, 100.f));
        VectorTrack.push_back(std::make_pair(2.f, 400.f));
        VectorTrack.push_back(std::make_pair(0.f, 600.f));
        VectorTrack.push_back(std::make_pair(-1.5f, 400.f));
        VectorTrack.push_back(std::make_pair(0.f, 400.f));
        VectorTrack.push_back(std::make_pair(1.f, 600.f));
        VectorTrack.push_back(std::make_pair(-0.5f, 200.f));
        VectorTrack.push_back(std::make_pair(1.f, 300.f));
        VectorTrack.push_back(std::make_pair(-1.f, 400.f));
        VectorTrack.push_back(std::make_pair(0.f, 200.f));

        for (auto track : VectorTrack)
            trackDistance += track.second;

        CarDesign[0] += L"      44      \n";
        CarDesign[0] += L"   0 4224 0   \n";
        CarDesign[0] += L"    441144    \n";
        CarDesign[0] += L" 0  333333  0 \n";
        CarDesign[0] += L"80873333337808\n";
        CarDesign[0] += L"80  333333  08\n";
        CarDesign[0] += L" 0   1331   0 \n";

        CarDesign[1] += L"     44       \n";
        CarDesign[1] += L"  0 4224 0    \n";
        CarDesign[1] += L"    441144    \n";
        CarDesign[1] += L" 0  333333  0 \n";
        CarDesign[1] += L"80873333337808\n";
        CarDesign[1] += L"80  333333  08\n";
        CarDesign[1] += L" 0   1331   0 \n";

        CarDesign[2] += L"       44     \n";
        CarDesign[2] += L"    0 4224 0  \n";
        CarDesign[2] += L"    441144    \n";
        CarDesign[2] += L" 0  333333  0 \n";
        CarDesign[2] += L"80873333337808\n";
        CarDesign[2] += L"80  333333  08\n";
        CarDesign[2] += L" 0   1331   0 \n";
    }

    JBOOL onUserUpdate(float ElapseTime)
    {
        Clear(S0, BG_AQUA);

        for (JINT x = 0; x < GetWidth(); x++)
        {
            JINT HillHeight = (JINT)(fabs(sinf(x * 0.01 + trackCurvature) * 30.f));
            for (JINT y = GetHeight() / 2 - HillHeight; y < GetHeight() / 2; y++)
                Draw(x, y, S1, FG_LYELLOW, 1);
        }

        for (JINT x = 0; x < GetWidth() * 2; x++)
        {
            JINT HillHeight = (JINT)(fabs(sinf(x * 0.01 + trackCurvature) * 30.f));
            for (JINT y = GetHeight() / 2 - HillHeight; y < GetHeight() / 2; y++)
                Draw(x - GetWidth() / 2, y, S1, FG_YELLOW, 1);
        }

        if (keyboard.Keys[Keys::J_WKEY].isHeld)
            CarSpeed += 2.f * ElapseTime;
        else
            CarSpeed -= 1.f * ElapseTime;

        JINT PlayerDirection = 0;
        if (keyboard.Keys[Keys::J_AKEY].isHeld)
        {
            PlayerCurvature -= 0.7f * ElapseTime;
            PlayerDirection = 1;
        }

        if (keyboard.Keys[Keys::J_DKEY].isHeld)
        {
            PlayerCurvature += 0.7f * ElapseTime;
            PlayerDirection = 2;
        }

        if (fabs(PlayerCurvature - trackCurvature) >= 0.8f)
            CarSpeed -= 5.0f * ElapseTime;

        if (CarSpeed < 0.f)
            CarSpeed = 0.f;
        if (CarSpeed > 1.f)
            CarSpeed = 1.f;
        Distance += (200 * CarSpeed) * ElapseTime;

        JFLOAT Offset = 0.f;
        JINT trackSection = 0;

        if (Distance >= trackDistance)
            Distance -= trackDistance;

        while (trackSection < VectorTrack.size() && Offset <= Distance)
        {
            Offset += VectorTrack[trackSection].second;
            trackSection++;
        }
        JFLOAT targetCurvature = VectorTrack[trackSection - 1].first;
        JFLOAT currentCurvature = (targetCurvature - Curvature) * ElapseTime * CarSpeed;
        Curvature += currentCurvature;

        trackCurvature += (Curvature)*ElapseTime * CarSpeed;

        for (JINT y = 0; y < GetHeight() / 2; y++)
        {
            for (JINT x = 0; x < GetWidth(); x++)
            {
                JFLOAT Perspective = (JFLOAT)y / (GetWidth() / 2.0);
                JFLOAT MiddlePoint = 0.5f + Curvature * powf(1.f - Perspective, 4);
                JFLOAT RoadWidth = 0.1f + Perspective * 0.9;
                JFLOAT ClipWidth = RoadWidth * 0.15;
                RoadWidth *= 0.5f;

                JINT LeftGrass = (MiddlePoint - RoadWidth - ClipWidth) * GetWidth();
                JINT LeftClip = (MiddlePoint - RoadWidth) * GetWidth();
                JINT RightGrass = (MiddlePoint + RoadWidth + ClipWidth) * GetWidth();
                JINT RightClip = (MiddlePoint + RoadWidth) * GetWidth();

                JINT Row = GetHeight() / 2 + y;
                JINT GrassColor = sinf(20.f * powf(1.f - Perspective, 3) + Distance * 0.1f) > 0.f ? FG_LGREEN : FG_GREEN;
                JINT ClipColor = sinf(80.f * powf(1.f - Perspective, 3) + Distance * 0.1f) > 0.f ? FG_RED : FG_LWHITE;
                JINT GroundColor = sinf(20.f * powf(1.f - Perspective, 3) + Distance * 0.1f) > 0.f ? FG_GRAY : FG_WHITE;

                if (x >= 0 && x < LeftGrass)
                    Draw(x, Row, S1, GrassColor);
                if (x >= LeftGrass && x < LeftClip)
                    Draw(x, Row, S1, ClipColor);
                if (x >= LeftClip && x < RightClip)
                    Draw(x, Row, S1, GroundColor);
                if (x >= RightClip && x < RightGrass)
                    Draw(x, Row, S1, ClipColor);
                if (x >= RightGrass && x < GetWidth())
                    Draw(x, Row, S1, GrassColor);
            }
        }

        std::to_wstring(Distance);
        CarPos = PlayerCurvature - trackCurvature;
        JINT NCarPos = (JFLOAT)GetWidth() / 2.0 + ((GetWidth() * CarPos) / 2) - 7;
        DrawCString(NCarPos, GetHeight() / 2 + 30, CarDesign[PlayerDirection], 1);

        return JTRUE;
    }
};

int main()
{
    WWindow window = WWindow();
    window.Start();
    return 0;
}
