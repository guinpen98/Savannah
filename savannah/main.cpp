#include"init.hpp"
#include"actor.hpp"
#include"creatures.h"
#include<random>
#include<vector>
#include <chrono>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    DxLib::SetOutApplicationLogValidFlag(FALSE);
    DxLib::ChangeWindowMode(TRUE);
    DxLib::SetGraphMode(windowWidth, windowHeight, 32);
    DxLib::SetMainWindowText("Sample");
    if (DxLib::DxLib_Init() == -1) return -1;
    DxLib::SetDrawScreen(DX_SCREEN_BACK);
    Main();
    return DxLib::DxLib_End();
}

void Main() {
    //Draw draw[3]
    std::vector<Herbivore> herbivore;

    std::chrono::system_clock::time_point  start, end;

    std::random_device rd;
    std::mt19937 eng(rd());
    //1フレーム後の動物の座標とID
    int animalNewX, animalNewY, animalID;
    //確率
    std::bernoulli_distribution uid(0.01);
    while (System::Update()) {
        end = std::chrono::system_clock::now();

        if (uid(eng)) herbivore.emplace_back();
        for (auto& h : herbivore) {
            h.getFps(double(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));
            h.behavior(animalNewX,animalNewY,animalID);
            Draw::circleDraw(animalNewX, animalNewY, animalID);
        }

        start = std::chrono::system_clock::now();
    }

}