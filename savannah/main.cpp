#include"init.hpp"
#include"actor.hpp"
#include<random>
#include<vector>
#include <chrono>


void DrawHerbivore(const std::vector<Herbivore>& herbivore,const int camera_x,const int camera_y, const double camera_exrate) {
    for (const auto& h : herbivore) {
        const double ext_rate = 0.05 * (1.0 + h.getAge() / h.getOneYear() / h.getLifespan())* camera_exrate;
        int zebra_picture = zebra1;
        switch (h.herbivore_state)
        {
        case herbivoreWanderE:
            zebra_picture = zebra1;
            break;
        case herbivoreForageE:
            zebra_picture = zebra2;
            break;
        case herbivoreBreedE:
            zebra_picture = zebra3;
            break;
        default:
            break;

        }
        DrawRotaGraph((int(h.getCoord().x) - camera_x)* camera_exrate, (int(h.getCoord().y) - camera_y)* camera_exrate, float(ext_rate), 0, zebra_picture, TRUE);
    }
}
void DrawCarnivore(const std::vector<Carnivore>& carnivore, const int camera_x, const int camera_y,const double camera_exrate) {
    for (const auto& c : carnivore) {
        const double ext_rate = 0.05 * (1.0 + c.getAge() / c.getOneYear() / c.getLifespan())* camera_exrate;
        int lion_picture = lion1;
        switch (c.carnivore_state)
        {
        case carnivoreWanderE:
            lion_picture = lion1;
            break;
        case carnivoreForageE:
            lion_picture = lion2;
            break;
        case carnivoreBreedE:
            lion_picture = lion3;
            break;
        default:
            break;
        }
        DrawRotaGraph((int(c.getCoord().x) - camera_x)* camera_exrate, (int(c.getCoord().y) - camera_y)* camera_exrate, float(ext_rate), 0, lion_picture, TRUE);
    }
}
void DrawPlant(const std::vector<Plant>& plant,const int camera_x, const int camera_y, const double camera_exrate) {
    for (const auto& p : plant) {
        const double ext_rate = 0.05* camera_exrate;
        const double age = p.getAge();
        DrawRotaGraph((int(p.getCoord().x) - camera_x) * camera_exrate, (int(p.getCoord().y) - camera_y) * camera_exrate, float(ext_rate), 0, grass1, TRUE);
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
    constexpr int wMAX = field_width;
    constexpr int hMAX = field_height;
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
    char key_state[256];
    int camera_x = 0;
    int camera_y = 0;
    const int camera_move_distance = 3;
    const double camera_change_exrate = 0.01;
    double camera_exrate = 1;
    

    while (System::Update()) {
        GetHitKeyStateAll(key_state);
        if (key_state[KEY_INPUT_E])
            if (camera_exrate <= 5)
                camera_exrate += camera_change_exrate;
        if (key_state[KEY_INPUT_Q])
            if (camera_exrate >= 1)
                camera_exrate -= camera_change_exrate;
        if (key_state[KEY_INPUT_A] || key_state[KEY_INPUT_LEFT])
            if(camera_x>=0) camera_x -= camera_move_distance;
        if (key_state[KEY_INPUT_D] || key_state[KEY_INPUT_RIGHT])
            if (camera_x <= field_width-window_width/camera_exrate) camera_x += camera_move_distance;
        if (key_state[KEY_INPUT_W] || key_state[KEY_INPUT_UP])
            if (camera_y >= 0) camera_y -= camera_move_distance;
        if (key_state[KEY_INPUT_S] || key_state[KEY_INPUT_DOWN])
            if (camera_y <= field_height-window_height/camera_exrate) camera_y += camera_move_distance;
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
            DrawPlant(plant,camera_x,camera_y, camera_exrate);
            DrawHerbivore(herbivore,camera_x,camera_y, camera_exrate);
            DrawCarnivore(carnivore,camera_x,camera_y, camera_exrate);


            pass_time += mi_spf/1000.0;
            unsigned int Color = GetColor(255, 255, 255);
            DrawFormatString(0, 0, Color, "%d", int(pass_time / 24 ));
        }
    }
}