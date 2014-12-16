//
//  OvalAction.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-27.
//
//

#include "OvalAction.h"

USING_NS_CC;

MoveOvalBy::MoveOvalBy()
{
    
}

MoveOvalBy::~MoveOvalBy()
{
    
}

MoveOvalBy *MoveOvalBy::create(float dt, const OvalConfig &c)
{
    auto moveOvalBy = new MoveOvalBy();
    if (moveOvalBy && moveOvalBy->initWithDuration(dt, c))
    {
        moveOvalBy->autorelease();
        return moveOvalBy;
    }
    
    return nullptr;
}

bool MoveOvalBy::initWithDuration(float dt, const OvalConfig &c)
{
    if (ActionInterval::initWithDuration(dt))
    {
        _config = c;
        return true;
    }
    
    return false;
}

void MoveOvalBy::update(float dt)
{
    if (_target)
    {
        float x = getPosXAtOval(dt);
        float y = getPosYAtOval(dt);
        _target->setPosition(_config.centerPos + Vec2(x, y));
        if (dt <= 0.5)
        {
            _target->setZOrder(_config.zOrder.first);
        }
        else
        {
            _target->setZOrder(_config.zOrder.second);
        }
    }
}

MoveOvalBy *MoveOvalBy::clone() const
{
    auto moveOvalBy = new MoveOvalBy();
    if (moveOvalBy && moveOvalBy->initWithDuration(_duration, _config))
    {
        moveOvalBy->autorelease();
        return moveOvalBy;
    }
    
    return nullptr;
}

MoveOvalBy *MoveOvalBy::reverse() const
{
    OvalConfig newConfig;
    newConfig.a = _config.a;
    newConfig.b = _config.b;
    newConfig.centerPos = _config.centerPos;
    newConfig.moveClockDir = !_config.moveClockDir;
    newConfig.zOrder = _config.zOrder;
    return MoveOvalBy::create(_duration, newConfig);
}

void MoveOvalBy::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
}

