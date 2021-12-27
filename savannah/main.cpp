#include"init.hpp"
#include"actor.hpp"
#include<random>
#include<vector>
#include <chrono>




void Main() {
    //配列の確保
    std::vector<Herbivore> herbivore;
    std::vector<Plant> plant;
    //時間
    std::chrono::system_clock::time_point  old_time, new_time = std::chrono::system_clock::now();
    //ランダム
    std::random_device rd;
    std::mt19937 eng(rd());
    //確率
    std::bernoulli_distribution uid(0.01);

    //植物生成
    for (int i = 0; i < 4; i++) {
        int seeds_count;
        plant.emplace_back();
        plant[i].born(plant,Vec2(i * 15.0+50.0, i * 25.0+20.0),seeds_count);
    }
    plant.emplace_back();

    while (System::Update()) {
        for (int k = 0; k < 1; k++) {
            //1フレームあたりの時間計測
            old_time = new_time;
            new_time = std::chrono::system_clock::now();

            //ランダムで草食動物生成
            if (uid(eng)) herbivore.emplace_back();

            const double mi_spf = double(std::chrono::duration_cast<std::chrono::milliseconds>(new_time - old_time).count());

            plantLifeActivity(plant, mi_spf);
            herbivoreBehavior(herbivore, mi_spf);



        }

    }
}