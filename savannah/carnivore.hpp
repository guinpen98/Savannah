#ifndef SAVANNAH_CARNIVORE_HPP
#define SAVANNAH_CARNIVORE_HPP
#include"animal.hpp"
#include"herbivore.hpp"

enum CarnivoreStateE :int {
	carnivoreWanderE
	, carnivoreForageE
	, carnivoreBreedE
	, carnivoreDieE
};

//肉食動物クラス
class Carnivore : public Animal {
public:
    CarnivoreStateE carnivore_state = carnivoreWanderE;
    explicit Carnivore() {
        lifespan = 20.0;
        one_year = 24;
        breed_period = one_year;
        breed_age = 2.0 * one_year;
    }
    //行動
    void behavior(std::vector<Carnivore>& carnivore, std::vector<Herbivore>& herbivore, const size_t hs);
    //距離を計測
    double distance(const Vec2& herbivore_coord)const;

    //食事
    void eat(std::vector<Herbivore>& herbivore, const size_t s);

    //肉食動物の近くにある草食動物物を探す
    void isCloseToHerbivores(const std::vector<Herbivore>& herbivore, size_t& s, bool& is_can_eat);
    //繁殖
    void carnivoreBreed(std::vector<Carnivore>& carnivore, const size_t hs);
    //子供が生まれる
    void born(const Vec2& born_coord, std::vector<Carnivore>& carnivore, const size_t s);
    //ステートの値を渡す
    int getCarnivoreState();
    //ステートの変更
    void setCarnivoreState(enum CarnivoreStateE new_state);

    void draw(int camera_x, const int camera_y, const double camera_exrate)const;
};

#endif // !SAVANNAH_CARNIVORE_HPP