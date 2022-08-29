#ifndef KIPL_CAMERA_H
#define KIPL_CAMERA_H
class Camera
{
public:
    int x = 0;
    int y = 0;
    const int move_distance = 3;
    const double change_exrate = 0.01;
    double exrate = 1;
};
#endif // !KIPL_CAMERA_H

