#include "Object.h"
#include "WorldManager.h"
#include "Vector.h"
#include "Box.h"
#include "Framework.h"
#include "Screen.h"
#include "Sprites.h"

#include <regex>
#include <string>
#include <iostream>

battleCity::Object::Object() : id(0), speed(0), sprite(SPR.getTankSprites())
{
    spriteSet(3);
    sight.y = -1;
    getSpriteSize(spriteDirection, spriteX, spriteY);
    box = Box(Vector(), spriteX, spriteY);
    position.x = SCR.getBoundaryL();
    position.y = SCR.getBoundaryU();
    isDeleted = false;
    solidness = Solidness::HARD;
    WM.insertObject(this);
}

std::string battleCity::Object::getType()
{
    return type;
}

bool battleCity::Object::objectIsDeleted() const
{
    return isDeleted;
}

std::vector<Sprite*>& battleCity::Object::getSpriteList()
{
    return sprite;
}

int battleCity::Object::getSpriteX() const
{
    return spriteX;
}

int battleCity::Object::getSpriteY() const
{
    return spriteY;
}

void battleCity::Object::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

float battleCity::Object::getSpeed() const
{
    return speed;
}

void battleCity::Object::setDirection(Vector newDirection)
{
    newDirection.x = newDirection.x > 0 ? 1 : (newDirection.x < 0 ? -1 : 0);
    newDirection.y = newDirection.y > 0 ? 1 : (newDirection.y < 0 ? -1 : 0);
    direction = Vector(newDirection.x, newDirection.y);
}

battleCity::Vector battleCity::Object::getDirection() const
{
    return direction;
}

battleCity::Vector battleCity::Object::getSight() const
{
    return sight;
}

void battleCity::Object::setVelocity(Vector newVelocity)
{
    setDirection(Vector(newVelocity.x, newVelocity.y));
    setSpeed(newVelocity.x == 0 ? newVelocity.y : newVelocity.x);
}

battleCity::Vector battleCity::Object::getVelocity() const
{
    return Vector(direction.x == 0 ? 0 : speed, direction.y == 0 ? 0 : speed);
}

battleCity::Vector battleCity::Object::predictPosition()
{
    Vector newPos = position + getVelocity();
    return newPos;
}

int battleCity::Object::setPosition(Vector newPosition)
{
    position = newPosition;
    return 0;
}

battleCity::Vector battleCity::Object::getPosition() const
{
    return position;
}

bool battleCity::Object::isSolid() const
{
    if (solidness == Solidness::SPECTRAL)
    {
        return 0;
    }
    return solidness == Solidness::HARD ? 1 : 0;
}

int battleCity::Object::setSolidness(Solidness newSolid)
{
    solidness = newSolid;
    return 0;
}

battleCity::Solidness battleCity::Object::getSolidness() const
{
    return solidness;
}

void battleCity::Object::setBox(Box newBox)
{
    box = newBox;
}

battleCity::Box battleCity::Object::getBox() const
{
    return box;
}

void battleCity::Object::spriteSet(int index)
{
    spriteDirection = sprite[index];
}

battleCity::Object::~Object()
{
#if DEBUG == 2
    std::cout << "Object Destructor" << std::endl;
#endif

    isDeleted = true;
    WM.removeObject(this);
    spriteDirection = NULL;
}