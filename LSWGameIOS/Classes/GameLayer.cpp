//
//  GameLayer.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-27.
//
//

#include "GameLayer.h"

USING_NS_CC;

bool GameLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    this->floatLevelWord();
    
    scheduleUpdate();
    return true;
}

void GameLayer::floatLevelWord()
{
    auto winSize = Director::getInstance()->getWinSize();
    _levelWord = FloatWord::create("关卡1", 40, Vec2(winSize.width, winSize.height * 2/3));
    _levelWord->fadeIn(1.0f, CC_CALLBACK_0(GameLayer::floatTargetNumWord, this));
    addChild(_levelWord, 1);
}

void GameLayer::floatTargetNumWord()
{
    auto winSize = Director::getInstance()->getWinSize();
    _targetNumWord = FloatWord::create("目标分数1000", 40, Vec2(winSize.width, winSize.height * 2/3));
    _targetNumWord->fadeIn(1.0f, CC_CALLBACK_0(GameLayer::removeFloatWord, this));
    addChild(_targetNumWord, 1);
}

void GameLayer::removeFloatWord()
{
    _levelWord->fadeOut(1.0f, nullptr);
    _targetNumWord->fadeOut(1.0f, CC_CALLBACK_0(GameLayer::showStarMatrix, this));
}

void GameLayer::showStarMatrix()
{
    _matrix = StarMatrix::create(this);
    addChild(_matrix);
}

void GameLayer::update(float dt)
{
    if (_matrix)
    {
        _matrix->updateStar(dt);
    }
}

void GameLayer::floatLeftStarNum(int num)
{
    
}

void GameLayer::refreshMenu()
{
    
}

void GameLayer::showLinkNum(int num)
{
    
}

void GameLayer::hideLinkNum()
{
    
}

void GameLayer::nextLevel()
{
    
}

void GameLayer::gameOver()
{
    
}

bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto loc = touch->getLocation();
    //loc = Director::getInstance()->convertToGL(loc);
    if (_matrix)
    {
        _matrix->onTouch(loc);
    }
    return true;
}

void GameLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}

void GameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}
