#include"init.hpp"
#include"actor.hpp"
#include<random>
#include<vector>
#include <chrono>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    DxLib::SetOutApplicationLogValidFlag(FALSE);
    DxLib::ChangeWindowMode(TRUE);
    DxLib::SetGraphMode(window_width, window_height, 32);
    DxLib::SetMainWindowText("Sample");
    if (DxLib::DxLib_Init() == -1) return -1;
    DxLib::SetDrawScreen(DX_SCREEN_BACK);
    Main();
    return DxLib::DxLib_End();
}

void Main() {
    //Draw draw[3]
    std::vector<Herbivore> herbivore;

    std::chrono::system_clock::time_point  old_time, new_time;

    std::random_device rd;
    std::mt19937 eng(rd());
    //1フレーム後の動物の座標とID
    int animalID;
    //死亡判定
    bool isDie;
    //確率
    std::bernoulli_distribution uid(0.01);
    new_time = std::chrono::system_clock::now();
    while (System::Update()) {
        for (int j = 0; j < 1; ++j) {
            //1フレームあたりの時間計測
            old_time = new_time;
            new_time = std::chrono::system_clock::now();

            if (uid(eng)) herbivore.emplace_back();
            for (size_t i = 0; i < herbivore.size();) {
                auto& h = herbivore[i];
                h.lifeActivity(double(std::chrono::duration_cast<std::chrono::milliseconds>(new_time - old_time).count()), isDie);
                if (isDie) {
                    herbivore.erase(herbivore.begin() + i);
                }
                else {
                    h.behavior();
                    i++;
                }
            }

        }

    }
}