#ifndef SAVANNAH_CREATURES_H
#define SAVANNAH_CREATURES_H
#include "vec2.h"

namespace Savannah {
	//生物クラス
	class Creatures {
	private:
		//座標
		Vec2 coord;

		//年齢
		double age = 0.0;
	protected:
		int one_year = 24;
		double lifespan = 5.0;
		class Rand* rd;
		class Time* time;

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
		Creatures(Rand*, Time*);
		//座標を渡す
		Vec2 getCoord()const;
		//座標の更新
		void setCoord(const Vec2& new_coord);
		Rand* getRd()const;
		Time* getTime()const;

		virtual void draw(int camera_x, const int camera_y, const double camera_exrate)const = 0;
	};
}

#endif // !SAVANNAH_CREATURES_H