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
        one_year = 24;
        satiety = 5;
    }
    //行動
    void behavior();
};

//草食動物実装
void Herbivore::behavior() {
    if (isDistination()) setDistination();
    calculateDistance(distination_coord);
    move();
}