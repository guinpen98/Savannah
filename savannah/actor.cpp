#include "actor.hpp"

bool isInTheWindow(const Vec2& sub_coord) {
    return (sub_coord.x > 0 && sub_coord.x < field_width&& sub_coord.y>0 && sub_coord.y < field_height);
}
bool plantIsCover(std::vector<Plant>& plant, const Vec2& born_coord) {
    for (size_t j = 0; j < plant.size(); j++) {
        if (plant[j].isCover(born_coord)) return true;
    }
    return false;
}
void plantBorn(std::vector<Plant>& plant, const Vec2& born_coord) {
    if (!isInTheWindow(born_coord)) return;
    if (plantIsCover(plant, born_coord)) return;
    plant.emplace_back();
    plant[plant.size() - 1].setCoord(born_coord);

}
//A•¨‚Ì”ÉB
void plantBreed(std::vector<Plant>& plant, const size_t i) {
    //A•¨‚ÌÀ•W
    const Vec2 plant_c = plant[i].getCoord();
    plantBorn(plant, Vec2(plant_c.x - 10, plant_c.y));
    plantBorn(plant, Vec2(plant_c.x + 10, plant_c.y));
    plantBorn(plant, Vec2(plant_c.x, plant_c.y - 10));
    plantBorn(plant, Vec2(plant_c.x, plant_c.y + 10));
}

//A•¨‚Ìs“®
void plantBehavior(std::vector<Plant>& plant, const double mi_spf) {
    //A•¨‚»‚ê‚¼‚ê‚Ì¶–½Šˆ“®
    for (size_t i = 0; i < plant.size();) {
        bool plant_is_die, plant_is_breed;
        plant[i].lifeActivity(mi_spf, plant_is_die, plant_is_breed);
        //A•¨‚Ì”ÉB
        if (plant_is_breed) plantBreed(plant, i);
        //A•¨‚ªõ–½‚Å€‚Ê
        if (plant_is_die) plant.erase(plant.begin() + i);
        else i++;
    }
}

void herbivoreBehavior(std::vector<Herbivore>& herbivore, std::vector<Plant>& plant, const double mi_spf) {
    //‘H“®•¨‚»‚ê‚¼‚ê‚Ìs“®
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
    //“÷H“®•¨‚»‚ê‚¼‚ê‚Ìs“®
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