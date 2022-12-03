#include "Explosion.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "Sprites.h"

namespace battleCity
{
    Explosion::Explosion(bool isLarge) : Object()
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
        drawSprite(sprite, (int)position.X, (int)position.Y);
    }

    void Explosion::step()
    {
        if (spriteIndex < 4)
        {
            spriteIndex++;
            sprite = spriteDB->at(spriteIndex);
            WM.MarkForDelete(mID);
        }
    }


    int Explosion::EventHandler(Event& eventPtr)
    {
        if (eventPtr.GetType() == EventType::Step) 
        {
	        auto& stepEvent = dynamic_cast<EventStep&>(eventPtr);
            if (stepEvent.GetStepCount() % 30 == 0)
            {
                step();
            }
            return 1;
        }
        return 0;
    }
}
