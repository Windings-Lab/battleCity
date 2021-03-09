#pragma once

#include "Object.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "WorldManager.h"

class TankPlayer : public battleCity::Object
{
private:
	vector<string> movement = { "IDLE" };
public:
	TankPlayer();
	~TankPlayer();

	void movementSet(string direction);
	void movementErase(string direction);

	void update() override;
	void draw() override;
	void keyboardInput();

	void move(int x, int y);

	virtual int eventHandler(const battleCity::Event* ptrEvent) override;
};