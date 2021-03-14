#pragma once

class Clock
{
private:
	int previousTime;
	int adjustTime = 0;
	int actualSleepTime = 0;
	int intendedSleepTime = 0;

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
	int split() const;

	void sleep(int loopTime);
};