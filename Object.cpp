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

battleCity::Object::Object() : worldID(WM.getWorldID()), moveID(WM.getMoveID())
{
    id = 0;
    type = "";

    health = 1;
    constSpeed = 0;
    bulletCount = 1;
    solidness = Solidness::HARD;
    isSpawnIntersects = true;

    initPosition(Vector(40, 44));

    WM.insertObject(this);
}

/// <summary>
/// Object default values
/// </summary>
/// <param name="id">0</param>
/// <param name="type">""</param>
/// <param name="position.x">SCR.getBoundaryL()</param>
/// <param name="position.y">SCR.getBoundaryU()</param>
/// <param name="health">1</param>
/// <param name="constSpeed">0</param>
/// <param name="bulletCount">1</param>
/// <param name="solidness">Solidness::HARD</param>
battleCity::Object::Object(int newMoveID) : worldID(WM.getWorldID()), moveID(newMoveID)
{
    id = 0;
    type = "";

    health = 1;
    constSpeed = 0;
    bulletCount = 1;
    solidness = Solidness::HARD;
    isSpawnIntersects = true;

    initPosition(Vector(40, 44));

    WM.insertObject(this);
}

std::string battleCity::Object::getType() const
{
    return type;
}

std::vector<Sprite*>& battleCity::Object::getSpriteList()
{
    return *spriteDB;
}

int battleCity::Object::eventHandler(const Event* ptrEvent)
{
    return 0;
}

int battleCity::Object::getSpriteX() const
{
    return spriteX;
}

int battleCity::Object::getSpriteY() const
{
    return spriteY;
}

int battleCity::Object::getSpriteIndexSize() const
{
    return spriteIndexSize;
}

int battleCity::Object::getID() const
{
    return id;
}

int battleCity::Object::getWorldID() const
{
    return worldID;
}

int battleCity::Object::getWorldMoveID() const
{
    return moveID;
}

void battleCity::Object::setWorldIndexRelative()
{
    if (sight.x == 1)
    {
        //std::cout << "WorldManager - getCollisions - 294" << std::endl;
        worldIndexRelative.x = (int)(((position.x - SCR.getBoundaryL()) / 16) + spriteIndexSize);
        if (worldIndexRelative.x >= WIDTH)
            worldIndexRelative.x = WIDTH - 1;
        worldIndexRelative.y = (int)(((position.y - SCR.getBoundaryU()) / 16));
        for (int i = 0; i < spriteIndexSize; i++)
        {
            if (WM.getWorldMap()[(int)worldIndexRelative.y][(int)worldIndexRelative.x] == nullptr)
            {
                worldIndexRelative.y++;
                if (worldIndexRelative.y >= HEIGHT)
                    worldIndexRelative.y = HEIGHT - 1;
            }
            else
            {
                break;
            }
        }
    }
    else if (sight.x == -1)
    {
        //std::cout << "WorldManager - getCollisions - 313" << std::endl;
        worldIndexRelative.x = (int)(((position.x - SCR.getBoundaryL()) / 16) - 1);
        if (worldIndexRelative.x < 0)
            worldIndexRelative.x = 0;
        worldIndexRelative.y = (int)((position.y - SCR.getBoundaryU()) / 16);
        for (int i = 0; i < spriteIndexSize; i++)
        {
            if (WM.getWorldMap()[(int)worldIndexRelative.y][(int)worldIndexRelative.x] == nullptr)
            {
                worldIndexRelative.y++;
                if (worldIndexRelative.y >= HEIGHT)
                    worldIndexRelative.y = HEIGHT - 1;
            }
            else
            {
                break;
            }
        }
    }
    else if (sight.y == 1)
    {
        /*std::cout << "WorldManager - getCollisions - 332" << std::endl;*/
        worldIndexRelative.x = (int)((position.x - SCR.getBoundaryL()) / 16);
        worldIndexRelative.y = (int)(((position.y - SCR.getBoundaryU()) / 16) + spriteIndexSize);
        if (worldIndexRelative.y >= HEIGHT)
            worldIndexRelative.y = HEIGHT - 1;
        for (int i = 0; i < spriteIndexSize; i++)
        {
            if (WM.getWorldMap()[(int)worldIndexRelative.y][(int)worldIndexRelative.x] == nullptr)
            {
                worldIndexRelative.x++;
                if (worldIndexRelative.x >= WIDTH)
                    worldIndexRelative.x = WIDTH - 1;
            }
            else
            {
                break;
            }
        }
    }
    else if (sight.y == -1)
    {
        //std::cout << "WorldManager - getCollisions - 351" << std::endl;
        worldIndexRelative.x = (int)((position.x - SCR.getBoundaryL()) / 16);
        worldIndexRelative.y = (int)(((position.y - SCR.getBoundaryU()) / 16) - 1);
        if (worldIndexRelative.y < 0)
            worldIndexRelative.y = 0;
        for (int i = 0; i < spriteIndexSize; i++)
        {
            if (WM.getWorldMap()[(int)worldIndexRelative.y][(int)worldIndexRelative.x] == nullptr)
            {
                worldIndexRelative.x++;
                if (worldIndexRelative.x >= WIDTH)
                    worldIndexRelative.x = WIDTH - 1;
            }
            else
            {
                break;
            }
        }
    }
}

