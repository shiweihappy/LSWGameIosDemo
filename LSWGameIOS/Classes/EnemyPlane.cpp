//
//  EnemyPlane.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-20.
//
//

#include "EnemyPlane.h"

USING_NS_CC;

EnemyPlane::EnemyPlane()
:nlife(0),
maxLife(0),
maxScore(0)
{
    
}

EnemyPlane::~EnemyPlane()
{
    
}

bool EnemyPlane::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    return true;
}

EnemyPlane *EnemyPlane::createEnemy(enemyType type)
{
    EnemyPlane *plane = new EnemyPlane();
    if (plane && plane->initEnemyPlaneByType(type))
    {
        plane->autorelease();
        return plane;
    }
    return nullptr;
}

bool EnemyPlane::initEnemyPlaneByType(enemyType type)
{
    Sprite *pEnemyPlane = nullptr;
    switch (type) {
        case Enemy1:
            pEnemyPlane = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("n1.png"));
            nlife = ENEMY1_MAXLIFE;
            maxLife = ENEMY1_MAXLIFE;
            maxScore = ENEMY1_MAXSCORE;
            break;
        case Enemy2:
            pEnemyPlane = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("n2.png"));
            nlife = ENEMY2_MAXLIFE;
            maxLife = ENEMY2_MAXLIFE;
            maxScore = ENEMY2_MAXSCORE;
            break;
        case Enemy3:
            pEnemyPlane = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("n3.png"));
            nlife = ENEMY2_MAXLIFE;
            maxLife = ENEMY2_MAXLIFE;
            maxScore = ENEMY2_MAXSCORE;
            break;
        case Enemy4:
            pEnemyPlane = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("n_boss.png"));
            nlife = ENEMY3_MAXLIFE;
            maxLife = ENEMY3_MAXLIFE;
            maxScore = ENEMY3_MAXSCORE;
            break;
        default:
            pEnemyPlane = nullptr;
            nlife = 0;
            maxLife = 0;
            maxScore = 0;
            break;
    }
    
    if (pEnemyPlane)
    {
        addChild(pEnemyPlane);
        return true;
    }
    
    return false;
}

int EnemyPlane::getLife()
{
    return nlife;
}

void EnemyPlane::loseLife()
{
    nlife--;
}

void EnemyPlane::increaseLife(int life)
{
    nlife += life;
    if (nlife > maxLife)
    {
        nlife = maxLife;
    }
}

int EnemyPlane::getScore()
{
    return maxScore;
}

bool EnemyPlane::isDie()
{
    if (getLife() <= 0)
    {
        return true;
    }
    return false;
}

Rect EnemyPlane::getBoundingBox()
{
    return this->getBoundingBox();
}


