#include "creatures.hpp"

//�����N���X����
void Creatures::setSpf(const double mi_spf) {
	spf = mi_spf / 1000.0;
}
double Creatures::getSpf() const {
	return spf;
}
void Creatures::getOld() {
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
int Creatures::getOneYear()const {
	return one_year;
}
double Creatures::getLifespan()const {
	return lifespan;
}