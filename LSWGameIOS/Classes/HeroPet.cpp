//
//  HeroPet.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-20.
//
//

#include "HeroPet.h"

USING_NS_CC;

HeroPet::HeroPet()
{
    
}

HeroPet::~HeroPet()
{
    
}

HeroPet *HeroPet::createHeroPet()
{
    auto heroPet = new HeroPet();
    if (heroPet && heroPet->initHeroPet())
    {
        heroPet->autorelease();
        return heroPet;
    }
    
    return nullptr;
}

bool HeroPet::initHeroPet()
{
    if (!Sprite::init())
    {
        return false;
    }
    
    _pet = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_01.png"));
    _pet->setScale(0.6);
    return true;
}

Sprite *HeroPet::getPet()
{
    return _pet;
}

void HeroPet::petAnimation()
{
    char buff[16];
    Vector<SpriteFrame *> frames;
    for (auto i = 1; i<=6; i++)
    {
        sprintf(buff, "hero_0%d.png", i);
        frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(buff));
    }
    
    Animation *pAnimation = Animation::createWithSpriteFrames(frames, 0.1f);
    getPet()->runAction(RepeatForever::create(Animate::create(pAnimation)));
}

void HeroPet::petFollowHero(cocos2d::Vec2 pos)
{
    auto winSize = Director::getInstance()->getWinSize();
    if (pos.x + 60 + getPet()->getContentSize().width < winSize.width)
    {
        getPet()->setPosition(Vec2(pos.x + 60 + getPet()->getContentSize().width, pos.y));
    }
    else
    {
        getPet()->setPosition(Vec2(pos.x - 60 - getPet()->getContentSize().width, pos.y));
    }
}
