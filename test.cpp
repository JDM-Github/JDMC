// #include <iostream>
// #include <list>
// #include <chrono>
// #include <memory>
// #include <algorithm>
// #include <time.h>
// #include <Windows.h>

// using namespace std;

// const short ScreenWidth = 100;
// const short ScreenHeight = 50;
// bool running = true;

// class Entity
// {
// protected:
//     float __x, __y;
//     int __width, __height;
//     wstring design;

// public:
//     Entity(const float x, const float y)
//         : __x(x), __y(y) {}
//     void render(wchar_t *screen)
//     {
//         for (int r = 0; r < this->__height; r++)
//             for (int c = 0; c < this->__width; c++)
//             {
//                 if (this->__x + c >= ScreenWidth || this->__x + c <= 0 || this->__y + r >= ScreenHeight || this->__y + r <= 0)
//                     continue;
//                 screen[(((int)this->__y + r) * ScreenWidth) + c + (int)this->__x] = this->design[r * this->__width + c];
//             }
//     }

//     int collide_point(float x, float y) { return (this->__x <= x && x <= this->__width + this->__x && this->__y <= y && y <= this->__height + this->__y); }

//     float getx() { return this->__x; }
//     float gety() { return this->__y; }
//     float getw() { return this->__width; }
//     float geth() { return this->__height; }
// };

// class Player : public Entity
// {
// private:
//     int __speed;

// public:
//     float reload = 0.2;
//     Player(float x, float y)
//         : Entity(x, y) { this->initVariables(); }

//     void move(char press, float ET)
//     {
//         switch (press)
//         {
//         case 'w':
//             if (this->__y - this->__speed * ET <= 0)
//                 break;
//             this->__y -= this->__speed * ET;
//             break;
//         case 's':
//             if (this->__y + this->__speed * ET > ScreenHeight - this->__height)
//                 break;
//             this->__y += this->__speed * ET;
//             break;
//         case 'a':
//             if (this->__x - this->__speed * ET <= 0)
//                 break;
//             this->__x -= this->__speed * ET;
//             break;
//         case 'd':
//             if (this->__x + this->__speed * ET > ScreenWidth - this->__width)
//                 break;
//             this->__x += this->__speed * ET;
//             break;
//         }
//     }

//     void initVariables()
//     {
//         this->__width = 8;
//         this->__height = 5;
//         this->__speed = 16;
//         design += L"   /\\   ";
//         design += L"^ /  \\ ^";
//         design += L"|| /\\ ||";
//         design += L"| _||_ |";
//         design += L"|/    \\|";
//     }
// };

// class Enemy : public Entity
// {
// private:
//     int __speed;
//     float __x_vel, __y_vel;

// public:
//     float reload = 1;
//     Enemy(float x = 46, float y = -5, float x_vel = 0, float y_vel = 16)
//         : Entity(x, y), __x_vel(x_vel), __y_vel(y_vel) { this->initVariables(); }

//     void initVariables()
//     {
//         this->__width = 8;
//         this->__height = 5;
//         design += L"|\\    /|";
//         design += L"| -||- |";
//         design += L"|| \\/ ||";
//         design += L"o \\  / o";
//         design += L"   \\/   ";
//     }

//     void update(wchar_t *screen, float ET)
//     {
//         if (this->__y < ScreenHeight)
//         {
//             this->reload -= ET;
//             this->__x += this->__x_vel * ET;
//             this->__y += this->__y_vel * ET;
//             this->render(screen);
//         }
//     }
// };

// class Bullet : public Entity
// {
// public:
//     float __x_vel, __y_vel;

// public:
//     Bullet(float x, float y, float x_vel, float y_vel)
//         : Entity(x, y), __x_vel(x_vel), __y_vel(y_vel) { this->initVariables(); }

//     void initVariables()
//     {
//         this->__width = 1;
//         this->__height = 2;
//         this->design += L"^";
//         this->design += L"|";
//     }

//     void update(wchar_t *screen, float ET)
//     {
//         if (this->__y > 0)
//         {
//             this->__x += __x_vel * ET;
//             this->__y += __y_vel * ET;
//             this->render(screen);
//         }
//     }
// };

