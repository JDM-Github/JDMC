#include "JDM.h"
#include "eval.h"

void evaluate(std::string &str)
{
    char equate[50];
    float value = eval(str.c_str());
    snprintf(equate, 50, "%.2f", value);
    str.clear();

    int i = 0;
    for (; i < equate[i]; i++)
        str += equate[i];
}

std::wstring num1 = (L"          "
                     L"          "
                     L"    ██    "
                     L"   █ █    "
                     L"     █    "
                     L"     █    "
                     L"     █    "
                     L"   ████   "
                     L"          "
                     L"          ");
std::wstring num2 = (L"          "
                     L"          "
                     L"    ██    "
                     L"   █  █   "
                     L"      █   "
                     L"     █    "
                     L"    █     "
                     L"   ████   "
                     L"          "
                     L"          ");
std::wstring num3 = (L"          "
                     L"          "
                     L"    ██    "
                     L"   █  █   "
                     L"      █   "
                     L"    ██    "
                     L"  █   █   "
                     L"   ████   "
                     L"          "
                     L"          ");
std::wstring num4 = (L"          "
                     L"          "
                     L"    ██    "
                     L"   █ █    "
                     L"  █  █    "
                     L"  █████   "
                     L"     █    "
                     L"   ████   "
                     L"          "
                     L"          ");
std::wstring num5 = (L"          "
                     L"          "
                     L"   ████   "
                     L"   █      "
                     L"   █      "
                     L"    ██    "
                     L"  █   █   "
                     L"   ████   "
                     L"          "
                     L"          ");
std::wstring num6 = (L"          "
                     L"          "
                     L"    ██    "
                     L"   █  █   "
                     L"   █      "
                     L"   ███    "
                     L"   █  █   "
                     L"    ███   "
                     L"          "
                     L"          ");
std::wstring num7 = (L"          "
                     L"          "
                     L"   ████   "
                     L"   █  █   "
                     L"      █   "
                     L"     █    "
                     L"     █    "
                     L"   ████   "
                     L"          "
                     L"          ");
std::wstring num8 = (L"          "
                     L"          "
                     L"    ██    "
                     L"   █  █   "
                     L"   █  █   "
                     L"    ██    "
                     L"   █  █   "
                     L"    ██    "
                     L"          "
                     L"          ");
std::wstring num9 = (L"          "
                     L"          "
                     L"    ██    "
                     L"   █  █   "
                     L"   █  █   "
                     L"    ███   "
                     L"      █   "
                     L"    ██    "
                     L"          "
                     L"          ");
std::wstring num0 = (L"          "
                     L"          "
                     L"    ██    "
                     L"   █  █   "
                     L"   █  █   "
                     L"   █  █   "
                     L"   █  █   "
                     L"    ██    "
                     L"          "
                     L"          ");
std::wstring add = (L"          "
                    L"          "
                    L"    ██    "
                    L"    ██    "
                    L"  ██████  "
                    L"  ██████  "
                    L"    ██    "
                    L"    ██    "
                    L"          "
                    L"          ");
std::wstring minus = (L"          "
                      L"          "
                      L"          "
                      L"          "
                      L"  ██████  "
                      L"          "
                      L"          "
                      L"          "
                      L"          "
                      L"          ");
std::wstring multiply = (L"          "
                         L"          "
                         L"          "
                         L"  █    █  "
                         L"   █  █   "
                         L"    ██    "
                         L"   █  █   "
                         L"  █    █  "
                         L"          "
                         L"          ");
std::wstring division = (L"          "
                         L"          "
                         L"    ██    "
                         L"          "
                         L"  ██████  "
                         L"          "
                         L"    ██    "
                         L"          "
                         L"          "
                         L"          ");
std::wstring equals = (L"          "
                       L"          "
                       L"          "
                       L"          "
                       L"  ██████  "
                       L"          "
                       L"  ██████  "
                       L"          "
                       L"          "
                       L"          ");
