#pragma once
enum CreaturesE :int {
	plantE
	, herbivoreE
	, carnivoreE
};
enum HerbivoreState :int {
	herbivoreWanderE
	,herbivoreForageE
	,herbivoreBreedE
};
struct Vec2 {
	double x = 0.0, y = 0.0;

	//デフォルトコンストラクタ
	Vec2() = default;

	//コンストラクタ
	Vec2(const double ix, const double iy)
		:x(ix), y(iy) {}

};
