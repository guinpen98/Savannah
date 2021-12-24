#include"init.hpp"
#include<random>
#include<array>
#include<vector>
#include <chrono>
#include <cmath>

struct vec2
{
    int x=0, y=0;
};

class Draw {
public:
    void circleDraw(const int x, const int y,const int number) {
        DrawCircle(x, y, 5, GetColor(255, 255, 255), TRUE);
    }
};
class Animal {
private:
    double x = 256;
    double y = 256;
    double distinationX = 256;
    double distinationY = 256;
protected:
    double update = 0;
public:
    void move(const int number) {
        double distance = calculateDistance(x, y, distinationX, distinationY);
        double dx = (distinationX-x) / distance;
        double dy = (distinationY-y) / distance;
        x += dx , y += dy;
        Draw draw;
        draw.circleDraw(x, y,number);
    } 
    bool isDistination() {
        if ((x -distinationX)<1 && (y-distinationY)<1) return true;
        else return false;
    }
    double calculateDistance(const int x,const int y,const int dsX,const int dsY) {
        return sqrt(pow(x - dsX, 2) + pow(y - dsY, 2));
    }

    void setDistination() {
        constexpr int MIN = -100;
        constexpr int MAX = 100;
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<int> distr(MIN, MAX);
        do {
            distinationX = x + distr(eng);
        }while (distinationX<0 || distinationX>windowWidth);
        do {
            distinationY = y + distr(eng);
        } while (distinationY<0 || distinationY>windowHeight);
    }

    void Update(const double up) {
        update = up;
    }
};
class Herbivore : public Animal {
public:
    void behavior(){
        if (isDistination()) setDistination();
        move(0);
    }
};


void Main() {
    //Draw draw[3]
    std::vector<Herbivore> herbivore;

    std::chrono::system_clock::time_point  start, end;

    std::random_device rd;
    std::mt19937 eng(rd());
    //確率
    std::bernoulli_distribution uid(0.01);
    while (System::Update()) {
        end = std::chrono::system_clock::now();

        if (uid(eng)) herbivore.emplace_back();
        for (auto& h : herbivore) {
            h.Update(std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
            h.behavior();
        }

        start = std::chrono::system_clock::now();
    }

}