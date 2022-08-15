#include"init.h"
#include "graph.h"
#include"configuration.h"

namespace Savannah {
    int zebra1 = 0;
    int zebra2 = 0;
    int zebra3 = 0;
    int lion1 = 0;
    int lion2 = 0;
    int lion3 = 0;
    int grass1 = 0;
}

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
    DxLib::SetOutApplicationLogValidFlag(FALSE);
    DxLib::ChangeWindowMode(TRUE);
    DxLib::SetGraphMode(window_width, window_height, 32);
    DxLib::SetMainWindowText("Sample");
    SetBackgroundColor(222, 192, 106);
    if (DxLib::DxLib_Init() == -1) return -1;
    DxLib::SetDrawScreen(DX_SCREEN_BACK);
    Savannah::zebra1 = LoadGraph("zebra1.png");
    Savannah::zebra2 = LoadGraph("zebra2.png");
    Savannah::zebra3 = LoadGraph("zebra3.png");
    Savannah::lion1 = LoadGraph("lion1.png");
    Savannah::lion2 = LoadGraph("lion2.png");
    Savannah::lion3 = LoadGraph("lion3.png");
    Savannah::grass1 = LoadGraph("grass.png");
    Savannah::init();
    DeleteGraph(Savannah::zebra1);
    DeleteGraph(Savannah::zebra2);
    DeleteGraph(Savannah::zebra3);
    DeleteGraph(Savannah::lion1);
    DeleteGraph(Savannah::lion2);
    DeleteGraph(Savannah::lion3);
    DeleteGraph(Savannah::grass1);
    return DxLib::DxLib_End();
}