#include "Sprites.h"

#include "Framework.h"
#include <regex>
#include <vector>

bool battleCity::Sprites::isCreated = false;
std::string battleCity::Sprites::tankPath = "";
std::string battleCity::Sprites::tankPlayerPath = "";
std::string battleCity::Sprites::bulletPath = "";

battleCity::Sprites::Sprites()
{

}

battleCity::Sprites& battleCity::Sprites::getInstance()
{
    static Sprites single;
    if (!isCreated)
    {
        single.tankPath =       ".\\data\\Player\\TankPlayer*.png";
        single.tankPlayerPath = ".\\data\\Player\\TankPlayer*.png";
        single.bulletPath =     ".\\data\\Bullet\\bullet*.png";
        single.isCreated = true;
    }
    return single;
}

std::vector<Sprite*>& battleCity::Sprites::spriteInit(std::string spritePath)
{
    std::vector<Sprite*>* spriteVec = new std::vector<Sprite*>();
    std::regex vowel_re(R"(\*)");

    spriteVec->push_back(createSprite(std::regex_replace(spritePath, vowel_re, "R").c_str()));
    spriteVec->push_back(createSprite(std::regex_replace(spritePath, vowel_re, "L").c_str()));
    spriteVec->push_back(createSprite(std::regex_replace(spritePath, vowel_re, "D").c_str()));
    spriteVec->push_back(createSprite(std::regex_replace(spritePath, vowel_re, "U").c_str()));

    if (spriteVec->at(0) == NULL)
    {
        exit(0);
    }

    return *spriteVec;
}

std::vector<Sprite*>& battleCity::Sprites::getTankSprites()
{
    return *tank;
}

std::vector<Sprite*>& battleCity::Sprites::getTankPlayerSprites()
{
    return *tankPlayer;
}

std::vector<Sprite*>& battleCity::Sprites::getBulletSprites()
{
    return *bullet;
}

int battleCity::Sprites::initAll()
{
    tank = &spriteInit(tankPath);
    tankPlayer = &spriteInit(tankPlayerPath);
    bullet = &spriteInit(bulletPath);

    return 1;
}

void battleCity::Sprites::deleteAll()
{
    for (size_t i = 0; i < tank->size(); i++)
    {
        destroySprite(tank->at(i));
        tank->at(i) = NULL;
    }
    delete tank;

    for (size_t i = 0; i < tankPlayer->size(); i++)
    {
        destroySprite(tankPlayer->at(i));
        tankPlayer->at(i) = NULL;
    }
    delete tankPlayer;

    for (size_t i = 0; i < bullet->size(); i++)
    {
        destroySprite(bullet->at(i));
        bullet->at(i) = NULL;
    }
    delete bullet;
}

battleCity::Sprites::~Sprites()
{
}