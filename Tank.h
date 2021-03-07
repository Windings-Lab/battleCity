#pragma once

#include "Object.h"

class Tank : public battleCity::Object
{
public:
	Tank();
	~Tank();

	virtual inline void update() override;
	virtual inline void draw() override;

	virtual int eventHandler(const battleCity::Event* ptrEvent) override;
};