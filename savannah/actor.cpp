#include "actor.h"
#include "rand.h"
#include "creatures.h"

namespace Savannah {
    bool isInTheWindow(const Vec2& sub_coord) {
        return (sub_coord.x > 0 && sub_coord.x < field_width&& sub_coord.y>0 && sub_coord.y < field_height);
    }
    bool plantIsCover(std::vector<Plant>& plant, const Vec2& born_coord) {
        for (size_t j = 0; j < plant.size(); j++) {
            if (plant[j].isCover(born_coord)) return true;
        }
        return false;
    }
    void plantBorn(std::vector<Plant>& plants, const Vec2& born_coord) {
        if (!isInTheWindow(born_coord)) return;
        if (plantIsCover(plants, born_coord)) return;
        plants.emplace_back(plants[0].getRd());
        plants[plants.size() - 1].setCoord(born_coord);

    }
    void randomPlantBorn(std::vector<Plant>& plants, class Rand& rd) {
        Vec2 born_coord = rd.randDist();
        while (!isInTheWindow(born_coord) || plantIsCover(plants, born_coord)) {
            born_coord = rd.randDist();
        }
        if (!isInTheWindow(born_coord)) return;
        if (plantIsCover(plants, born_coord)) return;
        plants.emplace_back(&rd);
        plants[plants.size() - 1].setCoord(born_coord);

    }
    //植物の繁殖
    void plantBreed(std::vector<Plant>& plant, const size_t i) {
        //植物の座標
        const Vec2 plant_c = plant[i].getCoord();
        plantBorn(plant, Vec2(plant_c.x - 10, plant_c.y));
        plantBorn(plant, Vec2(plant_c.x + 10, plant_c.y));
        plantBorn(plant, Vec2(plant_c.x, plant_c.y - 10));
        plantBorn(plant, Vec2(plant_c.x, plant_c.y + 10));
    }

    //植物の行動
    void plantBehavior(std::vector<Plant>& plant, const double mi_spf) {
        //植物それぞれの生命活動
        for (size_t i = 0; i < plant.size();) {
            bool plant_is_die, plant_is_breed;
            plant[i].lifeActivity(mi_spf, plant_is_die, plant_is_breed);
            //植物の繁殖
            if (plant_is_breed) plantBreed(plant, i);
            //植物が寿命で死ぬ
            if (plant_is_die) plant.erase(plant.begin() + i);
            else i++;
        }
    }

    void herbivoreBehavior(std::vector<Herbivore>& herbivore, std::vector<Plant>& plant, const double mi_spf) {
        //草食動物それぞれの行動
        for (size_t i = 0; i < herbivore.size();) {
            auto& h = herbivore[i];
            bool herbivore_is_die;
            h.lifeActivity(mi_spf, herbivore_is_die);
            if (herbivore_is_die) {
                herbivore.erase(herbivore.begin() + i);
            }
            else {
                herbivore[i].behavior(herbivore, plant, i);
                i++;
            }
        }
    }

    void carnivoreBehavior(std::vector<Carnivore>& carnivore, std::vector<Herbivore>& herbivore, const double mi_spf) {
        //肉食動物それぞれの行動
        for (size_t i = 0; i < carnivore.size();) {
            auto& c = carnivore[i];
            bool carnivore_is_die;
            c.lifeActivity(mi_spf, carnivore_is_die);
            if (carnivore_is_die) {
                carnivore.erase(carnivore.begin() + i);
            }
            else {
                carnivore[i].behavior(carnivore, herbivore, i);
                i++;
            }
        }
    }
}