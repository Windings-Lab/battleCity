#include "Explosion.h"
#include "EventStep.h"
#include "Sprites.h"
#include "WorldManager.h"

namespace battleCity
{
    Explosion::Explosion(bool isLarge) : Object()
    {
        mType = Type::Explosion;

        mHealth = isLarge ? 1 : 3;
        spriteIndex = isLarge ? 3 : 0;
        mConstSpeed = 0;
        mBulletCount = 0;
        mSolidness = Solidness::Spectral;

        spriteDB = &SPR.getExplosionSprites();
        mSprite = spriteDB->at(spriteIndex);

        initPosition(Vector(40, 44));
    }

    void Explosion::Draw()
    {
        drawSprite(mSprite, (int)mPosition.X, (int)mPosition.Y);
    }

    void Explosion::step()
    {
        if (spriteIndex < 4)
        {
            spriteIndex++;
            mSprite = spriteDB->at(spriteIndex);
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
