#include "vec2.h"

namespace Savannah {
	//コンストラクタ
	Vec2::Vec2(const double ix, const double iy)
		:x(ix), y(iy) {}

	//Vec2同士の距離の二乗
	double Vec2::distanceSquared(const Vec2& coord) const {
		return ((x - coord.x) * (x - coord.x) + (y - coord.y) * (y - coord.y));
	}

	//Vec2同士の足し算
	Vec2 Vec2::operator+(const Vec2& coord) const {
		return Vec2(x + coord.x, y + coord.y);
	}
}