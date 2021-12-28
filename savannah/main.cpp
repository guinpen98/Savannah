#include"init.hpp"
#include"actor.hpp"
#include<random>
#include<vector>
#include <chrono>


void DrawHerbivore(const std::vector<Herbivore>& herbivore) {
    for (const auto& h : herbivore) {
        const double ext_rate = 0.05 * (1.0 + h.getAge() / h.getOneYear() / h.getLifespan());
        switch (h.herbivore_state)
        {
        case herbivoreWanderE:
            DrawRotaGraph(int(h.getCoord().x), int(h.getCoord().y), float(ext_rate), 0, shimauma1, TRUE);
            break;
        case herbivoreForageE:
            DrawRotaGraph(int(h.getCoord().x), int(h.getCoord().y), float(ext_rate), 0, shimauma2, TRUE);
            break;
        case herbivoreBreedE:
            DrawRotaGraph(int(h.getCoord().x), int(h.getCoord().y), float(ext_rate), 0, shimauma3, TRUE);
            break;
        default:
            break;
        }
    }
}
void DrawCarnivore(const std::vector<Carnivore>& carnivore) {
    for (const auto& c : carnivore) {
        Draw::oldDraw(c.getCoord(), carnivoreE);
    }
}

void Main() {
    //配列の確保
    std::vector<Herbivore> herbivore;
    std::vector<Plant> plant; plant.reserve(100000);
    std::vector<Carnivore> carnivore;
    //時間
    std::chrono::system_clock::time_point  old_time, new_time = std::chrono::system_clock::now();
    double pass_time = 0.0;
    //ランダム
    constexpr int MIN = 0;
    constexpr int wMAX = window_width;
    constexpr int hMAX = window_height;
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> wDistr(MIN, wMAX);
    std::uniform_int_distribution<int> hDistr(MIN, hMAX);
    //確率
    std::bernoulli_distribution uid(0.01);

    //草食動物の生成
    for (int i = 0; i < 50; i++) {
        herbivore.emplace_back();
        herbivore.back().setCoord(Vec2(wDistr(eng), hDistr(eng)));
    }
    //肉食動物の生成
    for (int i = 0; i < 5; i++) {
        carnivore.emplace_back();
        carnivore.back().setCoord(Vec2(wDistr(eng), hDistr(eng)));
    }
    //植物生成
    for (int i = 0; i < 200; i++) {
        plantBorn(plant, Vec2(wDistr(eng), hDistr(eng)));
    }

    while (System::Update()) {
        for (int k = 0; k < 1; k++) {
            //1フレームあたりの時間計測
            old_time = new_time;
            new_time = std::chrono::system_clock::now();

            //ランダムで草食動物生成
            //if (uid(eng)) herbivore.emplace_back();

            const double mi_spf = double(std::chrono::duration_cast<std::chrono::milliseconds>(new_time - old_time).count());

            plantBehavior(plant, mi_spf);
            herbivoreBehavior(herbivore,plant, mi_spf);
            carnivoreBehavior(carnivore,herbivore, mi_spf);
            DrawHerbivore(herbivore);
            DrawCarnivore(carnivore);


            pass_time += mi_spf/1000.0;
            unsigned int Color = GetColor(255, 255, 255);
            DrawFormatString(0, 0, Color, "%d", int(pass_time / 24 ));
        }
    }
}