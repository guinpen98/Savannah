#pragma once
#include "DxLib.h"
#include"creatures.h"

namespace System {
    bool Update() { return (DxLib::ScreenFlip() != -1 && DxLib::ClearDrawScreen() != -1 && DxLib::ProcessMessage() != -1); }
}

namespace Draw {
    void circleDraw(const int x, const int y, const int animalID) {
        switch (animalID)
        {
        case plantE:
            DrawCircle(x, y, 5, GetColor(0, 255, 0), TRUE);
            break;
        case herbivoreE:
            DrawCircle(x, y, 5, GetColor(0, 0, 255), TRUE);
            break;
        case carnivoreE:
            DrawCircle(x, y, 5, GetColor(255, 0, 0), TRUE);
            break;
        default:
            break;
        }
    }
};

void Main();
constexpr int windowWidth = 512;
constexpr int windowHeight = 512;

