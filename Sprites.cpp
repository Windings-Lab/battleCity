#include "Sprites.h"

#include "Framework.h"
#include <regex>
#include <vector>
#include <iostream>

bool battleCity::Sprites::isCreated = false;
std::vector<std::string> battleCity::Sprites::path;

battleCity::Sprites::Sprites()
{
    tank = nullptr;
    tankPlayer = nullptr;
    bullet = nullptr;
    explosion = new std::vector<Sprite*>();

    background = nullptr;
    wall = nullptr;

    whiteFlag = nullptr;
    phoenix = nullptr;
    gameOverSpr = nullptr;

    powerUp = new std::vector<Sprite*>();
}

battleCity::Sprites& battleCity::Sprites::getInstance()
{
    static Sprites single;
    if (!isCreated)
    {
        single.path.push_back(".\\data\\Tank\\Tank*.png");             // 0
        single.path.push_back(".\\data\\Player\\TankPlayer*.png");     // 1
        single.path.push_back(".\\data\\Bullet\\bullet*.png");         // 2

        single.path.push_back(".\\data\\Explosion\\Small1.png");       // 3
        single.path.push_back(".\\data\\Explosion\\Small2.png");       // 4
        single.path.push_back(".\\data\\Explosion\\Small3.png");       // 5
        single.path.push_back(".\\data\\Explosion\\Large1.png");       // 6
        single.path.push_back(".\\data\\Explosion\\Large2.png");       // 7

        single.path.push_back(".\\data\\Logo\\Background.png");        // 8
        single.path.push_back(".\\data\\Wall.png");                    // 9

        single.path.push_back(".\\data\\PhoenixAndFlag\\Phoenix.png"); // 10
        single.path.push_back(".\\data\\PhoenixAndFlag\\Flag.png");    // 11
        single.path.push_back(".\\data\\Logo\\GameOver.png");          // 12

        single.path.push_back(".\\data\\PowerUp\\ExtraHealth.png");    // 13

        single.isCreated = true;
    }
    return single;
}

std::vector<Sprite*>& battleCity::Sprites::spriteInitDirections(std::string spritePath)
{
    std::vector<Sprite*>* spriteVec = new std::vector<Sprite*>();
    std::regex vowel_re(R"(\*)");

    spriteVec->push_back(createSprite(std::regex_replace(spritePath, vowel_re, "R").c_str()));
    spriteVec->push_back(createSprite(std::regex_replace(spritePath, vowel_re, "L").c_str()));
    spriteVec->push_back(createSprite(std::regex_replace(spritePath, vowel_re, "D").c_str()));
    spriteVec->push_back(createSprite(std::regex_replace(spritePath, vowel_re, "U").c_str()));

    if (spriteVec->at(0) == nullptr)
    {
        std::cout << "\"" << spritePath << "\" - not found/initialized" << std::endl;
        exit(0);
    }

    return *spriteVec;
}

Sprite& battleCity::Sprites::spriteInit(std::string spritePath)
{
    Sprite* newSprite = createSprite(spritePath.c_str());

    if (newSprite == nullptr)
    {
        std::cout << "\"" << spritePath << "\" - not found/initialized" << std::endl;
        exit(0);
    }

    return *newSprite;
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

std::vector<Sprite*>& battleCity::Sprites::getExplosionSprites()
{
    return *explosion;
}

Sprite& battleCity::Sprites::getBackgroundSprite()
{
    return *background;
}

Sprite& battleCity::Sprites::getWallSprite()
{
    return *wall;
}

Sprite& battleCity::Sprites::getWhiteFlagSprite()
{
    return *whiteFlag;
}

Sprite& battleCity::Sprites::getPhoenixSprite()
{
    return *phoenix;
}

Sprite& battleCity::Sprites::getGameOverSprite()
{
    return *gameOverSpr;
}

std::vector<Sprite*>& battleCity::Sprites::getPowerUpSprites()
{
    return *powerUp;
}

int battleCity::Sprites::initAll()
{
    tank = &spriteInitDirections(path[0]);
    tankPlayer = &spriteInitDirections(path[1]);
    bullet = &spriteInitDirections(path[2]);

    explosion->push_back(&spriteInit(path[3]));
    explosion->push_back(&spriteInit(path[4]));
    explosion->push_back(&spriteInit(path[5]));
    explosion->push_back(&spriteInit(path[6]));
    explosion->push_back(&spriteInit(path[7]));

    background = &spriteInit(path[8]);
    wall = &spriteInit(path[9]);

    phoenix = &spriteInit(path[10]);
    whiteFlag = &spriteInit(path[11]);
    gameOverSpr = &spriteInit(path[12]);

    powerUp->push_back(&spriteInit(path[13]));

    return 1;
}

void battleCity::Sprites::deleteAll()
{
    for (size_t i = 0; i < tank->size(); i++)
    {
        destroySprite(tank->at(i));
        tank->at(i) = nullptr;
    }
    delete tank;
    tank = nullptr;

    for (size_t i = 0; i < tankPlayer->size(); i++)
    {
        destroySprite(tankPlayer->at(i));
        tankPlayer->at(i) = nullptr;
    }
    delete tankPlayer;
    tankPlayer = nullptr;

    for (size_t i = 0; i < bullet->size(); i++)
    {
        destroySprite(bullet->at(i));
        bullet->at(i) = nullptr;
    }
    delete bullet;
    bullet = nullptr;

    for (size_t i = 0; i < explosion->size(); i++)
    {
        destroySprite(explosion->at(i));
        explosion->at(i) = nullptr;
    }
    delete explosion;
    explosion = nullptr;

    destroySprite(background);
    background = nullptr;

    destroySprite(wall);
    wall = nullptr;

    destroySprite(whiteFlag);
    whiteFlag = nullptr;

    destroySprite(phoenix);
    phoenix = nullptr;

    destroySprite(gameOverSpr);
    gameOverSpr = nullptr;

    for (size_t i = 0; i < powerUp->size(); i++)
    {
        destroySprite(powerUp->at(i));
        powerUp->at(i) = nullptr;
    }
    delete powerUp;
    powerUp = nullptr;
}

battleCity::Sprites::~Sprites()
{
}