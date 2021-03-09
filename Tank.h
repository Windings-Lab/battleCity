#pragma once

#include "Object.h"

class Tank : public battleCity::Object
{
private:
	int change;
public:
	Tank();
	Tank(int x, int y);
	~Tank();

	virtual inline void update() override;
	virtual inline void draw() override;

	virtual int eventHandler(const battleCity::Event* eventPtr) override;
};
