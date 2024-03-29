﻿#include "plant.h"
#include "configuration.h"
#include "time.h"

namespace Savannah {
    Plant::Plant(Rand* rd, Time* time):Creatures(rd, time)
    {
        one_year = 24;
        lifespan = 5.0;
    }
    //植物クラス実装
    void Plant::lifeActivity(bool& is_die, bool& is_breed) {
        setOld();
        breed += time->getSpf();
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