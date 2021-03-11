#include "EventStep.h"
#include "GameManager.h"

battleCity::EventStep::EventStep() : stepCount(GM.stepCount)
{
	setType(STEP_EVENT);
}

battleCity::EventStep::EventStep(unsigned int init) : stepCount(init) {}

void battleCity::EventStep::setStepCount(unsigned int newStep)
{
	stepCount = newStep;
}

int battleCity::EventStep::getStepCount() const
{
	return stepCount;
}

battleCity::EventStep::~EventStep()
{
//#if DEBUG == 2
//	std::cout << "EventStep Destructor" << std::endl;
//#endif
}