#pragma once
#include"creatures.hpp"
#include<random>

//動物クラス
class Animal : public Creatures {
private:
    double distance = 100.0;
protected:
    Vec2 distination_coord = Vec2(window_width / 2.0, window_height / 2.0);

public:
    //新しいX座標を設定
    int moveX();
    //新しいY座標を設定
    int moveY();
    //新しい座標の設定
    void move();
    //目的地にいるかどうかの判定
    bool isDistination();
    //目的地の設定
    void setDistination();
    //目的地との距離
    void calculateDistance(const Vec2& distination_coord);
};

//動物クラス実装
void Animal::move() {
    if (distance == 0.0) {
        setDistination();
        calculateDistance(distination_coord);
    }
    Vec2 const coord = getCoord();
    const  Vec2 dCoord = Vec2((distination_coord.x - coord.x) / distance, (distination_coord.y - coord.y) / distance);
    setCoord (Vec2(coord.x + dCoord.x, coord.y + dCoord.y));
    Draw::circleDraw(coord, herbivoreE);
}
bool Animal::isDistination() {
    const Vec2 coord = getCoord();
    return ((coord.x - distination_coord.x) < 1.0 && (coord.y - distination_coord.y) < 1.0);
}
void Animal::calculateDistance(const Vec2& distination_coord) {
    const Vec2 coord = getCoord();
    distance = std::sqrt(std::pow(coord.x - distination_coord.x, 2) + std::pow(coord.y - distination_coord.y, 2));
}
void Animal::setDistination() {
    constexpr int MIN = 0;
    constexpr int wMAX = window_width;
    constexpr int hMAX = window_height;
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> wDistr(MIN, wMAX);
    std::uniform_int_distribution<int> hDistr(MIN, hMAX);
    distination_coord.x = wDistr(eng);
    distination_coord.y = hDistr(eng);
}
