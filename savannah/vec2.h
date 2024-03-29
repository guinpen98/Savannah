﻿#ifndef SAVANNAH_VEC2_H
#define SAVANNAH_VEC2_H

namespace Savannah {
	//座標
	struct Vec2 {
		double x = 0.0, y = 0.0;

		//デフォルトコンストラクタ
		explicit Vec2() = default;

		//コンストラクタ
		explicit Vec2(const double ix, const double iy);

		//Vec2同士の距離の二乗
		double distanceSquared(const Vec2& coord) const;

		//Vec2同士の足し算
		Vec2 operator+(const Vec2& coord) const;
	};
}

#endif // !SAVANNAH_VEC2_H