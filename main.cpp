#include "JDM.h"

class WWindow : public Window
{
public:
    BoxEntity entity = BoxEntity(10, 10, 30, 30);

public:
    WWindow() : Window("Game", 100, 75, 8) {}
    JBOOL onUserCreate() { return JTRUE; }
    JBOOL onUserUpdate(float ElapseTime)
    {
        Clear();
        return JTRUE;
    }
};

int main()
{
    WWindow window = WWindow();
    window.Start();
    return 0;
}
