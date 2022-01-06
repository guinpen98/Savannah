#include "plant.hpp"

//A•¨ƒNƒ‰ƒXŽÀ‘•
void Plant::lifeActivity(const double mi_spf, bool& is_die, bool& is_breed) {
    setSpf(mi_spf);
    getOld();
    breed += getSpf();
    is_breed = isBreed();
    is_die = (getAge() > one_year * lifespan);
    Vec2 temp_coord = getCoord();
    is_die = (temp_coord.x<0 || temp_coord.x>field_width || temp_coord.y<0 || temp_coord.y>field_height);
}
bool Plant::isCover(const Vec2& sub_coord) {
    return (getCoord().distance(sub_coord) < 100.0);
}
bool Plant::isBreed() {
    if (breed > one_year && getAge() > one_year / 2) {
        breed = 0.0;
        return true;
    }
    return false;
}