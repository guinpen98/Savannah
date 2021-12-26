#pragma once
#include"init.hpp"
#include<random>
#include <cmath>

//生物クラス
class Creatures {
protected:
    double spf = 0.0;
    double age = 0.0;
    int one_year = 24;
public:
    //計測した1フレームあたりの秒数を設定する
    void setSpf(const double mi_spf);
};
//生物クラス実装
void Creatures::setSpf(const double mi_spf) {
    spf = mi_spf / 1000.0;
}


//植物クラス
class Plant : public Creatures {
private:
    double x = window_width / 2.0;
    double y = window_height / 2.0;
    double age = 0;
    double breed = 0.0;
    double lifespan = 5.0;
public:
    void lifeActivity(const double mi_spf, bool& is_die,bool& is_breed);
    void born(const double x, const double y);
    bool isBreed();
};

//植物クラス実装
void Plant::lifeActivity(const double mi_spf, bool& is_die,bool& is_breed) {
    setSpf(mi_spf);
    age += spf;
    breed += spf;
    is_breed = isBreed();
    is_die = (age > one_year * lifespan);
    if (!is_die) Draw::circleDraw(int(x), int(y), plantE);
}
void Plant::born(const double born_x, const double born_y) {
    x = born_x;
    y = born_y;
}
bool Plant::isBreed() {
    if (breed > one_year && age > one_year / 2) {
        breed = 0.0;
        return true;
    }
    else return false;
}

//動物クラス
class Animal : public Creatures{
private:
    double distance=100.0;
protected:
    double x = window_width/2.0;
    double y = window_height/2.0;
    double distination_x = window_width / 2.0;
    double distination_y = window_height / 2.0;
public:
    //新しいX座標を設定
    int moveX();
    //新しいY座標を設定
    int moveY();
    //目的地にいるかどうかの判定
    bool isDistination();
    //目的地の設定
    void setDistination();
    //目的地との距離
    void calculateDistance(const double x, const double y, const double ds_x, const double ds_y);
};


//草食動物クラス
class Herbivore : public Animal {
private:
    double lifespan=20.0;
public:
    //生命活動を管理
    void lifeActivity(const double mi_spf, bool& is_die);
    //行動
    void behavior();
};


//動物クラス実装
int Animal::moveX() {
    if (distance == 0.0) {
        setDistination();
        calculateDistance(x, y, distination_x, distination_y);
    }
    double dx = (distination_x - x) / distance;
    x += dx;
    return int(x);
}
int Animal::moveY() {
    if (distance == 0.0) {
        setDistination();
        calculateDistance(x, y, distination_x, distination_y);
    }
    double dy = (distination_y - y) / distance;
    y += dy;
    return int(y);
}
bool Animal::isDistination() {
    if ((x - distination_x) < 1 && (y - distination_y) < 1) return true;
    else return false;
}
void Animal::calculateDistance(const double x, const double y, const double ds_x, const double ds_y) {
    distance=sqrt(pow(x - ds_x, 2) + pow(y - ds_y, 2));
}
void Animal::setDistination() {
    constexpr int MIN = 0;
    constexpr int wMAX = window_width;
    constexpr int hMAX = window_height;
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> wDistr(MIN, wMAX);
    std::uniform_int_distribution<int> hDistr(MIN, hMAX);
    distination_x = wDistr(eng);
    distination_y = hDistr(eng);
}



//草食動物実装
void Herbivore::lifeActivity(const double mi_spf,bool& is_die) {
    setSpf(mi_spf);
    age += spf;
    is_die = (age > one_year * lifespan);
    if (isDistination()) setDistination();
    calculateDistance(x,y,distination_x,distination_y);
}
void Herbivore::behavior() {
    if (isDistination()) setDistination();
    calculateDistance(x, y, distination_x, distination_y);
    Draw::circleDraw(moveX(), moveY(), herbivoreE);
}