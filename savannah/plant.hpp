#pragma once
#include"creatures.hpp"
#include<vector>

//植物クラス
class Plant : public Creatures {
private:
    double breed = 0.0;
    double lifespan = 5.0;
public:
    //コンストラクタ
    Plant() {
        one_year = 2;
    }

    void lifeActivity(const double mi_spf, bool& is_die, bool& is_breed);
    Vec2 getCoordinate();
    bool isCover(const Vec2& sub_coord) const;
    bool isBreed();
    void born(std::vector<Plant>& plant, const Vec2& sub_coord, int& seeds_count)const;
};


//植物クラス実装
void Plant::lifeActivity(const double mi_spf, bool& is_die, bool& is_breed) {
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
void Plant::born(std::vector<Plant>& plant, const Vec2& sub_coord, int& seeds_count)const {
    if (isInTheWindow(Vec2(sub_coord))) {
        plant.emplace_back();
        plant[plant.size() - 1].coord = Vec2(sub_coord);
        seeds_count++;
    }
}