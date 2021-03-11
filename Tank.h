#pragma once

#include "Object.h"
#include "Event.h"

class Tank : public battleCity::Object
{
private:
	int change;
public:
	Tank();
	Tank(float x, float y);
	~Tank();

	virtual inline void update() override;
	virtual inline void draw() override;

	virtual int eventHandler(const battleCity::Event* eventPtr) override;
};
