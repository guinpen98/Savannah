#include "get_key.h"
#include <DxLib.h>
namespace Savannah {
    void GetKey::update() {
        GetHitKeyStateAll(key_state);
    }
    bool GetKey::isZoomIn()
    {
        return key_state[KEY_INPUT_E];
    }
    bool GetKey::isZoomOut()
    {
        return key_state[KEY_INPUT_Q];
    }
    bool GetKey::isLeft()
    {
        return key_state[KEY_INPUT_A] || key_state[KEY_INPUT_LEFT];
    }
    bool GetKey::isRight()
    {
        return key_state[KEY_INPUT_D] || key_state[KEY_INPUT_RIGHT];
    }
    bool GetKey::isUp()
    {
        return key_state[KEY_INPUT_W] || key_state[KEY_INPUT_UP];
    }
    bool GetKey::isDown()
    {
        return key_state[KEY_INPUT_S] || key_state[KEY_INPUT_DOWN];
    }
}