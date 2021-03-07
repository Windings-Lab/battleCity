#include "Object.h"

bool battleCity::Object::operator==(const Object& other) noexcept
{
    //The sides of the rectangles
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    //Calculate the sides of this object
    leftA = this->position.x;
    rightA = this->position.x + this->spriteX;
    topA = this->position.y;
    bottomA = this->position.y + this->spriteY;

    //Calculate the sides of other object
    leftB = other.position.x;
    rightB = other.position.x + other.spriteX;
    topB = other.position.y;
    bottomB = other.position.y + other.spriteY;

    //If any of the sides from this object are outside of other
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from this object are outside other
	return false;
}

void battleCity::Object::spriteInit(string path)
{
    if (sprite[0] != NULL)
    {
        return;
    }

    std::regex vowel_re(R"(\*)");

    sprite[1] = std::move(createSprite(std::regex_replace(path, vowel_re, "R").c_str()));
    sprite[2] = std::move(createSprite(std::regex_replace(path, vowel_re, "L").c_str()));
    sprite[3] = std::move(createSprite(std::regex_replace(path, vowel_re, "D").c_str()));
    sprite[4] = std::move(createSprite(std::regex_replace(path, vowel_re, "U").c_str()));
    sprite[0] = sprite[4];

    getSpriteSize(sprite[0], spriteX, spriteY);
}

void battleCity::Object::spriteSet(Sprite& newSprite)
{
    sprite[0] = &newSprite;
}

battleCity::Object::~Object()
{
#if DEBUG == 2
    std::cout << "Object Destructor" << std::endl;
#endif
    for (unsigned long long i = 1; i < sprite.size(); i++)
    {
        destroySprite(sprite[i]);
        sprite[i] = NULL;
    }
    sprite[0] = NULL;
}