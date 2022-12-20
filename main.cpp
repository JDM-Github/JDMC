#include "JDM.h"

class WWindow : public Window
{
public:
    WWindow() : Window("Game", 200, 150, 4) { }
    void onUserCreate() { }
    void onUserUpdate(float ElapseTime) { }
};

int main()
{
    WWindow window = WWindow();
    window.run();
    return 0;
}