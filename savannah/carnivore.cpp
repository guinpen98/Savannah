#include "carnivore.h"

namespace Savannah {
    Carnivore::Carnivore(Rand* rd, Time* time):Animal(rd, time)
    {
        lifespan = 20.0;
        one_year = 24;
        breed_period = one_year;
        breed_age = 2.0 * one_year;
    }
    //肉食動物実装
    void Carnivore::behavior(std::vector<Carnivore>& carnivore, std::vector<Herbivore>& herbivore, const size_t hs) {
        if (isBreedingSeason()) {
            carnivore_state = CarnivoreStateE::carnivoreBreedE;
            carnivoreBreed(carnivore, hs);
        }
        else if (satiety < max_satiety * 3.0 / 4.0) {
            //肉食物にの視界のなかにあって、最も近い草食動物の添え字
            size_t s = (std::numeric_limits<size_t>::max)();
            bool is_can_eat;
            isCloseToHerbivores(herbivore, s, is_can_eat);
            if (s != (std::numeric_limits<size_t>::max)()) {
                carnivore_state = CarnivoreStateE::carnivoreForageE;
                setDistination(herbivore[s].getCoord());
                if (is_can_eat) eat(herbivore, s);
            }
            else {
                carnivore_state = CarnivoreStateE::carnivoreWanderE;
                if (isDistination()) setRandomDistination();
            }
        }
        else {
            carnivore_state = CarnivoreStateE::carnivoreWanderE;
            if (isDistination()) setRandomDistination();
        }
        move();
    }
    void Carnivore::isCloseToHerbivores(const std::vector<Herbivore>& herbivore, size_t& s, bool& is_can_eat) {
        double min_distance = 50000.0;
        for (size_t i = 0; i < herbivore.size(); i++) {
            //最小距離以上の長さの場合は返す
            if (getCoord().distanceSquared(herbivore[i].getCoord()) >= min_distance) continue;

            min_distance = getCoord().distanceSquared(herbivore[i].getCoord());
            s = i;
        }
        is_can_eat = (min_distance < 50.0);
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

            if (carnivore[i].carnivore_state != CarnivoreStateE::carnivoreBreedE) continue;
            if (getCoord().distanceSquared(carnivore[i].getCoord()) >= min_distance) continue;
            min_distance = getCoord().distanceSquared(carnivore[i].getCoord());
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
    void Carnivore::born(const Vec2& born_coord, std::vector<Carnivore>& carnivores, const size_t s) {
        carnivores.emplace_back(carnivores[0].getRd(),carnivores[0].getTime());
        carnivores.back().setCoord(born_coord);
        satiety -= one_year / 4.0;
        carnivore_state = CarnivoreStateE::carnivoreWanderE;
        breed_count = 0.0;
        carnivores[s].satiety -= one_year / 4.0;
        carnivores[s].carnivore_state = CarnivoreStateE::carnivoreWanderE;
        carnivores[s].breed_count = 0.0;

    }
    int Carnivore::getCarnivoreState() {
        return (int)carnivore_state;
    }
    void Carnivore::setCarnivoreState(enum CarnivoreStateE new_state) {
        carnivore_state = new_state;
    }
}