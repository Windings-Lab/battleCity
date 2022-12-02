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

namespace battleCity
{
    int Object::IDCounter = 1;

    Object::Object() : mID(IDCounter++)
    {
        mType = Type::Error;

        health = 1;
        constSpeed = 0;
        bulletCount = 1;
        solidness = Solidness::Hard;
        isSpawnIntersects = true;

        initPosition(Vector(40, 44));
    }

    std::vector<Sprite*>& Object::getSpriteList()
    {
        return *spriteDB;
    }

    int Object::eventHandler(const Event* ptrEvent)
    {
        return 0;
    }

    int Object::getSpriteX() const
    {
        return spriteX;
    }

    int Object::getSpriteY() const
    {
        return spriteY;
    }

    int Object::getSpriteIndexSize() const
    {
        return spriteIndexSize;
    }

    int Object::GetID() const
    {
        return mID;
    }

    Object::Type Object::getType() const
    {
        return mType;
    }

    void Object::setWorldIndexRelative()
    {
        if (sight.X == 1)
        {
            //std::cout << "WorldManager - getCollisions - 294" << std::endl;
            worldIndexRelative.X = (int)(((position.X - SCR.getBoundaryL()) / 16) + spriteIndexSize);
            if (worldIndexRelative.X >= WIDTH)
                worldIndexRelative.X = WIDTH - 1;
            worldIndexRelative.Y = (int)(((position.Y - SCR.getBoundaryU()) / 16));
            for (int i = 0; i < spriteIndexSize; i++)
            {
                if (WM.GetWorldMap()[(int)worldIndexRelative.Y][(int)worldIndexRelative.X] == 0)
                {
                    worldIndexRelative.Y++;
                    if (worldIndexRelative.Y >= HEIGHT)
                        worldIndexRelative.Y = HEIGHT - 1;
                }
                else
                {
                    break;
                }
            }
        }
        else if (sight.X == -1)
        {
            //std::cout << "WorldManager - getCollisions - 313" << std::endl;
            worldIndexRelative.X = (int)(((position.X - SCR.getBoundaryL()) / 16) - 1);
            if (worldIndexRelative.X < 0)
                worldIndexRelative.X = 0;
            worldIndexRelative.Y = (int)((position.Y - SCR.getBoundaryU()) / 16);
            for (int i = 0; i < spriteIndexSize; i++)
            {
                if (WM.GetWorldMap()[(int)worldIndexRelative.Y][(int)worldIndexRelative.X] == 0)
                {
                    worldIndexRelative.Y++;
                    if (worldIndexRelative.Y >= HEIGHT)
                        worldIndexRelative.Y = HEIGHT - 1;
                }
                else
                {
                    break;
                }
            }
        }
        else if (sight.Y == 1)
        {
            /*std::cout << "WorldManager - getCollisions - 332" << std::endl;*/
            worldIndexRelative.X = (int)((position.X - SCR.getBoundaryL()) / 16);
            worldIndexRelative.Y = (int)(((position.Y - SCR.getBoundaryU()) / 16) + spriteIndexSize);
            if (worldIndexRelative.Y >= HEIGHT)
                worldIndexRelative.Y = HEIGHT - 1;
            for (int i = 0; i < spriteIndexSize; i++)
            {
                if (WM.GetWorldMap()[(int)worldIndexRelative.Y][(int)worldIndexRelative.X] == 0)
                {
                    worldIndexRelative.X++;
                    if (worldIndexRelative.X >= WIDTH)
                        worldIndexRelative.X = WIDTH - 1;
                }
                else
                {
                    break;
                }
            }
        }
        else if (sight.Y == -1)
        {
            //std::cout << "WorldManager - getCollisions - 351" << std::endl;
            worldIndexRelative.X = (int)((position.X - SCR.getBoundaryL()) / 16);
            worldIndexRelative.Y = (int)(((position.Y - SCR.getBoundaryU()) / 16) - 1);
            if (worldIndexRelative.Y < 0)
                worldIndexRelative.Y = 0;
            for (int i = 0; i < spriteIndexSize; i++)
            {
                if (WM.GetWorldMap()[(int)worldIndexRelative.Y][(int)worldIndexRelative.X] == 0)
                {
                    worldIndexRelative.X++;
                    if (worldIndexRelative.X >= WIDTH)
                        worldIndexRelative.X = WIDTH - 1;
                }
                else
                {
                    break;
                }
            }
        }
    }

