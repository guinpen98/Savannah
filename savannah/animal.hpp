#ifndef SAVANNAH_ANIMAL_HPP
#define SAVANNAH_ANIMAL_HPP
#include"creatures.hpp"
#include<random>

//動物クラス
class Animal : public Creatures {
private:
    double distance = 100.0;
    bool is_left_direction = true;
protected:
    Vec2 distination_coord = Vec2(field_width / 2.0, field_height / 2.0);
    double max_satiety = one_year;
    double satiety = max_satiety;
    double breed_count = 0.0;
    double breed_age = 3.0 * one_year;
    double breed_period = one_year / 4.0;
public:
    //新しい座標の設定
    void move();
    //目的地にいるかどうかの判定
    bool isDistination();
    //目的地をランダムに設定
    void setRandomDistination();
    //目的地の設定
    void setDistination(const Vec2 new_coord);
    //目的地との距離
    void calculateDistinationDistance();
    //向きの設定
    void setIsLeftDirection(const double dx);
    //向きの取得
    bool getIsLeftDirection()const;
    //生命活動を管理
    void lifeActivity(const double mi_spf, bool& is_die);
    //繁殖期かどうかの判定
    bool isBreedingSeason();
    //繁殖からの時間経過
    void PassBreedPeriod();
};

#endif // !SAVANNAH_ANIMAL_HPP