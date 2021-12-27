#pragma once
#include "DxLib.h"
#include"creatures.hpp"

namespace System {
    bool Update() { return (DxLib::ScreenFlip() != -1 && DxLib::ClearDrawScreen() != -1 && DxLib::ProcessMessage() != -1); }
}

namespace Draw {
    void circleDraw(Vec2& coord, const int animalID) {

        unsigned int color = GetColor(255, 255, 255);

        switch (animalID)
        {
        case plantE:
            color = GetColor(0, 255, 0);
            break;
        case herbivoreE:
            color = GetColor(0, 0, 255);
            break;
        case carnivoreE:
            color = GetColor(255, 0, 0);
            break;
        default:
            break;
        }

        DrawCircle(int(coord.x), int(coord.y), 5, color, TRUE);
    }
};

void Main();


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