    Vector Object::getWorldIndexRelative() const
    {
        return worldIndexRelative;
    }

    void Object::setSpeed(float newSpeed)
    {
        speed = newSpeed;
    }

    float Object::getSpeed() const
    {
        return speed;
    }

    // Health += newHealth
    void Object::setHealth(int newHealth)
    {
        health += newHealth;
    }

    int Object::getHealth() const
    {
        return health;
    }

    void Object::setBulletCount(int newBulletCount)
    {
        bulletCount += newBulletCount;
    }

    int Object::getBulletCount()
    {
        return bulletCount;
    }

    void Object::setDirection(Vector newDirection)
    {
        newDirection.X = newDirection.X > 0 ? 1 : (newDirection.X < 0 ? -1 : 0);
        newDirection.Y = newDirection.Y > 0 ? 1 : (newDirection.Y < 0 ? -1 : 0);
        direction = Vector(newDirection.X, newDirection.Y);
    }

    Vector Object::getDirection() const
    {
        return direction;
    }

    Vector Object::getSight() const
    {
        return sight;
    }

    void Object::setSight(Vector newSight)
    {
        if (!(newSight.X == 0 && newSight.Y == 0))
            sight = newSight;
    }

    void Object::setVelocity(Vector newVelocity)
    {
        setDirection(Vector(newVelocity.X, newVelocity.Y));
        setSpeed(newVelocity.X == 0 ? newVelocity.Y : newVelocity.X);
    }

    Vector Object::getVelocity() const
    {
        return Vector(direction.X == 0 ? 0 : speed, direction.Y == 0 ? 0 : speed);
    }

    Vector Object::predictPosition()
    {
        Vector newPos = position + getVelocity();
        setWorldIndexRelative();
        return newPos;
    }

    int Object::setPosition(Vector newPosition)
    {
        position = newPosition;
        return 0;
    }

    void Object::initPosition(Vector initPosition)
    {
        position = initPosition;
        if (initPosition.X < SCR.getBoundaryL() || initPosition.X > SCR.getBoundaryR())
        {
            position.X = SCR.getBoundaryL();
        }
        if (initPosition.Y < SCR.getBoundaryU() || initPosition.Y > SCR.getBoundaryD())
        {
            position.Y = SCR.getBoundaryU();
        }
    }

    Vector Object::getPosition() const
    {
        return position;
    }

    bool Object::isSolid() const
    {
        return solidness == Solidness::Hard;
    }

    bool Object::isSoft() const
    {
        return solidness == Solidness::Soft;
    }

    int Object::setSolidness(Solidness newSolid)
    {
        solidness = newSolid;
        return 0;
    }

    Object::Solidness Object::getSolidness() const
    {
        return solidness;
    }

    void Object::setBox(Box newBox)
    {
        box = newBox;
    }

    Box Object::getBox() const
    {
        return box;
    }

    bool Object::getSpawnIntersection()
    {
        return isSpawnIntersects;
    }

    void Object::setSpawnIntersection(bool newSpawnIntersection)
    {
        isSpawnIntersects = newSpawnIntersection;
    }

    bool Object::IsMovable() const
    {
        return isMovable;
    }

    void Object::spriteSet(Sprite* newSprite, int index)
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

    void Object::update()
    {
    }

    void Object::draw()
    {
    }

    Object::~Object()
    {
#if DEBUG == 2
        std::cout << "Object Destructor" << std::endl;
#endif
        spriteDB = nullptr;
        sprite = nullptr;
    }
}