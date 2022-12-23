#include "JDM.h"

class WWindow : public JWINDOW
{
public:
    WWindow() : JWINDOW("Game", 200, 150, 4, 4) {}
    JBOOL onUserCreate()
    {
    }

    JBOOL onUserUpdate(float ElapseTime)
    {
        Clear(S1, FG_BLACK);
        SetColorIndex(0, VERY_DARK_BLUE);
        return JTRUE;
    }
};

int main()
{
    WWindow window = WWindow();
    window.Start();
    return 0;
}
