#include "creatures.h"
#include"configuration.h"
#include "rand.h"
#include "time.h"
#include <cmath>

namespace Savannah {
	//生物クラス実装
	void Creatures::setOld() {
		age += time->getSpf();
	}
	double Creatures::getAge()const {
		return age;
	}
	bool Creatures::isInTheWindow(const Vec2& sub_coord)const {
		return (sub_coord.x > 0 && sub_coord.x < field_width&& sub_coord.y > 0 && sub_coord.y < field_height);
	}
	Vec2 Creatures::getCoord() const {
		return coord;
	}
	void Creatures::setCoord(const Vec2& new_coord) {
		coord = Vec2(new_coord);
	}
	Rand* Creatures::getRd() const
	{
		return rd;
	}
	Time* Creatures::getTime() const
	{
		return time;
	}
	int Creatures::getOneYear()const {
		return one_year;
	}
	double Creatures::getLifespan()const {
		return lifespan;
	}
	Creatures::Creatures(Rand* new_rd, Time* new_time):rd(new_rd), time(new_time)
	{
		coord = rd->randDist();
	}
}