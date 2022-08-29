#ifndef KIPL_CAMERA_H
#define KIPL_CAMERA_H
namespace Savannah {
    class Camera
    {
    private:
        class GetKey* get_key;
        const int move_distance = 3;
        const double change_exrate = 0.01;
    public:
        int x = 0;
        int y = 0;
        double exrate = 1;
        Camera(GetKey*);
        void update();
    };
}
#endif // !KIPL_CAMERA_H

