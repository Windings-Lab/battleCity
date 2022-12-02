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

    Object::Object()
    {
        mType = Type::Error;

        health = 1;
        constSpeed = 0;
        bulletCount = 1;
        solidness = Solidness::Hard;
        isSpawnIntersects = true;

        initPosition(Vector(40, 44));

        mID = IDCounter++;
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
        if (sight.x == 1)
        {
            //std::cout << "WorldManager - getCollisions - 294" << std::endl;
            worldIndexRelative.x = (int)(((position.x - SCR.getBoundaryL()) / 16) + spriteIndexSize);
            if (worldIndexRelative.x >= WIDTH)
                worldIndexRelative.x = WIDTH - 1;
            worldIndexRelative.y = (int)(((position.y - SCR.getBoundaryU()) / 16));
            for (int i = 0; i < spriteIndexSize; i++)
            {
                if (WM.GetWorldMap()[(int)worldIndexRelative.y][(int)worldIndexRelative.x] == nullptr)
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
                if (WM.GetWorldMap()[(int)worldIndexRelative.y][(int)worldIndexRelative.x] == nullptr)
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
                if (WM.GetWorldMap()[(int)worldIndexRelative.y][(int)worldIndexRelative.x] == nullptr)
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
                if (WM.GetWorldMap()[(int)worldIndexRelative.y][(int)worldIndexRelative.x] == nullptr)
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
        newDirection.x = newDirection.x > 0 ? 1 : (newDirection.x < 0 ? -1 : 0);
        newDirection.y = newDirection.y > 0 ? 1 : (newDirection.y < 0 ? -1 : 0);
        direction = Vector(newDirection.x, newDirection.y);
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
        if (!(newSight.x == 0 && newSight.y == 0))
            sight = newSight;
    }

    void Object::setVelocity(Vector newVelocity)
    {
        setDirection(Vector(newVelocity.x, newVelocity.y));
        setSpeed(newVelocity.x == 0 ? newVelocity.y : newVelocity.x);
    }

    Vector Object::getVelocity() const
    {
        return Vector(direction.x == 0 ? 0 : speed, direction.y == 0 ? 0 : speed);
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
        if (initPosition.x < SCR.getBoundaryL() || initPosition.x > SCR.getBoundaryR())
        {
            position.x = SCR.getBoundaryL();
        }
        if (initPosition.y < SCR.getBoundaryU() || initPosition.y > SCR.getBoundaryD())
        {
            position.y = SCR.getBoundaryU();
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
        WM.RemoveObject(this);
        spriteDB = nullptr;
        sprite = nullptr;
    }
}