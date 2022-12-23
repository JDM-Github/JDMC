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
        Clear(S1, FG_CYAN);
        return JTRUE;
    }
};

int main()
{
    WWindow window = WWindow();
    window.Start();
    return 0;
}
