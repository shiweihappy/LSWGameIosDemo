//
//  LSWProgressTimer.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-28.
//
//

#include "LSWProgressTimer.h"

USING_NS_CC;

bool LSWProgressTimer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    auto s = Sprite::create("yellowNum.png");

    auto center = Vec2(winSize.width/2, winSize.height/2);
    
    auto progressTimer = ProgressTimer::create(s);
    addChild(progressTimer);
    progressTimer->setPosition(center);
    progressTimer->setTag(100);
    progressTimer->setType(ProgressTimer::Type::BAR);
    progressTimer->setBarChangeRate(Vec2(1, 0));
    progressTimer->setMidpoint(Vec2(0, 0));
//    progressTimer->setPercentage(50);

//    schedule(schedule_selector(LSWProgressTimer::scheduleProgressTimer), 0.5f);

//    progressTimer->runAction(ProgressTo::create(2.0f, 100));
    
    return true;
}

Scene *LSWProgressTimer::createScene()
{
    auto scene = Scene::create();
    auto layer = LSWProgressTimer::create();
    scene->addChild(layer);
    return scene;
}

void LSWProgressTimer::scheduleProgressTimer(float dt)
{
    auto progressTimer = (ProgressTimer *)getChildByTag(100);
    progressTimer->setPercentage(progressTimer->getPercentage() + 10);
    if (progressTimer->getPercentage() >= 100)
    {
        unscheduleAllSelectors();
    }
}