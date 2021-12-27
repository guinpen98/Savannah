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
        one_year = 24;
        lifespan = 5.0;
    }
    //生命活動
    void lifeActivity(const double mi_spf, bool& is_die, bool& is_breed);
    //他の植物と被っているかの判定
    bool isCover(const Vec2& sub_coord);
    //繁殖判定
    bool isBreed();
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
    if (!is_die) Draw::oldDraw(coord, plantE);
}
bool Plant::isCover(const Vec2& sub_coord)  {
    return (getCoord().distance(sub_coord) < 100.0);
}
bool Plant::isBreed() {
    if (breed > one_year && getAge() > one_year / 2) {
        breed = 0.0;
        return true;
    }
    return false;
}