#ifndef SAVANNAH_ANIMAL_HPP
#define SAVANNAH_ANIMAL_HPP
#include"creatures.hpp"

namespace Savannah {
    //動物クラス
    class Animal : public Creatures {
    private:
        double distance = 100.0;
        bool is_left_direction = true;

        //目的地との距離
        void calculateDistinationDistance();
        //向きの設定
        void setIsLeftDirection(const double dx);
        //繁殖からの時間経過
        void passBreedPeriod();
    protected:
        Vec2 distination_coord;
        double max_satiety = one_year;
        double satiety = max_satiety;
        double breed_count = 0.0;
        double breed_age = 3.0 * one_year;
        double breed_period = one_year / 4.0;

        //新しい座標の設定
        void move();
        //目的地にいるかどうかの判定
        bool isDistination();
        //目的地の設定
        void setDistination(const Vec2 new_coord);
        //向きの取得
        bool getIsLeftDirection()const;
        //繁殖期かどうかの判定
        bool isBreedingSeason();
    public:
        Animal(Rand*);
        //目的地をランダムに設定
        void setRandomDistination();
        //生命活動を管理
        void lifeActivity(const double mi_spf, bool& is_die);
    };
}

#endif // !SAVANNAH_ANIMAL_HPP