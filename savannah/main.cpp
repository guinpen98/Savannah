#include"init.hpp"
#include<random>
#include<array>
#include<vector>

struct vec2
{
    int x=0, y=0;
};

class Draw {
public:
    void circleDraw(const int x, const int y) {
        DrawCircle(x, y, 10, GetColor(255, 255, 255), TRUE);
    }
};
class Actor {
private:
    int x = 256;
    int y = 150;
public:
    void move(const int moveX, const int moveY) {
        x += moveX, y += moveY;
        if (x < 0) x = 0;
        else if (x > windowWidth) x = windowWidth;
        if (y < 0) y = 0;
        else if (y > windowHeight) y = windowHeight;
        Draw draw;
        draw.circleDraw(x, y);
    }
};


void Main() {
    //Draw draw[3];
    //std::array<Actor,3> actor;
    std::vector<Actor> actor;

    constexpr int MIN = -20;
    constexpr int MAX = 20;
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distr(MIN, MAX);
    //確率
    std::bernoulli_distribution uid(0.01);
    while (System::Update()) {
        if (uid(eng)) actor.emplace_back();
        for(auto& a:actor) a.move(distr(eng), distr(eng));
        

    }

}