// int main()
// {
//     srand(time(0));
//     wchar_t *screen = new wchar_t[ScreenWidth * ScreenHeight];
//     HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
//     SetConsoleTitleA("Ship Game");
//     SetConsoleActiveScreenBuffer(hConsole);
//     DWORD BytesWritten = 0;

//     auto tp1 = chrono::system_clock::now();
//     auto tp2 = chrono::system_clock::now();
//     Player *player = new Player(46, 21);
//     list<shared_ptr<Bullet>> player_bull;
//     list<shared_ptr<Enemy>> enemy_list;
//     list<shared_ptr<Bullet>> enemy_bullet;

//     list<shared_ptr<Bullet>>::iterator pbullet;
//     list<shared_ptr<Bullet>>::iterator ebullet;
//     list<shared_ptr<Enemy>>::iterator enemy;

//     float spawn_enemy = 1.5;
//     while (true)
//     {
//         tp2 = chrono::system_clock::now();
//         chrono::duration<float> elapseTime = tp2 - tp1;
//         tp1 = tp2;
//         float ElapseTime = elapseTime.count();

//         for (int i = 0; i < ScreenHeight; i++)
//             for (int j = 0; j < ScreenWidth; j++)
//                 screen[i * ScreenWidth + j] = L' ';

//         if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
//             player->move('a', ElapseTime);
//         else if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
//             player->move('d', ElapseTime);
//         if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
//             player->move('s', ElapseTime);
//         else if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
//             player->move('w', ElapseTime);
//         if (GetAsyncKeyState((unsigned short)'F') & 0x8000)
//         {
//             if (player->reload <= 0)
//             {
//                 player_bull.push_back(make_shared<Bullet>(player->getx(), player->gety(), 0, -20));
//                 player_bull.push_back(make_shared<Bullet>(player->getx() + player->getw(), player->gety(), 0, -20));
//                 player->reload = 0.2;
//             }
//         }
//         player->render(screen);
//         pbullet = player_bull.begin();
//         while (pbullet != player_bull.end())
//         {
//             int hit = 0;
//             (*pbullet)->update(screen, ElapseTime);
//             enemy = enemy_list.begin();
//             while (enemy != enemy_list.end())
//             {
//                 if ((*enemy)->collide_point((*pbullet)->getx(), (*pbullet)->gety()))
//                 {
//                     enemy_list.erase(enemy);
//                     hit = 1;
//                     break;
//                 }
//                 enemy++;
//             }
//             if (hit || (*pbullet)->gety() <= 0)
//                 pbullet = player_bull.erase(pbullet);
//             else
//                 pbullet++;
//         }

//         ebullet = enemy_bullet.begin();
//         while (ebullet != enemy_bullet.end())
//         {
//             (*ebullet)->update(screen, ElapseTime);
//             if (player->collide_point((*ebullet)->getx(), (*ebullet)->gety()) || (*ebullet)->gety() <= 0)
//                 ebullet = enemy_bullet.erase(ebullet);
//             else
//                 ebullet++;
//         }

//         enemy = enemy_list.begin();
//         while (enemy != enemy_list.end())
//         {
//             (*enemy)->update(screen, ElapseTime);
//             if ((*enemy)->gety() > ScreenHeight - (*enemy)->getw())
//             {
//                 enemy = enemy_list.erase(enemy);
//                 continue;
//             }
//             if ((*enemy)->reload <= 0)
//             {
//                 enemy_bullet.push_back(make_shared<Bullet>((*enemy)->getx(), (*enemy)->gety() + (*enemy)->geth(), 0, 40));
//                 enemy_bullet.push_back(make_shared<Bullet>((*enemy)->getx() + (*enemy)->getw(), (*enemy)->gety() + (*enemy)->geth(), 0, 40));
//                 (*enemy)->reload = 1;
//             }
//             enemy++;
//         }
//         spawn_enemy -= ElapseTime;
//         if (spawn_enemy <= 0)
//         {
//             float x = rand() % (ScreenWidth - 8);
//             enemy_list.emplace_back(make_shared<Enemy>(x));
//             spawn_enemy = 0.5 + (rand() % 3);
//         }
//         player->reload -= ElapseTime;
//         WriteConsoleOutputCharacterW(hConsole, screen, (ScreenWidth * ScreenHeight), {0, 0}, &BytesWritten);
//     }

//     return 0;
// }
