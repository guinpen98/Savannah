#pragma once
#include "DxLib.h"
#include"creatures.hpp"

namespace System {
    bool Update() { return (DxLib::ScreenFlip() != -1 && DxLib::ClearDrawScreen() != -1 && DxLib::ProcessMessage() != -1); }
}

int zebra1 = 0;
int zebra2 = 0;
int zebra3 = 0;
int lion1 = 0;
int lion2 = 0;
int lion3 = 0;
int grass1 = 0;

namespace Draw {
    void oldDraw(const Vec2& coord, const int animalID) {

        unsigned int color = GetColor(255, 255, 255);

        switch (animalID)
        {
        case plantE:
            color = GetColor(0, 255, 0);
            DrawCircle(int(coord.x), int(coord.y), 5, color, TRUE);
            break;
        case herbivoreE:
            //color = GetColor(0, 0, 255);
            DrawRotaGraph(int(coord.x), int(coord.y), 0.05f, 0, zebra1, TRUE);
            break;
        case carnivoreE:
            color = GetColor(255, 0, 0);
            DrawCircle(int(coord.x), int(coord.y), 5, color, TRUE);
            break;
        default:
            break;
        }
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
    zebra1 = LoadGraph("zebra1.png");
    zebra2 = LoadGraph("zebra2.png");
    zebra3 = LoadGraph("zebra3.png");
    lion1 = LoadGraph("lion1.png");
    lion2 = LoadGraph("lion2.png");
    lion3 = LoadGraph("lion3.png");
    grass1 = LoadGraph("grass.png");
    Main();
    DeleteGraph(zebra1);
    DeleteGraph(zebra2);
    DeleteGraph(zebra3);
    return DxLib::DxLib_End();
}