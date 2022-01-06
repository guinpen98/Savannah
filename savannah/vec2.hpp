#ifndef SAVANNAH_VEC2_HPP
#define SAVANNAH_VEC2_HPP

//���W
struct Vec2 {
	double x = 0.0, y = 0.0;

	//�f�t�H���g�R���X�g���N�^
	Vec2() = default;

	//�R���X�g���N�^
	Vec2(const double ix, const double iy);

	//Vec2���m�̋����̓��
	double distance(const Vec2& coord) const;

	//Vec2���m�̑����Z
	Vec2 operator+(const Vec2& coord) const;
};

#endif // !SAVANNAH_VEC2_HPP