#include "init.hpp"

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
        //ランダム
        constexpr int MIN = 0;
        constexpr int wMAX = field_width;
        constexpr int hMAX = field_height;
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<int> wDistr(MIN, wMAX);
        std::uniform_int_distribution<int> hDistr(MIN, hMAX);
        //確率
        std::bernoulli_distribution uid(0.01);

        //草食動物の生成
        herbivores.resize(50);
        for (auto& herbivore : herbivores) {
            herbivore.setCoord(Vec2(wDistr(eng), hDistr(eng)));
        }
        //肉食動物の生成
        carnivores.resize(5);
        for (auto& carnivore : carnivores) {
            carnivore.setCoord(Vec2(wDistr(eng), hDistr(eng)));
        }
        //植物生成
        for (int i = 0; i < 200; i++) {
            plantBorn(plant, Vec2(wDistr(eng), hDistr(eng)));
        }
        char key_state[256];
        int camera_x = 0;
        int camera_y = 0;
        const int camera_move_distance = 3;
        const double camera_change_exrate = 0.01;
        double camera_exrate = 1;


        while (Update()) {
            GetHitKeyStateAll(key_state);
            if (key_state[KEY_INPUT_E])
                if (camera_exrate <= 5)
                    camera_exrate += camera_change_exrate;
            if (key_state[KEY_INPUT_Q])
                if (camera_exrate >= 1) {
                    camera_exrate -= camera_change_exrate;
                    if (camera_x > field_width - window_width / camera_exrate)
                        camera_x = field_width - window_width / camera_exrate;
                    if (camera_y > field_height - window_height / camera_exrate)
                        camera_y = field_height - window_height / camera_exrate;
                }
            if (key_state[KEY_INPUT_A] || key_state[KEY_INPUT_LEFT])
                if (camera_x >= 0) camera_x -= camera_move_distance;
            if (key_state[KEY_INPUT_D] || key_state[KEY_INPUT_RIGHT])
                if (camera_x <= field_width - window_width / camera_exrate) camera_x += camera_move_distance;
            if (key_state[KEY_INPUT_W] || key_state[KEY_INPUT_UP])
                if (camera_y >= 0) camera_y -= camera_move_distance;
            if (key_state[KEY_INPUT_S] || key_state[KEY_INPUT_DOWN])
                if (camera_y <= field_height - window_height / camera_exrate) camera_y += camera_move_distance;
            for (int k = 0; k < 1; k++) {
                //1フレームあたりの時間計測
                old_time = new_time;
                new_time = std::chrono::system_clock::now();

                //ランダムで草食動物生成
                //if (uid(eng)) herbivore.emplace_back();

                const double mi_spf = double(std::chrono::duration_cast<std::chrono::milliseconds>(new_time - old_time).count());

                plantBehavior(plant, mi_spf);
                herbivoreBehavior(herbivores, plant, mi_spf);
                carnivoreBehavior(carnivores, herbivores, mi_spf);

                for (const auto& p : plant) {
                    p.draw(camera_x, camera_y, camera_exrate);
                }
                for (const auto& h : herbivores) {
                    h.draw(camera_x, camera_y, camera_exrate);
                }
                for (const auto& c : carnivores) {
                    c.draw(camera_x, camera_y, camera_exrate);
                }

                pass_time += mi_spf / 1000.0;
                unsigned int Color = GetColor(255, 255, 255);
                DrawFormatString(0, 0, Color, "%d", int(pass_time / 24));
            }
        }
    }
}