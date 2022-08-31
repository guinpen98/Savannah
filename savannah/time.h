#ifndef SAVANNAH_TIME_H
#define SAVANNAH_TIME_H
#include <chrono>
namespace Savannah {
	class Time
	{
	private:
		std::chrono::system_clock::time_point old_time;
		std::chrono::system_clock::time_point new_time;
		double mi_spf=0;
	public:
		void init();
		void update();
		double getSpf()const;
	};
}
#endif // !SAVANNAH_TIME_H



