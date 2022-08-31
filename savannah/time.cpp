#include "time.h"

namespace Savannah {
	void Time::init()
	{
		new_time = std::chrono::system_clock::now();
	}
	void Savannah::Time::update()
	{
		//1ƒtƒŒ[ƒ€‚ ‚½‚è‚ÌŠÔŒv‘ª
		old_time = new_time;
		new_time = std::chrono::system_clock::now();
		mi_spf = double(std::chrono::duration_cast<std::chrono::milliseconds>(new_time - old_time).count());
	}
	double Time::getSpf() const
	{
		return mi_spf / 1000.0;
	}
}