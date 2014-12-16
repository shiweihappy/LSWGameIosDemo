//
//  FloatWord.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-27.
//
//

#include "FloatWord.h"

USING_NS_CC;

FloatWord* FloatWord::create(const std::string &word, int fontSize, cocos2d::Vec2 startPos)
{
    auto floatWord = new FloatWord();
    if (floatWord && floatWord->init(word, fontSize, startPos))
    {
        floatWord->autorelease();
        return floatWord;
    }
    
    CC_SAFE_DELETE(floatWord);
    return nullptr;
}

bool FloatWord::init(const std::string &word, int fontSize, cocos2d::Vec2 startPos)
{
    if (!Node::init())
    {
        return false;
    }
    
    _startPos = startPos;
    _label = Label::createWithSystemFont(word, "Arial", fontSize);
    _label->setPosition(startPos);
    addChild(_label);
    return true;
}

void FloatWord::fadeIn(float delay, std::function<void ()> callback)
{
    auto winSize = Director::getInstance()->getWinSize();
    auto moveTo = MoveTo::create(delay, Vec2(winSize.width/2, winSize.height/2));
    auto callFunc = CallFunc::create(callback);
    if (_label)
    {
        _label->runAction(Sequence::create(moveTo, callFunc, NULL));
    }
}

void FloatWord::fadeInOut(const float speed, float delay, std::function<void ()> callback)
{
    auto winSize = Director::getInstance()->getWinSize();
    auto moveIn = MoveTo::create(speed, Vec2(winSize.width/2, winSize.height/2));
    auto delayTime = DelayTime::create(delay);
    auto moveOut = MoveTo::create(speed, Vec2(0, _startPos.y));
    auto callFunc = CallFunc::create(callback);
    auto callRemove = CallFunc::create([this](){
        this->removeFromParentAndCleanup(true);
    });
    
    if (_label)
    {
        _label->runAction(Sequence::create(moveIn, delayTime, moveOut, callFunc, callRemove, NULL));
    }
}

void FloatWord::fadeOut(float delay, std::function<void ()> callback)
{
    auto moveTo = MoveTo::create(delay, Vec2(0, _startPos.y));
    auto callFunc = CallFunc::create(callback);
    auto callRemove = CallFunc::create([this](){
        this->removeFromParentAndCleanup(true);
    });
    
    if (_label)
    {
        _label->runAction(Sequence::create(moveTo, callFunc, callRemove, NULL));
    }
}
