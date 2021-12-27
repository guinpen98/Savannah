#pragma once
#include"animal.hpp"

enum HerbivoreStateE :int {
	herbivoreWanderE
	, herbivoreForageE
	, herbivoreBreedE
};

//草食動物クラス
class Herbivore : public Animal {
public:
    Herbivore() {
        lifespan = 20.0;
        one_year = 24;
    }
    int herbivore_state = herbivoreWanderE;
    //行動
    void behavior(std::vector<Plant>& plant);
    //距離を計測
    double plantDistance(const Vec2& plant_coord)const;

    //食事
    void eat(std::vector<Plant>& plant, const int s);

    //草食動物の近くにある植物を探す
    void isCloseToPlants(const std::vector<Plant>& plant, int& s, bool& is_can_eat);
};

//草食動物実装
void Herbivore::behavior(std::vector<Plant>& plant) {
    if (isBreedingSeason()) {
        herbivore_state = herbivoreBreedE;
        if (isDistination()) setRandomDistination();
    }
    else {
        //草食物にの視界のなかにあって、最も近い植物の添え字
        int s = -1;
        bool is_can_eat;
        isCloseToPlants(plant, s, is_can_eat);
        if (s != -1) {
            herbivore_state = herbivoreForageE;
            setDistination(plant[s].getCoord());
            if (is_can_eat) eat(plant, s);
        }
        else {
            herbivore_state = herbivoreWanderE;
            if (isDistination()) setRandomDistination();
        }
    }
    move();
}
void Herbivore::isCloseToPlants(const std::vector<Plant>& plant,int& s,bool& is_can_eat) {
    double min_distance = 15;
    for (size_t i = 0; i < plant.size();i++) {
        if (plantDistance(plant[i].getCoord()) < min_distance) {
            min_distance = plantDistance(plant[i].getCoord());
            s = i;
        }
    }
    is_can_eat = (min_distance < 2);
}
double Herbivore::plantDistance(const Vec2& plant_coord) const{
    return std::sqrt(std::pow(getCoord().x - plant_coord.x, 2) + std::pow(getCoord().y - plant_coord.y, 2));
}
void Herbivore::eat( std::vector<Plant>& plant, const int s) {
    plant.erase(plant.begin() + s);
    satiety += one_year / 2;
}