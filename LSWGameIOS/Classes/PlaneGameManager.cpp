//
//  PlaneGameManager.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-20.
//
//

#include "PlaneGameManager.h"
#include "EnemyPlane.h"
#include "Bullet.h"
#include "HeroPlane.h"
#include "HeroPet.h"

USING_NS_CC;

static PlaneGameManager *_instance = nullptr;

PlaneGameManager::PlaneGameManager()
:_heroPet(nullptr)
,_heroPlane(nullptr)
{
    
}

PlaneGameManager::~PlaneGameManager()
{
    
}

PlaneGameManager *PlaneGameManager::getInstance()
{
    if (_instance)
    {
        _instance = new PlaneGameManager();
    }
    return _instance;
}

HeroPlane *PlaneGameManager::createHeroPlane()
{
    _heroPlane = HeroPlane::create();
    return _heroPlane;
}

HeroPet *PlaneGameManager::createHeroPet()
{
    _heroPet = HeroPet::createHeroPet();
    _heroPet->petAnimation();
    return _heroPet;
}

void PlaneGameManager::createEnemyPlane()
{
    
}

void PlaneGameManager::createBullets()
{
    
}

void PlaneGameManager::update(float dt)
{
    
}

bool PlaneGameManager::checkTouchPlane(Vec2 &loc)
{
    if (!_heroPlane)
    {
        return false;
    }
    return _heroPlane->getBoundingBox().containsPoint(loc);
}

void PlaneGameManager::moveHeroPlane(Vec2 &loc)
{
    if (!_heroPlane)
    {
        return;
    }
    
    _heroPlane->setPosition(loc);
    _heroPet->setPosition(_heroPlane->getPosition());
}

void PlaneGameManager::onTouchMoved(Vec2 &loc)
{
    moveHeroPlane(loc);
}





