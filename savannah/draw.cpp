#include "draw.hpp"

namespace Savannah {
    void Plant::draw(int camera_x, const int camera_y, const double camera_exrate)const {
        const double ext_rate = 0.05 * camera_exrate;
        const double age = getAge();
        DrawRotaGraph(int((getCoord().x - camera_x) * camera_exrate), int((getCoord().y - camera_y) * camera_exrate), float(ext_rate), 0, grass1, TRUE);
    }


    void Carnivore::draw(int camera_x, const int camera_y, const double camera_exrate)const {
        const double ext_rate = 0.05 * (1.0 + getAge() / getOneYear() / getLifespan()) * camera_exrate;
        int lion_picture = lion1;
        switch (carnivore_state)
        {
        case CarnivoreStateE::carnivoreWanderE:
            lion_picture = lion1;
            break;
        case CarnivoreStateE::carnivoreForageE:
            lion_picture = lion2;
            break;
        case CarnivoreStateE::carnivoreBreedE:
            lion_picture = lion3;
            break;
        default:
            break;
        }
        DrawRotaGraph(int((getCoord().x - camera_x) * camera_exrate), int((getCoord().y - camera_y) * camera_exrate), float(ext_rate), 0, lion_picture, TRUE, getIsLeftDirection() ? FALSE : TRUE);
    }

    void Herbivore::draw(int camera_x, const int camera_y, const double camera_exrate)const {
        const double ext_rate = 0.05 * (1.0 + getAge() / getOneYear() / getLifespan()) * camera_exrate;
        int zebra_picture = zebra1;
        switch (herbivore_state)
        {
        case HerbivoreStateE::herbivoreWanderE:
            zebra_picture = zebra1;
            break;
        case HerbivoreStateE::herbivoreForageE:
            zebra_picture = zebra2;
            break;
        case HerbivoreStateE::herbivoreBreedE:
            zebra_picture = zebra3;
            break;
        default:
            break;

        }
        DrawRotaGraph(int((getCoord().x - camera_x) * camera_exrate), int((getCoord().y - camera_y) * camera_exrate), float(ext_rate), 0, zebra_picture, TRUE, getIsLeftDirection() ? FALSE : TRUE);
    }
}