battleCity::Vector battleCity::Object::getWorldIndexRelative() const
{
    return worldIndexRelative;
}

void battleCity::Object::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

float battleCity::Object::getSpeed() const
{
    return speed;
}

// Health += newHealth
void battleCity::Object::setHealth(int newHealth)
{
    health += newHealth;
}

int battleCity::Object::getHealth() const
{
    return health;
}

void battleCity::Object::setBulletCount(int newBulletCount)
{
    bulletCount += newBulletCount;
}

int battleCity::Object::getBulletCount()
{
    return bulletCount;
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

void battleCity::Object::setSight(Vector newSight)
{
    if(!(newSight.x == 0 && newSight.y == 0))
        sight = newSight;
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
    setWorldIndexRelative();
    return newPos;
}

int battleCity::Object::setPosition(Vector newPosition)
{
    position = newPosition;
    return 0;
}

void battleCity::Object::initPosition(Vector initPosition)
{
    position = initPosition;
    if (initPosition.x < SCR.getBoundaryL() || initPosition.x > SCR.getBoundaryR())
    {
        position.x = SCR.getBoundaryL();
    }
    if (initPosition.y < SCR.getBoundaryU() || initPosition.y > SCR.getBoundaryD())
    {
        position.y = SCR.getBoundaryU();
    }
}

battleCity::Vector battleCity::Object::getPosition() const
{
    return position;
}

bool battleCity::Object::isSolid() const
{
    return solidness == Solidness::HARD ? 1 : 0;
}

bool battleCity::Object::isSoft() const
{
    return solidness == Solidness::SOFT ? 1 : 0;
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

bool battleCity::Object::getSpawnIntersection()
{
    return isSpawnIntersects;
}

void battleCity::Object::setSpawnIntersection(bool newSpawnIntersection)
{
    isSpawnIntersects = newSpawnIntersection;
}

void battleCity::Object::spriteSet(Sprite* newSprite, int index)
{
    if (spriteDB == nullptr)
    {
        sprite = newSprite;
    }
    else
    {
        sprite = spriteDB->at(index);
    }
    getSpriteSize(sprite, spriteX, spriteY);
    box = Box(Vector(), spriteX, spriteY);
    spriteIndexSize = (spriteX / 16) + 1;
    newSprite = nullptr;
}

void battleCity::Object::update()
{
}

void battleCity::Object::draw()
{
}

battleCity::Object::~Object()
{
#if DEBUG == 2
    std::cout << "Object Destructor" << std::endl;
#endif
    WM.removeObject(this);
    spriteDB = nullptr;
    sprite = nullptr;
}