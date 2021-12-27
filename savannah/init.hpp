#pragma once
#include "DxLib.h"
#include"creatures.hpp"

namespace System {
    bool Update() { return (DxLib::ScreenFlip() != -1 && DxLib::ClearDrawScreen() != -1 && DxLib::ProcessMessage() != -1); }
}

int shimauma1 = 0;
int shimauma2 = 0;
int shimauma3 = 0;

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
            DrawRotaGraph(int(coord.x), int(coord.y), 0.05f, 0, shimauma1, TRUE);
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
    shimauma1 = LoadGraph("animal_shimauma1.png");
    shimauma2 = LoadGraph("animal_shimauma2.png");
    shimauma3 = LoadGraph("animal_shimauma3.png");
    Main();
    DeleteGraph(shimauma1);
    DeleteGraph(shimauma2);
    DeleteGraph(shimauma3);
    return DxLib::DxLib_End();
}