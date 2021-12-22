#include"init.hpp"

class Draw {
private:
    int x = 0;
    int x2 = 500;
public:
    void circleDraw() {
        DrawCircle(x++, 240, 150, GetColor(0, 0, 255), TRUE);
        DrawCircle(x2--, 240, 150, GetColor(255, 0, 0), TRUE);
    }
};

void Main() {
    Draw draw;

    while (System::Update()) {
        draw.circleDraw();
        

    }

}