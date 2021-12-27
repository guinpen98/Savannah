#pragma once
#include"init.hpp"
#include"plant.hpp"
#include"herbivore.hpp"
#include<vector>


void plantLifeActivity(std::vector<Plant>& plant, const double mi_spf) {
    //植物それぞれの生命活動
    for (size_t i = 0; i < plant.size();) {
        bool plant_is_die, plant_is_breed;
        plant[i].lifeActivity(mi_spf, plant_is_die, plant_is_breed);
        //植物の繁殖
        if (plant_is_breed) {
            //植物の座標
            const Vec2 plant_c = plant[i].getCoordinate();
            const unsigned int plant_size = plant.size();
            int seeds_count = 0;
            plant[i].born(plant,Vec2(plant_c.x - 10, plant_c.y),seeds_count);
            plant[i].born(plant,Vec2(plant_c.x + 10, plant_c.y),seeds_count);
            plant[i].born(plant,Vec2(plant_c.x, plant_c.y - 10),seeds_count);
            plant[i].born(plant,Vec2(plant_c.x, plant_c.y + 10),seeds_count);
            //植物が他の植物に被っている場合死ぬ


            for (int k = 0; k < seeds_count; k++) {
                for (size_t j = 0; j < plant_size; j++) {
                    //植物の座標
                    const Vec2 plant_c = plant[j].getCoordinate();
                    if (plant[plant_size + k].isCover(plant_c)) {
                        plant.erase(plant.begin() + plant_size + k);
                        seeds_count--;
                        k--;
                        break;
                    }
                }
            }
        }

        //植物の死
        if (plant_is_die) {
            plant.erase(plant.begin() + i);
        }
        else {
            i++;
        }
    }

}

void herbivoreBehavior(std::vector<Herbivore>& herbivore, const double mi_spf) {
    //草食動物それぞれの行動
    for (size_t i = 0; i < herbivore.size();) {
        auto& h = herbivore[i];
        bool herbivore_is_die;
        h.lifeActivity(mi_spf, herbivore_is_die);
        if (herbivore_is_die) {
            herbivore.erase(herbivore.begin() + i);
        }
        else {
            h.behavior();
            i++;
        }
    }
}