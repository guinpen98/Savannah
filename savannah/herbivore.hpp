#pragma once
#include"animal.hpp"

enum HerbivoreState :int {
	herbivoreWanderE
	, herbivoreForageE
	, herbivoreBreedE
};

//草食動物クラス
class Herbivore : public Animal {
public:
    Herbivore() {
        lifespan = 5.0;
        one_year = 1;
    }
    //生命活動を管理
    void lifeActivity(const double mi_spf, bool& is_die);
    //行動
    void behavior();
};

//草食動物実装
void Herbivore::lifeActivity(const double mi_spf, bool& is_die) {
    setSpf(mi_spf);
    getOld();
    is_die = (getAge() > one_year * lifespan);
    if (isDistination()) setDistination();
    calculateDistance(distination_coord);
}
void Herbivore::behavior() {
    if (isDistination()) setDistination();
    calculateDistance(distination_coord);
    move();
}