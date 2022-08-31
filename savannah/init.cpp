#include "init.h"
#include "rand.h"
#include "carnivore.h"
#include "get_key.h"
#include "camera.h"
#include "time.h"
#include "actor.h"

namespace Savannah {
    bool Update() { return (DxLib::ScreenFlip() != -1 && DxLib::ClearDrawScreen() != -1 && DxLib::ProcessMessage() != -1); }

    void init() {
        //配列の確保
        std::vector<Herbivore> herbivores;
        std::vector<Plant> plant; plant.reserve(100000);
        std::vector<Carnivore> carnivores;

        double pass_time = 0.0;
        Rand rd;
        GetKey get_key;
        Camera camera(&get_key);
        Time time;

        //草食動物の生成
        for (int i = 0; i < 50; ++i) {
            herbivores.emplace_back(&rd, &time);
        }
        //肉食動物の生成
        for (int i = 0; i < 5; ++i) {
            carnivores.emplace_back(&rd, &time);
        }
        //植物生成
        for (int i = 0; i < 200; ++i) {
            randomPlantBorn(plant, rd, time);
        }
        time.init();

        while (Update()) {
            camera.update();
            time.update();

            plantBehavior(plant);
            herbivoreBehavior(herbivores, plant);
            carnivoreBehavior(carnivores, herbivores);

            for (const auto& p : plant) {
                p.draw(camera.x, camera.y, camera.exrate);
            }
            for (const auto& h : herbivores) {
                h.draw(camera.x, camera.y, camera.exrate);
            }
            for (const auto& c : carnivores) {
                c.draw(camera.x, camera.y, camera.exrate);
            }

            pass_time += time.getSpf() / 1000.0;
            unsigned int Color = GetColor(255, 255, 255);
            DrawFormatString(0, 0, Color, "%d", int(pass_time / 24));
        }
    }
}