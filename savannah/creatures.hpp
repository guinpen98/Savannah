#pragma once
#include"configuration.h"
#include <cmath>

//生物の種類
enum CreaturesE :int {
	plantE
	, herbivoreE
	, carnivoreE
};

//座標
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
private:
	//座標
	Vec2 coord = Vec2(window_width / 2.0, window_height / 2.0);
	double spf = 0.0;
	double age = 0.0;
protected:
	int one_year = 24;
	double lifespan = 5.0;
public:
	//計測した1フレームあたりの秒数を設定する
	void setSpf(const double mi_spf);
	//経過秒数を渡す
	double getSpf()const;
	//歳をとる
	void getOld();
	//年齢を渡す
	double getAge()const;
	//画面内にいるかどうかの判定
	bool isInTheWindow(const Vec2& sub_coord)const;
	//座標を渡す
	Vec2 getCoord()const;
	//座標の更新
	void setCoord(const Vec2& new_coord);
};

//生物クラス実装
void Creatures::setSpf(const double mi_spf) {
	spf = mi_spf / 1000.0;
}
double Creatures::getSpf() const{
	return spf;
}
void Creatures::getOld() {
	age += spf;
}
double Creatures::getAge()const {
	return age;
}
bool Creatures::isInTheWindow(const Vec2& sub_coord)const {
	return (sub_coord.x > 0 && sub_coord.x < window_width&& sub_coord.y>0 && sub_coord.y < window_height);
}
Vec2 Creatures::getCoord() const{
	return coord;
}
void Creatures::setCoord(const Vec2& new_coord) {
	coord = Vec2(new_coord);
}