#pragma once
#include"configuration.h"
#include <cmath>

enum CreaturesE :int {
	plantE
	, herbivoreE
	, carnivoreE
};

struct Vec2 {
	double x = 0.0, y = 0.0;

	//デフォルトコンストラクタ
	Vec2() = default;

	//コンストラクタ
	Vec2(const double ix, const double iy)
		:x(ix), y(iy) {}

};

//生物クラス
class Creatures {
protected:
	//座標
	Vec2 coord = Vec2(window_width / 2.0, window_height / 2.0);

	double spf = 0.0;
	double age = 0.0;
	int one_year = 24;// 24;
public:
	//計測した1フレームあたりの秒数を設定する
	void setSpf(const double mi_spf);
	//画面内にいるかどうかの判定
	bool isInTheWindow(const Vec2& sub_coord)const;
};

//生物クラス実装
void Creatures::setSpf(const double mi_spf) {
	spf = mi_spf / 1000.0;
}
bool Creatures::isInTheWindow(const Vec2& sub_coord)const {
	return (sub_coord.x > 0 && sub_coord.x < window_width&& sub_coord.y>0 && sub_coord.y < window_height);
}