#pragma once
#include"creatures.hpp"
#include<vector>

//植物クラス
class Plant : public Creatures {
private:
    double breed = 0.0;
public:
    //コンストラクタ
    Plant() {
        one_year = 2;
        lifespan = 5.0;
    }
    //生命活動
    void lifeActivity(const double mi_spf, bool& is_die, bool& is_breed);
    bool isCover(const Vec2& sub_coord);
    bool isBreed();
    void born(std::vector<Plant>& plant, const Vec2& sub_coord, int& seeds_count)const;
};


//植物クラス実装
void Plant::lifeActivity(const double mi_spf, bool& is_die, bool& is_breed) {
    setSpf(mi_spf);
    getOld();
    breed += getSpf();
    is_breed = isBreed();
    is_die = (getAge() > one_year * lifespan);
    Vec2 coord = getCoord();
    is_die = (coord.x<0 || coord.x>window_width || coord.y<0 || coord.y>window_height);
    if (!is_die) Draw::circleDraw(coord, plantE);
}
bool Plant::isCover(const Vec2& sub_coord)  {
    const Vec2 coord = getCoord();
    return (std::sqrt(std::pow(coord.x - sub_coord.x, 2) + std::pow(coord.y - sub_coord.y, 2)) < 10);
}
bool Plant::isBreed() {
    if (breed > one_year && getAge() > one_year / 2) {
        breed = 0.0;
        return true;
    }
    return false;
}
void Plant::born(std::vector<Plant>& plant, const Vec2& sub_coord, int& seeds_count)const {
    if (isInTheWindow(Vec2(sub_coord))) {
        plant.emplace_back();
        plant[plant.size() - 1].setCoord(sub_coord);
        seeds_count++;
    }
}