#pragma once

#include "Object.h"
class TankPlayer : public battleCity::Object
{
private:
	vector<string> movement = { "IDLE" };

public:
	TankPlayer();
	~TankPlayer();

	void directionSet(string direction);
	void directionErase(string direction);

	void update() override;
	void draw() override;

	virtual int eventHandler(const battleCity::Event* ptrEvent) override;
};