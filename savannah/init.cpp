#include "init.h"
#include "rand.h"
#include "actor.h"
#include <chrono>
#include "carnivore.h"
#include "get_key.h"
#include "camera.h"

namespace Savannah {
    bool Update() { return (DxLib::ScreenFlip() != -1 && DxLib::ClearDrawScreen() != -1 && DxLib::ProcessMessage() != -1); }

    void init() {
        //配列の確保
        std::vector<Herbivore> herbivores;
        std::vector<Plant> plant; plant.reserve(100000);
        std::vector<Carnivore> carnivores;
        //時間
        std::chrono::system_clock::time_point  old_time, new_time = std::chrono::system_clock::now();
        double pass_time = 0.0;
        Rand rd;

        //草食動物の生成
        for (int i = 0; i < 50;++i) {
            herbivores.emplace_back(&rd);
        }
        //肉食動物の生成
        for (int i = 0; i < 5;++i) {
            carnivores.emplace_back(&rd);
        }
        //植物生成
        for (int i = 0; i < 200; i++) {
            randomPlantBorn(plant, rd);
        }
        GetKey get_key;
        Camera camera(&get_key);


        while (Update()) {
            camera.update();
            //1フレームあたりの時間計測
            old_time = new_time;
            new_time = std::chrono::system_clock::now();

            const double mi_spf = double(std::chrono::duration_cast<std::chrono::milliseconds>(new_time - old_time).count());

            plantBehavior(plant, mi_spf);
            herbivoreBehavior(herbivores, plant, mi_spf);
            carnivoreBehavior(carnivores, herbivores, mi_spf);

            for (const auto& p : plant) {
                p.draw(camera.x, camera.y, camera.exrate);
            }
            for (const auto& h : herbivores) {
                h.draw(camera.x, camera.y, camera.exrate);
            }
            for (const auto& c : carnivores) {
                c.draw(camera.x, camera.y, camera.exrate);
            }

            pass_time += mi_spf / 1000.0;
            unsigned int Color = GetColor(255, 255, 255);
            DrawFormatString(0, 0, Color, "%d", int(pass_time / 24));
        }
    }
}