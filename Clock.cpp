#include "Clock.h"
#include "Framework.h"

#include <thread>
#include <chrono>
#include <iostream>

Clock::Clock() : previousTime(getTickCount())
{

}

Clock::~Clock()
{
#if DEBUG == 2
	std::cout << "Clock Destructor" << std::endl;
#endif
}

void Clock::delta()
{
	previousTime = getTickCount();
}

int Clock::split() const
{
	return getTickCount() - previousTime;
}

void Clock::sleep(int loopTime)
{
	intendedSleepTime = FPS - loopTime - adjustTime;

	delta();
	std::this_thread::sleep_for(std::chrono::milliseconds(intendedSleepTime));
	actualSleepTime = split();



	adjustTime = actualSleepTime - intendedSleepTime;
	if (adjustTime < 0)
		adjustTime = 0;
}
