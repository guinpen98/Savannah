#ifndef SAVANNAH_CARNIVORE_HPP
#define SAVANNAH_CARNIVORE_HPP
#include"animal.hpp"

enum CarnivoreStateE :int {
	carnivoreWanderE
	, carnivoreForageE
	, carnivoreBreedE
	, carnivoreDieE
};

//肉食動物クラス
class Carnivore : public Animal {
public:
    CarnivoreStateE carnivore_state = carnivoreWanderE;
    Carnivore() {
        lifespan = 20.0;
        one_year = 24;
        breed_period = one_year;
        breed_age = 2.0 * one_year;
    }
    //行動
    void behavior(std::vector<Carnivore>& carnivore, std::vector<Herbivore>& herbivore, const size_t hs);
    //距離を計測
    double distance(const Vec2& herbivore_coord)const;

    //食事
    void eat(std::vector<Herbivore>& herbivore, const size_t s);

    //肉食動物の近くにある草食動物物を探す
    void isCloseToHerbivores(const std::vector<Herbivore>& herbivore, size_t& s, bool& is_can_eat);
    //繁殖
    void carnivoreBreed(std::vector<Carnivore>& carnivore, const size_t hs);
    //子供が生まれる
    void born(const Vec2& born_coord, std::vector<Carnivore>& carnivore, const size_t s);
    //ステートの値を渡す
    int getCarnivoreState();
    //ステートの変更
    void setCarnivoreState(enum CarnivoreStateE new_state);
};

//肉食動物実装
void Carnivore::behavior(std::vector<Carnivore>& carnivore, std::vector<Herbivore>& herbivore, const size_t hs) {
    if (isBreedingSeason()) {
        carnivore_state = carnivoreBreedE;
        carnivoreBreed(carnivore, hs);
    }
    else if (satiety < max_satiety * 3.0 / 4.0) {
        //肉食物にの視界のなかにあって、最も近い草食動物の添え字
        size_t s = (std::numeric_limits<size_t>::max)();
        bool is_can_eat;
        isCloseToHerbivores(herbivore, s, is_can_eat);
        if (s != (std::numeric_limits<size_t>::max)()) {
            carnivore_state = carnivoreForageE;
            setDistination(herbivore[s].getCoord());
            if (is_can_eat) eat(herbivore, s);
        }
        else {
            carnivore_state = carnivoreWanderE;
            if (isDistination()) setRandomDistination();
        }
    }
    else {
        carnivore_state = carnivoreWanderE;
        if (isDistination()) setRandomDistination();
    }
    move();
}
void Carnivore::isCloseToHerbivores(const std::vector<Herbivore>& herbivore, size_t& s, bool& is_can_eat) {
    double min_distance = 50000.0;
    for (size_t i = 0; i < herbivore.size(); i++) {
        //最小距離以上の長さの場合は返す
        if (distance(herbivore[i].getCoord()) >= min_distance) continue;

        min_distance = distance(herbivore[i].getCoord());
        s = i;
    }
    is_can_eat = (min_distance < 50.0);
}
double Carnivore::distance(const Vec2& herbivore_coord) const {
    return getCoord().distance(herbivore_coord);
}
void Carnivore::eat(std::vector<Herbivore>& herbivore, const size_t s) {
    herbivore.erase(herbivore.begin() + s);
    satiety += one_year / 2.0;
    if (satiety > max_satiety) satiety = max_satiety;
}
void Carnivore::carnivoreBreed(std::vector<Carnivore>& carnivore, const size_t hs) {
    double min_distance = (std::numeric_limits<double>::max)();
    size_t s = (std::numeric_limits<size_t>::max)();
    for (size_t i = 0; i < carnivore.size(); i++) {
        //同じ個体の場合は返す
        if (i == hs) continue;

        if (carnivore[i].carnivore_state != carnivoreBreedE) continue;
        if (distance(carnivore[i].getCoord()) >= min_distance) continue;
        min_distance = distance(carnivore[i].getCoord());
        s = i;
    }
    if (s == (std::numeric_limits<size_t>::max)()) {
        if (isDistination()) setRandomDistination();
        return;
    }
    if (min_distance < 4) {
        born(getCoord(), carnivore, s);
    }
    else setDistination(carnivore[s].getCoord());
}
void Carnivore::born(const Vec2& born_coord, std::vector<Carnivore>& carnivore, const size_t s) {
    carnivore.emplace_back();
    carnivore.back().setCoord(born_coord);
    satiety -= one_year / 4.0;
    carnivore_state = carnivoreWanderE;
    breed_count = 0.0;
    carnivore[s].satiety -= one_year / 4.0;
    carnivore[s].carnivore_state = carnivoreWanderE;
    carnivore[s].breed_count = 0.0;

}
int Carnivore::getCarnivoreState() {
    return carnivore_state;
}
void Carnivore::setCarnivoreState(enum CarnivoreStateE new_state) {
    carnivore_state = new_state;
}
#endif // !SAVANNAH_CARNIVORE_HPP