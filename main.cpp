#include "JDM.h"

using namespace std;

class WWindow : public Window
{
public:
public:
    WWindow(const char *Title, uint16_t Width, uint16_t Height, uint8_t fontSize)
        : Window(Title, Width, Height, fontSize) { keyPressValue = 0; }

    void onUserCreate()
    {
    }

    void onUserUpdate(float ElapseTime)
    {
    }
};

int main(int argv, char **argc)
{
    WWindow *window = new WWindow("Test", 150, 100, 5);
    window->run();
    return 0;
}
