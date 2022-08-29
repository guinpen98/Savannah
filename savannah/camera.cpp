#include "camera.h"
#include "get_key.h"
#include "configuration.h"

namespace Savannah {
	Camera::Camera(GetKey* new_get_key) :get_key(new_get_key){}

	void Camera::update()
	{
        get_key->update();
        if (get_key->isZoomIn())
            if (exrate <= 5)
                exrate += change_exrate;
        if (get_key->isZoomOut())
            if (exrate >= 1) {
                exrate -= change_exrate;
                if (x > field_width - window_width / exrate)
                    x = field_width - int(window_width / exrate);
                if (y > field_height - window_height / exrate)
                    y = field_height - int(window_height / exrate);
            }
        if (get_key->isLeft()) if (x >= 0) x -= move_distance;
        if (get_key->isRight()) if (x <= field_width - window_width / exrate) x += move_distance;
        if (get_key->isUp()) if (y >= 0) y -= move_distance;
        if (get_key->isDown()) if (y <= field_height - window_height / exrate) y += move_distance;
	}
}
