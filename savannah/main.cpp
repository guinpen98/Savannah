#include"init.hpp"
#include "property.hpp"

int zebra1 = 0;
int zebra2 = 0;
int zebra3 = 0;
int lion1 = 0;
int lion2 = 0;
int lion3 = 0;
int grass1 = 0;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    DxLib::SetOutApplicationLogValidFlag(FALSE);
    DxLib::ChangeWindowMode(TRUE);
    DxLib::SetGraphMode(window_width, window_height, 32);
    DxLib::SetMainWindowText("Sample");
    SetBackgroundColor(222, 192, 106);
    if (DxLib::DxLib_Init() == -1) return -1;
    DxLib::SetDrawScreen(DX_SCREEN_BACK);
    zebra1 = LoadGraph("zebra1.png");
    zebra2 = LoadGraph("zebra2.png");
    zebra3 = LoadGraph("zebra3.png");
    lion1 = LoadGraph("lion1.png");
    lion2 = LoadGraph("lion2.png");
    lion3 = LoadGraph("lion3.png");
    grass1 = LoadGraph("grass.png");
    init();
    DeleteGraph(zebra1);
    DeleteGraph(zebra2);
    DeleteGraph(zebra3);
    return DxLib::DxLib_End();
}