#include "JDM.h"

class Bird : public BoxEntity
{

public:
    float max_Gravity = 100.f;
    float accelaration = 0.f;
    float velocity = 0.f;

    std::wstring jump_str;
    std::wstring normal_str;
    std::wstring falling;

public:
    Bird() : BoxEntity(10, 6, 20, 37)
    {
        this->initString();
        this->design.clear();
        this->design = this->normal_str;
    }

    void initString()
    {
        this->falling += L"    ----  ";
        this->falling += L"  \\\\---^- ";
        this->falling += L"  -\\\\--O-\\";
        this->falling += L"  --\\----/";
        this->falling += L"   ------ ";
        this->falling += L"    ----  ";

        this->jump_str += L"    ----  ";
        this->jump_str += L"   ----^- ";
        this->jump_str += L"  --/--O-\\";
        this->jump_str += L"  -//----/";
        this->jump_str += L"  //----- ";
        this->jump_str += L"    ----  ";

        this->normal_str += L"    ----  ";
        this->normal_str += L"   ----^- ";
        this->normal_str += L" ____--O-\\";
        this->normal_str += L"  ___----/";
        this->normal_str += L"   ------ ";
        this->normal_str += L"    ----  ";
    }

    void update(float ElapseTime)
    {
        this->accelaration += max_Gravity * ElapseTime;
        if (this->accelaration >= max_Gravity)
            this->accelaration = max_Gravity;
        this->velocity += this->accelaration * ElapseTime;
        if (this->velocity > 5 && this->velocity < 8)
            this->design = this->normal_str;
        else if (this->velocity > 8)
            this->design = this->falling;
        this->y_pos += this->velocity * ElapseTime;
    }

    void jump()
    {
        this->accelaration = 0.f;
        this->velocity = -(this->max_Gravity / 4);
        this->design = this->jump_str;
    }
};

class Pipe : public BoxEntity
{
public:
    Pipe(int height, float x, float y)
        : BoxEntity(10, height, x, y) { fill_design(L'@'); }
};

class WWindow : public Window
{

public:
    Bird *bird;
    BoxEntity *ground;
    std::list<std::shared_ptr<Pipe>> all_pipe;
    std::list<std::shared_ptr<Pipe>>::iterator it_pipe;

    std::wstring GameOver = (L"#### #### #   # #### #### #   # #### ####\n"
                             L"#  # #  # ## ## #    #  # #   # #    #  #\n"
                             L"#    #  # # # # #    #  # #   # #    #  #\n"
                             L"#    #  # # # # #    #  # #   # #    #  #\n"
                             L"#    #### #   # ###  #  # #   # ###  ### \n"
                             L"# ## #  # #   # #    #  # #   # #    #  #\n"
                             L"#  # #  # #   # #    #  #  # #  #    #  #\n"
                             L"#### #  # #   # #### ####   #   #### #  #");

    bool running,
        start;

    float speed = 10;
    float spawn_pipe = 3;

public:
    WWindow(const char *Title, uint16_t Width, uint16_t Height, uint8_t fontSize)
        : Window(Title, Width, Height, fontSize) { this->keyPressValue = 0.5; }

    void onUserCreate()
    {
        start = false;
        running = true;
        bird = new Bird();
        ground = new BoxEntity(ScreenWidth, 10, 0, ScreenHeight - 10);
        ground->fill_design(L'*');
    }

    void keyPressJ(float ElapseTime)
    {
        start = true;
        bird->jump();
    }

    void onUserUpdate(float ElapseTime)
    {
        Clear();
        if (running && start)
        {
            bird->update(ElapseTime);
            spawn_pipe -= ElapseTime;
            if (spawn_pipe <= 0)
            {
                spawn_pipe = 3;
                int height = 10 + rand() % 30;
                this->all_pipe.emplace_back(std::make_shared<Pipe>(height, ScreenWidth, 0));
                this->all_pipe.emplace_back(std::make_shared<Pipe>((ScreenHeight - 10) - (height + 25), ScreenWidth, height + 25));
            }
        }
        it_pipe = all_pipe.begin();
        while (it_pipe != all_pipe.end())
        {
            if (running)
            {
                (*it_pipe)->x_pos -= speed * ElapseTime;
                if ((*it_pipe)->collide_box(6, 4, bird->x_pos + 2, bird->y_pos + 1))
                    running = false;
            }
            if ((*it_pipe)->x_pos <= -20)
                it_pipe = all_pipe.erase(it_pipe);
            else
            {
                (*it_pipe)->render(Screen, ScreenWidth, ScreenHeight);
                it_pipe++;
            }
        }
        if (ground->collide_box(6, 4, bird->x_pos + 2, bird->y_pos + 1))
            running = false;
        if (!running)
            DrawString(20, 20, GameOver);
        bird->renderA(Screen, ScreenWidth, ScreenHeight);
        ground->render(Screen, ScreenWidth, ScreenHeight);
    }
};

int main(int argv, char **argc)
{
    srand(std::time(0));
    WWindow *window = new WWindow("Test", 80, 80, 6);
    window->run();
    return 0;
}
