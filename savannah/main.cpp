#include"init.hpp"
#include<random>

struct vec2
{
    int x=0, y=0;
};
class Draw {
private:
    int x = 256;
    int x2 = 150;
    int y = 150;
    int y2 = 256;
public:
    void circleDraw(const int moveX,const int moveY, const int moveX2, const int moveY2) {
        if (x < 0) x = 0;
        else if (x > windowWidth) x = windowWidth;
        if (y < 0) y = 0;
        else if (y > windowHeight) y = windowHeight;
        if (x2 < 0) x2 = 0;
        else if (x2 > windowWidth) x2 = windowWidth;
        if (y2 < 0) y2 = 0;
        else if (y2 > windowHeight) y2 = windowHeight;
        DrawCircle(x+moveX, y+moveY, 10, GetColor(0, 0, 255), TRUE);
        DrawCircle(x2+moveX2,y2+moveY2, 10, GetColor(255, 0, 0), TRUE);
    }
};

void Main() {
    Draw draw;
    constexpr int MIN = -20;
    constexpr int MAX = 20;
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distr(MIN, MAX);
    while (System::Update()) {
        draw.circleDraw(distr(eng), distr(eng), distr(eng), distr(eng));
        

    }

}