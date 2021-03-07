#pragma once

#include "Framework.h"

class Clock
{
private:
	unsigned int previousTime;
	unsigned int adjustTime = 0;
	unsigned int actualSleepTime = 0;
	unsigned int intendedSleepTime = 0;

public:
	// Sets previous_time to current time
	Clock();
	~Clock();

	// Return time elapsed since delta() was called
	// Resets clock time
	// Units are milliseconds
	void delta();

	// Return time elapsed since delta() was called
	// Does not reset clock time
	// Units are milliseconds
	unsigned int split() const;

	void sleep(unsigned int loopTime);
};