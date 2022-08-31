#ifndef SAVANNAH_PLANT_H
#define SAVANNAH_PLANT_H

#include"creatures.h"

namespace Savannah {
    //植物クラス
    class Plant : public Creatures {
    private:
        double breed = 0.0;
        //繁殖判定
        bool isBreed();
    public:
        //コンストラクタ
        explicit Plant(Rand*, Time*);
        //生命活動
        void lifeActivity(bool& is_die, bool& is_breed);
        //他の植物と被っているかの判定
        bool isCover(const Vec2& sub_coord)const;

        void draw(int camera_x, const int camera_y, const double camera_exrate)const;
    };
}


#endif // !SAVANNAH_PLANT_H