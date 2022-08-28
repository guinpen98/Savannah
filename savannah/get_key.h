#ifndef SAVANNAH_GET_KEY_H
#define SAVANNAH_GET_KEY_H
namespace Savannah {
    class GetKey
    {
    private:
    public:
        char key_state[256];
        void update();
        bool isZoomIn();
        bool isZoomOut();
        bool isLeft();
        bool isRight();
        bool isUp();
        bool isDown();
    };
}
#endif //!SAVANNAH_GET_KEY_H