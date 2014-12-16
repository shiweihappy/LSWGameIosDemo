//
//  HeroPlane.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-20.
//
//

#include "HeroPlane.h"

USING_NS_CC;

HeroPlane::HeroPlane()
:_life(0)
{
    
}

HeroPlane::~HeroPlane()
{
    
}

bool HeroPlane::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    
    auto heroPlane = Sprite::create("plane/mplane.png");
    heroPlane->setScale(0.7f);
    addChild(heroPlane);
    _life = 10;
    
    return true;
}

bool HeroPlane::isDie()
{
    if (getLife() <= 0)
    {
        return true;
    }
    return false;
}

void HeroPlane::loseLife()
{
    _life--;
}

int HeroPlane::getLife()
{
    return _life;
}


