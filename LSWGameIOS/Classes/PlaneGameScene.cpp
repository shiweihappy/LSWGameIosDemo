//
//  PlaneGameScene.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-20.
//
//

#include "PlaneGameScene.h"
#include "PlaneGameManager.h"

USING_NS_CC;

bool PlaneGameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plane/bullet.plist");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plane/wsparticle_p01.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plane/nplane.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plane/pig.plist");
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(PlaneGameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(PlaneGameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(PlaneGameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(PlaneGameScene::onTouchCancelled, this);
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    auto menuItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(PlaneGameScene::closeMenuCallBack, this));
    menuItem->setPosition(Vec2(winSize.width - menuItem->getContentSize().width, menuItem->getContentSize().height));
    auto menu = Menu::create(menuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 100);
    
    //addChild(PlaneGameManager::getInstance()->createHeroPlane());
    //addChild(PlaneGameManager::getInstance()->createHeroPet()->getPet());
    
    this->scheduleUpdate();
    return true;
}


Scene *PlaneGameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PlaneGameScene::create();
    scene->addChild(layer);
    return scene;
}

void PlaneGameScene::update(float dt)
{
    PlaneGameManager::getInstance()->update(dt);
}

bool PlaneGameScene::onTouchBegan(Touch *touch, Event *pEvent)
{
    auto loc = touch->getLocation();
    auto flag = PlaneGameManager::getInstance()->checkTouchPlane(loc);
    return flag;
}

void PlaneGameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *pEvent)
{
    auto loc = touch->getLocation();
    PlaneGameManager::getInstance()->onTouchMoved(loc);
}

void PlaneGameScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *pEvent)
{
    
}

void PlaneGameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *pEvent)
{
    CCLOG("onTouchEnded....");
}

void PlaneGameScene::closeMenuCallBack(Ref *pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

