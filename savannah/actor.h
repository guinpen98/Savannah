#ifndef SAVANNAH_ACTOR_H
#define SAVANNAH_ACTOR_H
#include"carnivore.h"

namespace Savannah {
	bool isInTheWindow(const Vec2& sub_coord);
	bool plantIsCover(std::vector<Plant>& plant, const Vec2& born_coord);
	void plantBorn(std::vector<Plant>& plant, const Vec2& born_coord);
	void randomPlantBorn(std::vector<Plant>& plant, class Rand& rd, class Time& time);
	//植物の繁殖
	void plantBreed(std::vector<Plant>& plant, const size_t i);
	//植物の行動
	void plantBehavior(std::vector<Plant>& plant);
	void herbivoreBehavior(std::vector<Herbivore>& herbivore, std::vector<Plant>& plant);
	void carnivoreBehavior(std::vector<Carnivore>& carnivore, std::vector<Herbivore>& herbivore);
}

#endif // !SAVANNAH_ACTOR_H
