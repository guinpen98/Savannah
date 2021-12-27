#pragma once
#include"init.hpp"
#include<random>
#include <cmath>
#include<vector>




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
    //画面内にいるかどうかの判定
    bool isInTheWindow(const Vec2& sub_coord)const;
};

//生物クラス実装
void Creatures::setSpf(const double mi_spf) {
    spf = mi_spf / 1000.0;
}
bool Creatures::isInTheWindow(const Vec2& sub_coord)const{
    return (sub_coord.x > 0&&sub_coord.x<window_width&&sub_coord.y>0&&sub_coord.y<window_height);
}


//植物クラス
class Plant : public Creatures {
private:
    double breed = 0.0;
    double lifespan = 5.0;
public:
    //コンストラクタ
    Plant() {
        one_year = 24;
    }

    void lifeActivity(const double mi_spf, bool& is_die,bool& is_breed);
    Vec2 getCoordinate();
    bool isCover(const Vec2& sub_coord) const;
    bool isBreed();
    void born(std::vector<Plant>& plant, const Vec2& sub_coord, int& seeds_count)const;
};
void plantLifeActivity(std::vector<Plant>& plant, const double mi_spf);

//植物クラス実装
void Plant::lifeActivity(const double mi_spf, bool& is_die,bool& is_breed) {
    setSpf(mi_spf);
    age += spf;
    breed += spf;
    is_breed = isBreed();
    is_die = (age > one_year * lifespan);
    is_die = (coord.x<0 || coord.x>window_width || coord.y<0 || coord.y>window_height);
    if (!is_die) Draw::circleDraw(coord, plantE);
}
Vec2 Plant::getCoordinate() {
    return coord;
}
bool Plant::isCover(const Vec2& sub_coord) const {
    return (std::sqrt(std::pow(coord.x - sub_coord.x, 2) + std::pow(coord.y - sub_coord.y, 2)) < 10);
}
bool Plant::isBreed() {
    if (breed > one_year && age > one_year / 2) {
        breed = 0.0;
        return true;
    }
    return false;
}
void Plant::born(std::vector<Plant>& plant,const Vec2& sub_coord,int& seeds_count)const {
    if (isInTheWindow(Vec2(sub_coord))) {
        plant.emplace_back();
        plant[plant.size() - 1].coord = Vec2(sub_coord);
        seeds_count++;
    }
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
            const unsigned int plant_size = plant.size();
            int seeds_count = 0;
            plant[i].born(plant,Vec2(plant_c.x - 10, plant_c.y),seeds_count);
            plant[i].born(plant,Vec2(plant_c.x + 10, plant_c.y),seeds_count);
            plant[i].born(plant,Vec2(plant_c.x, plant_c.y - 10),seeds_count);
            plant[i].born(plant,Vec2(plant_c.x, plant_c.y + 10),seeds_count);
            //植物が他の植物に被っている場合死ぬ


            for (int k = 0; k < seeds_count; k++) {
                for (size_t j = 0; j < plant_size; j++) {
                    //植物の座標
                    const Vec2 plant_c = plant[j].getCoordinate();
                    if (plant[plant_size + k].isCover(plant_c)) {
                        plant.erase(plant.begin() + plant_size + k);
                        seeds_count--;
                        k--;
                        break;
                    }
                }
            }
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

//動物クラス
class Animal : public Creatures{
private:
    double distance=100.0;
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
    bool isDistination() const;
    //目的地の設定
    void setDistination();
    //目的地との距離
    void calculateDistance(const Vec2& distination_coord);
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
void Animal::move() {
    if (distance == 0.0) {
        setDistination();
        calculateDistance(distination_coord);
    }
    const  Vec2 dCoord = Vec2((distination_coord.x - coord.x) / distance,(distination_coord.y - coord.y) / distance);
    coord = Vec2(coord.x+dCoord.x,coord.y+dCoord.y);
    Draw::circleDraw(coord, herbivoreE);
}
bool Animal::isDistination() const {
    return ((coord.x - distination_coord.x) < 1.0 && (coord.y - distination_coord.y) < 1.0);
}
void Animal::calculateDistance( const Vec2& distination_coord) {
    distance=std::sqrt(std::pow(coord.x - distination_coord.x, 2) + std::pow(coord.y - distination_coord.y, 2));
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



//草食動物実装
void Herbivore::lifeActivity(const double mi_spf,bool& is_die) {
    setSpf(mi_spf);
    age += spf;
    is_die = (age > one_year * lifespan);
    if (isDistination()) setDistination();
    calculateDistance(distination_coord);
}
void Herbivore::behavior() {
    if (isDistination()) setDistination();
    calculateDistance(distination_coord);
    move();
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