std::wstring undo = (L"          "
                     L"          "
                     L"          "
                     L"    █     "
                     L"   ██     "
                     L"  ██████  "
                     L"   ██     "
                     L"    █     "
                     L"          "
                     L"          ");
std::wstring dot = (L"          "
                    L"          "
                    L"          "
                    L"          "
                    L"          "
                    L"          "
                    L"          "
                    L"    ██    "
                    L"    ██    "
                    L"          ");

std::wstring Title = (L"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
                      L"░                                        ░"
                      L"░  ███ ███ █   ███ █ █ █   ███ ███ ███   ░"
                      L"░  █   █ █ █   █   █ █ █   █ █  █  █     ░"
                      L"░  █   █ █ █   █   █ █ █   █ █  █  █     ░"
                      L"░  █   ███ █   █   █ █ █   ███  █  ███   ░"
                      L"░  █   █ █ █   █   █ █ █   █ █  █  █     ░"
                      L"░  ███ █ █ ███ ███ ███ ███ █ █  █  ███   ░"
                      L"░                                        ░"
                      L"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░");

class Key : public Entity
{
public:
    Key(float x, float y, int num) : Entity(10, 10, x, y)
    {
        design.clear();
        switch (num)
        {
        case 1:
            design = num1;
            break;
        case 2:
            design = num2;
            break;
        case 3:
            design = num3;
            break;
        case 4:
            design = num4;
            break;
        case 5:
            design = num5;
            break;
        case 6:
            design = num6;
            break;
        case 7:
            design = num7;
            break;
        case 8:
            design = num8;
            break;
        case 9:
            design = num9;
            break;
        case 0:
            design = num0;
            break;
        case 11:
            design = add;
            break;
        case 12:
            design = minus;
            break;
        case 13:
            design = division;
            break;
        case 14:
            design = multiply;
            break;
        case 15:
            design = equals;
            break;
        case 16:
            design = undo;
            break;
        case 17:
            design = dot;
            break;
        }
        for (int r = 0; r < 10; r++)
            for (int c = 0; c < 10; c++)
                if (r == 0 || r == 9 || c == 0 || c == 9)
                    design[r * 10 + c] = 0x2591;
    }
};

class WWindow : public Window
{
public:
    Entity board = {42, 10, 0, 0};
    Key key1 = {1, 21, 1};
    Key key2 = {11, 21, 2};
    Key key3 = {21, 21, 3};
    Key key4 = {1, 31, 4};
    Key key5 = {11, 31, 5};
    Key key6 = {21, 31, 6};
    Key key7 = {1, 41, 7};
    Key key8 = {11, 41, 8};
    Key key9 = {21, 41, 9};

    Key keydot = {1, 51, 17};
    Key key0 = {11, 51, 0};

    Key keyadd = {31, 21, 11};
    Key keymin = {31, 31, 12};
    Key keydiv = {31, 41, 13};
    Key keymul = {31, 51, 14};
    Key keyeq = {21, 51, 15};

    std::wstring line = L"██████████████████████████████████████████";
    Entity box = {10, 10, 1, 21};

    std::string the_Equation;

public:
    WWindow(const char *Title, uint16_t Width, uint16_t Height)
        : Window(Title, Width, Height) {}
    WWindow(uint16_t Width, uint16_t Height)
        : Window("Window", Width, Height) {}

    void onUserCreate()
    {
        the_Equation = "45";
        box.design.clear();
        board.design = Title;
        box.design = (L"██████████"
                      L"█        █"
                      L"█        █"
                      L"█        █"
                      L"█        █"
                      L"█        █"
                      L"█        █"
                      L"█        █"
                      L"█        █"
                      L"██████████");
    }

