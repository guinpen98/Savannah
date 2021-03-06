#ifndef SAVANNAH_ACTOR_HPP
#define SAVANNAH_ACTOR_HPP
#include"plant.hpp"
#include"herbivore.hpp"
#include"carnivore.hpp"
#include<vector>

bool isInTheWindow(const Vec2& sub_coord);
bool plantIsCover(std::vector<Plant>& plant, const Vec2& born_coord);
void plantBorn(std::vector<Plant>& plant, const Vec2& born_coord);
//植物の繁殖
void plantBreed(std::vector<Plant>& plant, const size_t i);
//植物の行動
void plantBehavior(std::vector<Plant>& plant, const double mi_spf);
void herbivoreBehavior(std::vector<Herbivore>& herbivore, std::vector<Plant>& plant, const double mi_spf);
void carnivoreBehavior(std::vector<Carnivore>& carnivore, std::vector<Herbivore>& herbivore, const double mi_spf);
#endif // !SAVANNAH_ACTOR_HPP