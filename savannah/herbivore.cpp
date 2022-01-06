#include "herbivore.hpp"

//ëêêHìÆï®é¿ëï
void Herbivore::behavior(std::vector<Herbivore>& herbivore, std::vector<Plant>& plant, const size_t hs) {
    if (isBreedingSeason()) {
        herbivore_state = herbivoreBreedE;
        herbivoreBreed(herbivore, hs);
    }
    else if (satiety < max_satiety * 3.0 / 4.0) {
        //ëêêHï®Ç…ÇÃéãäEÇÃÇ»Ç©Ç…Ç†Ç¡ÇƒÅAç≈Ç‡ãﬂÇ¢êAï®ÇÃìYÇ¶éö
        size_t s = (std::numeric_limits<size_t>::max)();
        bool is_can_eat;
        isCloseToPlants(plant, s, is_can_eat);
        if (s != (std::numeric_limits<size_t>::max)()) {
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
void Herbivore::isCloseToPlants(const std::vector<Plant>& plant, size_t& s, bool& is_can_eat) {
    double min_distance = 50000.0;
    for (size_t i = 0; i < plant.size(); i++) {
        //ç≈è¨ãóó£à»è„ÇÃí∑Ç≥ÇÃèÍçáÇÕï‘Ç∑
        if (distance(plant[i].getCoord()) >= min_distance) continue;

        min_distance = distance(plant[i].getCoord());
        s = i;
    }
    is_can_eat = (min_distance < 2);
}
double Herbivore::distance(const Vec2& plant_coord) const {
    return getCoord().distance(plant_coord);
}
void Herbivore::eat(std::vector<Plant>& plant, const size_t s) {
    plant.erase(plant.begin() + s);
    satiety += one_year / 2.0;
    if (satiety > max_satiety) satiety = max_satiety;
}
void Herbivore::herbivoreBreed(std::vector<Herbivore>& herbivore, const size_t hs) {
    double min_distance = (std::numeric_limits<double>::max)();
    size_t s = (std::numeric_limits<size_t>::max)();
    for (size_t i = 0; i < herbivore.size(); i++) {
        //ìØÇ∂å¬ëÃÇÃèÍçáÇÕï‘Ç∑
        if (i == hs) continue;

        if (herbivore[i].herbivore_state != herbivoreBreedE) continue;
        if (distance(herbivore[i].getCoord()) >= min_distance) continue;
        min_distance = distance(herbivore[i].getCoord());
        s = i;
    }
    if (s == (std::numeric_limits<size_t>::max)()) {
        if (isDistination()) setRandomDistination();
        return;
    }
    if (min_distance < 4) {
        born(getCoord(), herbivore, s);
    }
    else setDistination(herbivore[s].getCoord());
}
void Herbivore::born(const Vec2& born_coord, std::vector<Herbivore>& herbivore, const size_t s) {
    if (!isBreedingSeason()) return;
    if (!herbivore[s].isBreedingSeason()) return;
    herbivore.emplace_back();
    herbivore.back().setCoord(born_coord);
    satiety -= one_year / 2.0;
    herbivore_state = herbivoreWanderE;
    breed_count = 0.0;
    herbivore[s].satiety -= one_year / 2.0;
    herbivore[s].herbivore_state = herbivoreWanderE;
    herbivore[s].breed_count = 0.0;

}
int Herbivore::getHerbivoreState() {
    return herbivore_state;
}
void Herbivore::setHerbivoreState(enum HerbivoreStateE new_state) {
    herbivore_state = new_state;
}