    void keyPressW(float ElapseTime)
    {
        if (box.y_pos - 10 >= 21)
            box.y_pos -= 10;
    }
    void keyPressS(float ElapseTime)
    {
        if (box.y_pos + 10 < ScreenHeight - 1)
            box.y_pos += 10;
    }
    void keyPressA(float ElapseTime)
    {
        if (box.x_pos - 10 >= 1)
            box.x_pos -= 10;
    }
    void keyPressD(float ElapseTime)
    {
        if (box.x_pos + 10 < ScreenWidth - 1)
            box.x_pos += 10;
    }

    void keyPressG(float ElapseTime)
    {
        if (the_Equation.size() > 0)
            the_Equation.resize(the_Equation.size() - 1);
    }

    void keyPressF(float ElapseTime)
    {
        if (key1.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '1';
        else if (key2.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '2';
        else if (key3.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '3';
        else if (key4.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '4';
        else if (key5.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '5';
        else if (key6.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '6';
        else if (key7.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '7';
        else if (key8.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '8';
        else if (key9.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '9';
        else if (key0.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '0';
        else if (keydot.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '.';
        else if (keyadd.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '+';
        else if (keymin.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '-';
        else if (keydiv.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '/';
        else if (keymul.collide_point(box.x_pos + 1, box.y_pos + 1))
            the_Equation += '*';
        else if (keyeq.collide_point(box.x_pos + 1, box.y_pos + 1))
            evaluate(the_Equation);
    }

    void onUserupdate(float ElapseTime)
    {
        Clear();
        board.render(Screen, ScreenWidth, ScreenHeight);
        key1.render(Screen, ScreenWidth, ScreenHeight);
        key2.render(Screen, ScreenWidth, ScreenHeight);
        key3.render(Screen, ScreenWidth, ScreenHeight);
        key4.render(Screen, ScreenWidth, ScreenHeight);
        key5.render(Screen, ScreenWidth, ScreenHeight);
        key6.render(Screen, ScreenWidth, ScreenHeight);
        key7.render(Screen, ScreenWidth, ScreenHeight);
        key8.render(Screen, ScreenWidth, ScreenHeight);
        key9.render(Screen, ScreenWidth, ScreenHeight);
        key0.render(Screen, ScreenWidth, ScreenHeight);

        keyadd.render(Screen, ScreenWidth, ScreenHeight);
        keymin.render(Screen, ScreenWidth, ScreenHeight);
        keydiv.render(Screen, ScreenWidth, ScreenHeight);
        keymul.render(Screen, ScreenWidth, ScreenHeight);
        keyeq.render(Screen, ScreenWidth, ScreenHeight);
        keydot.render(Screen, ScreenWidth, ScreenHeight);

        box.renderA(Screen, ScreenWidth, ScreenHeight);

        int rsize = (the_Equation.size() < 6) ? the_Equation.size() : 6;
        for (int i = 0; i < rsize; i++)
        {
            std::wstring design;
            int y_adder = 0;
            int x_adder = 0;
            char num = the_Equation[the_Equation.size() - i - 1];
            switch (num)
            {
            case '1':
                design = num1;
                break;
            case '2':
                design = num2;
                break;
            case '3':
                design = num3;
                break;
            case '4':
                design = num4;
                break;
            case '5':
                design = num5;
                break;
            case '6':
                design = num6;
                break;
            case '7':
                design = num7;
                break;
            case '8':
                design = num8;
                break;
            case '9':
                design = num9;
                break;
            case '0':
                design = num0;
                break;
            case '.':
                design = dot;
                break;
            case '+':
                design = add;
                break;
            case '-':
                design = minus;
                break;
            case '*':
                design = multiply;
                break;
            case '/':
                design = division;
                break;
            }
            for (int j = 0; j < 100; j++)
            {
                if ((j + 1) % 10 == 0)
                {
                    x_adder = 0;
                    y_adder++;
                }
                if (design[j] != L' ')
                    Draw(0 + ((rsize - 1 - i) * 6) + x_adder, 11 + y_adder, design[j]);
                x_adder++;
            }
        }
    }
};

int main(int argv, char **argc)
{
    WWindow *window = new WWindow("Test", 42, 62);
    window->run();
    return 0;
}
