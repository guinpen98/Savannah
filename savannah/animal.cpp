#include "animal.hpp"

namespace Savannah {
    //動物クラス実装
    void Animal::move() {
        if (distance == 0.0) {
            setRandomDistination();
        }
        calculateDistinationDistance();
        const Vec2 temp_coord = getCoord();
        const double temp_spf = getSpf();
        const  Vec2 dCoord = Vec2((distination_coord.x - temp_coord.x) / distance * temp_spf * 60, (distination_coord.y - temp_coord.y) / distance * temp_spf * 60);
        setIsLeftDirection(dCoord.x);
        setCoord(temp_coord + dCoord);
    }
    bool Animal::isDistination() {
        const Vec2 temp_coord = getCoord();
        return ((temp_coord.x - distination_coord.x) < 1.0 && (temp_coord.y - distination_coord.y) < 1.0);
    }
    void Animal::calculateDistinationDistance() {
        distance = std::sqrt(getCoord().distanceSquared(distination_coord));
    }
    void Animal::setRandomDistination() {
        constexpr int MIN = 0;
        constexpr int wMAX = field_width;
        constexpr int hMAX = field_height;
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<int> wDistr(MIN, wMAX);
        std::uniform_int_distribution<int> hDistr(MIN, hMAX);
        distination_coord.x = wDistr(eng);
        distination_coord.y = hDistr(eng);
        calculateDistinationDistance();
    }
    void Animal::setDistination(const Vec2 new_coord) {
        if (isInTheWindow(new_coord)) distination_coord = new_coord;
        else setRandomDistination();
        calculateDistinationDistance();
    }
    void Animal::setIsLeftDirection(const double dx) {
        if (dx == 0) return;
        is_left_direction = (dx < 0);
    }
    bool Animal::getIsLeftDirection()const {
        return is_left_direction;
    }
    void Animal::lifeActivity(const double mi_spf, bool& is_die) {
        setSpf(mi_spf);
        setOld();
        passBreedPeriod();
        satiety -= getSpf();
        is_die = (getAge() > one_year * lifespan || satiety < 0);
    }
    bool Animal::isBreedingSeason() {
        return (satiety > max_satiety * 3.0 / 4.0 && getAge() > breed_age && breed_count > breed_period);
    }
    void Animal::passBreedPeriod() {
        breed_count += getSpf();
    }
}