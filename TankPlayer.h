#pragma once

#include <string>
#include <vector>

#include "Object.h"
#include "Event.h"
#include "EventMouse.h"

class TankPlayer : public battleCity::Object
{
private:
	std::vector<std::string> movement = { "IDLE" };
public:
	TankPlayer();
	TankPlayer(float x, float y);
	~TankPlayer();

	void movementSet(std::string direction);
	void movementErase(std::string direction);

	void update() override;
	void draw() override;
	void keyboardInput();
	void mouseInput(const battleCity::EventMouse* mouseEvent);

	void move(int x, int y);
	void fire();

	virtual int eventHandler(const battleCity::Event* ptrEvent) override;
};