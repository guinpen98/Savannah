#include "creatures.hpp"
#include "rand.h"

namespace Savannah {
	//生物クラス実装
	void Creatures::setSpf(const double mi_spf) {
		spf = mi_spf / 1000.0;
	}
	double Creatures::getSpf() const {
		return spf;
	}
	void Creatures::setOld() {
		age += spf;
	}
	double Creatures::getAge()const {
		return age;
	}
	bool Creatures::isInTheWindow(const Vec2& sub_coord)const {
		return (sub_coord.x > 0 && sub_coord.x < field_width&& sub_coord.y>0 && sub_coord.y < field_height);
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
	int Creatures::getOneYear()const {
		return one_year;
	}
	double Creatures::getLifespan()const {
		return lifespan;
	}
	Creatures::Creatures(Rand* new_rd):rd(new_rd) {}
}