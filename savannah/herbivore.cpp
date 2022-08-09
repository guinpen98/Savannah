#include "herbivore.hpp"

namespace Savannah {
    //草食動物実装
    void Herbivore::behavior(std::vector<Herbivore>& herbivore, std::vector<Plant>& plant, const size_t hs) {
        if (isBreedingSeason()) {
            herbivore_state = HerbivoreStateE::herbivoreBreedE;
            herbivoreBreed(herbivore, hs);
        }
        else if (satiety < max_satiety * 3.0 / 4.0) {
            //草食物にの視界のなかにあって、最も近い植物の添え字
            size_t s = (std::numeric_limits<size_t>::max)();
            bool is_can_eat;
            isCloseToPlants(plant, s, is_can_eat);
            if (s != (std::numeric_limits<size_t>::max)()) {
                herbivore_state = HerbivoreStateE::herbivoreForageE;
                setDistination(plant[s].getCoord());
                if (is_can_eat) eat(plant, s);
            }
            else {
                herbivore_state = HerbivoreStateE::herbivoreWanderE;
                if (isDistination()) setRandomDistination();
            }
        }
        else {
            herbivore_state = HerbivoreStateE::herbivoreWanderE;
            if (isDistination()) setRandomDistination();
        }
        move();
    }
    void Herbivore::isCloseToPlants(const std::vector<Plant>& plant, size_t& s, bool& is_can_eat) {
        double min_distance = 50000.0;
        for (size_t i = 0; i < plant.size(); i++) {
            //最小距離以上の長さの場合は返す
            if (getCoord().distanceSquared(plant[i].getCoord()) >= min_distance) continue;

            min_distance = getCoord().distanceSquared(plant[i].getCoord());
            s = i;
        }
        is_can_eat = (min_distance < 2);
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
            //同じ個体の場合は返す
            if (i == hs) continue;

            if (herbivore[i].herbivore_state != HerbivoreStateE::herbivoreBreedE) continue;
            if (getCoord().distanceSquared(herbivore[i].getCoord()) >= min_distance) continue;
            min_distance = getCoord().distanceSquared(herbivore[i].getCoord());
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
    void Herbivore::born(const Vec2& born_coord, std::vector<Herbivore>& herbivores, const size_t s) {
        if (!isBreedingSeason()) return;
        if (!herbivores[s].isBreedingSeason()) return;
        herbivores.emplace_back(herbivores[0].getRd());
        herbivores.back().setCoord(born_coord);
        satiety -= one_year / 2.0;
        herbivore_state = HerbivoreStateE::herbivoreWanderE;
        breed_count = 0.0;
        herbivores[s].satiety -= one_year / 2.0;
        herbivores[s].herbivore_state = HerbivoreStateE::herbivoreWanderE;
        herbivores[s].breed_count = 0.0;

    }
    int Herbivore::getHerbivoreState() {
        return (int)herbivore_state;
    }
    void Herbivore::setHerbivoreState(enum HerbivoreStateE new_state) {
        herbivore_state = new_state;
    }
    Herbivore::Herbivore(Rand* rd):Animal(rd)
    {
        lifespan = 20.0;
        one_year = 24;
        breed_age = one_year * 2.0;
    }
}