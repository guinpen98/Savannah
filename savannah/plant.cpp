#include "plant.hpp"

namespace Savannah {
    //植物クラス実装
    void Plant::lifeActivity(const double mi_spf, bool& is_die, bool& is_breed) {
        setSpf(mi_spf);
        setOld();
        breed += getSpf();
        is_breed = isBreed();
        Vec2 temp_coord = getCoord();
        is_die = (temp_coord.x < 0 || temp_coord.x > field_width || temp_coord.y < 0 || temp_coord.y > field_height || getAge() > one_year * lifespan);
    }
    bool Plant::isCover(const Vec2& sub_coord)const {
        return (getCoord().distanceSquared(sub_coord) < 100.0);
    }
    bool Plant::isBreed() {
        if (breed > one_year && getAge() > one_year / 2) {
            breed = 0.0;
            return true;
        }
        return false;
    }
}