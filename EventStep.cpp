#include "EventStep.h"

battleCity::EventStep::EventStep() : stepCount(0) {}

battleCity::EventStep::~EventStep()
{
#if DEBUG == 2
	std::cout << "EventStep Destructor" << std::endl;
#endif
}

battleCity::EventStep::EventStep(int init) : stepCount(init) {}

void battleCity::EventStep::setStepCount(int newStep) 
{
	stepCount = newStep;
}

int battleCity::EventStep::getStepCount() const
{
	return stepCount;
}
