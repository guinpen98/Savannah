#pragma once
#include"animal.hpp"
#include <limits>

enum HerbivoreStateE :int {
	herbivoreWanderE
	, herbivoreForageE
	, herbivoreBreedE
	, herbivoreDieE
};

//草食動物クラス
class Herbivore : public Animal {
public:
    HerbivoreStateE herbivore_state = herbivoreWanderE;
    Herbivore() {
        lifespan = 20.0;
        one_year = 24;
    }
    //行動
    void behavior(std::vector<Herbivore>& herbivore,std::vector<Plant>& plant,const size_t i);
    //距離を計測
    double distance(const Vec2& plant_coord)const;

    //食事
    void eat(std::vector<Plant>& plant, const int s);

    //草食動物の近くにある植物を探す
    void isCloseToPlants(const std::vector<Plant>& plant, int& s, bool& is_can_eat);
    //繁殖
    void herbivoreBreed(std::vector<Herbivore>& herbivore,const size_t hs);
    //子供が生まれる
    void born(const Vec2& born_coord, std::vector<Herbivore>& herbivore,const int s);
    //ステートの値を渡す
    int getHerbivoreState();
    //ステートの変更
    void setHerbivoreState(enum HerbivoreStateE new_state);
};

//草食動物実装
void Herbivore::behavior(std::vector<Herbivore>& herbivore,std::vector<Plant>& plant,const size_t hs) {
    if (isBreedingSeason()) {
        herbivore_state = herbivoreBreedE;
        herbivoreBreed(herbivore, hs);
        if (isDistination()) setRandomDistination();
    }
    else if(satiety< max_satiety * 3.0 / 4.0){
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
    else {
        herbivore_state = herbivoreWanderE;
        if (isDistination()) setRandomDistination();
    }
    move();
}
void Herbivore::isCloseToPlants(const std::vector<Plant>& plant,int& s,bool& is_can_eat) {
    double min_distance = 50000.0;
    for (size_t i = 0; i < plant.size(); i++) {
        //最小距離以上の長さの場合は返す
        if (distance(plant[i].getCoord()) >= min_distance) continue;
        
        min_distance = distance(plant[i].getCoord());
        s = i;
    }
    is_can_eat = (min_distance < 2);
}
double Herbivore::distance(const Vec2& plant_coord) const{
    return getCoord().distance(plant_coord);
}
void Herbivore::eat( std::vector<Plant>& plant, const int s) {
    plant.erase(plant.begin() + s);
    satiety += one_year / 2.0;
    if (satiety > max_satiety) satiety = max_satiety;
}
void Herbivore::herbivoreBreed(std::vector<Herbivore>& herbivore, const size_t hs) {
    double min_distance = (std::numeric_limits<double>::max)();
    int s = -1;
    for (size_t i = 0; i < herbivore.size(); i++) {
        //同じ個体の場合は返す
        if (i == hs) continue;

        if (herbivore[i].herbivore_state != herbivoreBreedE) continue;
        if (distance(herbivore[i].getCoord()) >= min_distance) continue;
        min_distance = distance(herbivore[i].getCoord());
        s = i;
    }
    if (s == -1) return;
    if (min_distance < 4) {
        born(getCoord(), herbivore, s);
    }
    else setDistination(herbivore[s].getCoord());
}
void Herbivore::born(const Vec2& born_coord, std::vector<Herbivore>& herbivore,const int s) {
    herbivore.emplace_back();
    herbivore.back().setCoord(born_coord);
    satiety -= one_year / 2.0;
    herbivore_state = herbivoreWanderE;
    breed_period = 0.0;
    herbivore[s].satiety -= one_year / 2.0;
    herbivore[s].herbivore_state = herbivoreWanderE;
    herbivore[s].breed_period = 0.0;

}
int Herbivore::getHerbivoreState() {
    return herbivore_state;
}
void Herbivore::setHerbivoreState(enum HerbivoreStateE new_state) {
    herbivore_state = new_state;
}