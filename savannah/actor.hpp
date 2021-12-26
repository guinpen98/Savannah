#pragma once
#include"init.hpp"
#include<random>
#include <cmath>
#include<vector>

struct Vec2 {
    double x=0.0, y=0.0;

    //デフォルトコンストラクタ
    Vec2() = default;

    //コンストラクタ
    Vec2(const double ix, const double iy)
        :x(ix), y(iy) {}

};

//生物クラス
class Creatures {
protected:
    //座標
    Vec2 coord = Vec2(window_width / 2.0, window_height / 2.0);

    double spf = 0.0;
    double age = 0.0;
    int one_year = 24;// 24;
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
    double breed = 0.0;
    double lifespan = 5.0;
public:
    //コンストラクタ
    Plant() {
        one_year = 1;
    }

    void lifeActivity(const double mi_spf, bool& is_die,bool& is_breed);
    void born(const Vec2& c);
    Vec2 getCoordinate();
    bool isCover(const Vec2& c) const;
    bool isBreed();
};

//植物クラス実装
void Plant::lifeActivity(const double mi_spf, bool& is_die,bool& is_breed) {
    setSpf(mi_spf);
    age += spf;
    breed += spf;
    is_breed = isBreed();
    is_die = (age > one_year * lifespan);
    is_die = (coord.x<0 || coord.x>window_width || coord.y<0 || coord.y>window_height);
    if (!is_die) Draw::circleDraw(int(coord.x), int(coord.y), plantE);
}
void Plant::born(const Vec2& c) {
    coord = c;
}
Vec2 Plant::getCoordinate() {
    return coord;
}
bool Plant::isCover(const Vec2& c) const {
    return (std::sqrt(std::pow(coord.x - c.x, 2) + std::pow(coord.y - c.y, 2)) < 10);
}
bool Plant::isBreed() {
    if (breed > one_year && age > one_year / 2) {
        breed = 0.0;
        return true;
    }
    return false;
}

//動物クラス
class Animal : public Creatures{
private:
    double distance=100.0;
protected:
    double distination_x = window_width / 2.0;
    double distination_y = window_height / 2.0;
public:
    //新しいX座標を設定
    int moveX();
    //新しいY座標を設定
    int moveY();
    //目的地にいるかどうかの判定
    bool isDistination() const;
    //目的地の設定
    void setDistination();
    //目的地との距離
    void calculateDistance(const double ds_x, const double ds_y);
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
        calculateDistance(distination_x, distination_y);
    }
    const double dx = (distination_x - coord.x) / distance;
    coord.x += dx;
    return int(coord.x);
}
int Animal::moveY() {
    if (distance == 0.0) {
        setDistination();
        calculateDistance( distination_x, distination_y);
    }
    const double dy = (distination_y - coord.y) / distance;
    coord.y += dy;
    return int(coord.y);
}
bool Animal::isDistination() const {
    return ((coord.x - distination_x) < 1 && (coord.y - distination_y) < 1);
}
void Animal::calculateDistance( const double ds_x, const double ds_y) {
    distance=std::sqrt(std::pow(coord.x - ds_x, 2) + std::pow(coord.y - ds_y, 2));
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
    calculateDistance(distination_x,distination_y);
}
void Herbivore::behavior() {
    if (isDistination()) setDistination();
    calculateDistance(distination_x, distination_y);
    Draw::circleDraw(moveX(), moveY(), herbivoreE);
}




void plantLifeActivity(std::vector<Plant>& plant, const double mi_spf) {
    //植物それぞれの生命活動
    for (size_t i = 0; i < plant.size();) {
        bool plant_is_die, plant_is_breed;
        plant[i].lifeActivity(mi_spf, plant_is_die, plant_is_breed);
        //植物の繁殖
        if (plant_is_breed) {
            //植物の座標
            const Vec2 plant_c = plant[i].getCoordinate();
            const int plant_size = plant.size();
            plant.emplace_back();
            plant[plant_size].born(Vec2(plant_c.x - 10, plant_c.y));
            plant.emplace_back();
            plant[plant_size + 1].born(Vec2(plant_c.x + 10, plant_c.y));
            plant.emplace_back();
            plant[plant_size + 2].born(Vec2(plant_c.x, plant_c.y - 10));
            plant.emplace_back();
            plant[plant_size + 3].born(Vec2(plant_c.x, plant_c.y + 10));
        }
        //植物が他の植物に被っている場合死ぬ
        for (size_t j = i + 1; j < plant.size(); j++) {
            //植物の座標
            const Vec2 plant_c = plant[j].getCoordinate();
            if (plant[i].isCover(plant_c)) plant.erase(plant.begin() + j);
        }
        //植物の死
        if (plant_is_die) {
            plant.erase(plant.begin() + i);
        }
        else {
            i++;
        }
    }

}

void herbivoreBehavior(std::vector<Herbivore>& herbivore, const double mi_spf) {
    //草食動物それぞれの行動
    for (size_t i = 0; i < herbivore.size();) {
        auto& h = herbivore[i];
        bool herbivore_is_die;
        h.lifeActivity(mi_spf, herbivore_is_die);
        if (herbivore_is_die) {
            herbivore.erase(herbivore.begin() + i);
        }
        else {
            h.behavior();
            i++;
        }
    }
}