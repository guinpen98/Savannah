#ifndef SAVANNAH_CREATURES_HPP
#define SAVANNAH_CREATURES_HPP
#include"configuration.h"
#include "vec2.hpp"
#include <cmath>

namespace Savannah {
	//生物クラス
	class Creatures {
	private:
		//座標
		Vec2 coord = Vec2(field_width / 2.0, field_height / 2.0);

		double spf = 0.0;

		//年齢
		double age = 0.0;
	protected:
		int one_year = 24;
		double lifespan = 5.0;

		//計測した1フレームあたりの秒数を設定する
		void setSpf(const double mi_spf);
		//経過秒数を渡す
		double getSpf()const;
		//歳をとる
		void setOld();
		//年齢を渡す
		double getAge()const;
		//画面内にいるかどうかの判定
		bool isInTheWindow(const Vec2& sub_coord)const;
		//一年が何秒かの値を渡す
		int getOneYear()const;
		//寿命の値を渡す
		double getLifespan()const;
	public:
		//座標を渡す
		Vec2 getCoord()const;
		//座標の更新
		void setCoord(const Vec2& new_coord);

		virtual void draw(int camera_x, const int camera_y, const double camera_exrate)const = 0;
	};
}

#endif // !SAVANNAH_CREATURES_HPP