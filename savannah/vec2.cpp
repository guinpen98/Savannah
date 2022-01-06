#include "vec2.hpp"

//�R���X�g���N�^
Vec2::Vec2(const double ix, const double iy)
	:x(ix), y(iy) {}

//Vec2���m�̋����̓��
double Vec2::distance(const Vec2& coord) const {
	return ((x - coord.x) * (x - coord.x) + (y - coord.y) * (y - coord.y));
}

//Vec2���m�̑����Z
Vec2 Vec2::operator+(const Vec2& coord) const {
	return Vec2(x + coord.x, y + coord.y);
}