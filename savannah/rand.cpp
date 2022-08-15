#include "rand.h"
#include "vec2.h"

namespace Savannah {
	Vec2 Rand::randDist() {
		return Vec2(wDistr(eng), hDistr(eng));
	}
}