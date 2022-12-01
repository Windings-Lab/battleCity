#include "Explosion.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "Sprites.h"

namespace battleCity
{
    Explosion::Explosion(bool isLarge) : Object(0)
    {
        mType = Type::Explosion;

        health = isLarge ? 1 : 3;
        spriteIndex = isLarge ? 3 : 0;
        constSpeed = 0;
        bulletCount = 0;
        solidness = Solidness::Spectral;

        spriteDB = &SPR.getExplosionSprites();
        sprite = spriteDB->at(spriteIndex);

        initPosition(Vector(40, 44));
    }

    void Explosion::draw()
    {
        drawSprite(sprite, (int)position.x, (int)position.y);
    }

    void Explosion::step()
    {
        if (spriteIndex < 4)
        {
            spriteIndex++;
            sprite = spriteDB->at(spriteIndex);
            WM.markForDelete(this);
        }
    }


    int Explosion::eventHandler(const Event* eventPtr)
    {
        if (eventPtr->GetType() == EventType::Step) {
            const EventStep* stepEvent = dynamic_cast <const EventStep*> (eventPtr);
            if (stepEvent->getStepCount() % 30 == 0)
            {
                step();
            }
            return 1;
        }
        return 0;
    }
}