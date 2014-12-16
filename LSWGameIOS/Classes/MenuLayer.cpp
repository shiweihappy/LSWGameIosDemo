//
//  MenuLayer.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-27.
//
//

#include "MenuLayer.h"
#include "GameScene.h"

USING_NS_CC;

bool MenuLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    auto menuBg = Sprite::create("bg_menuscene.jpg");
    menuBg->setPosition(Vec2(winSize.width/2, winSize.height/2));
    addChild(menuBg, -1);
    
    auto menuItemImg = MenuItemImage::create("menu_start.png", "menu_start.png", CC_CALLBACK_1(MenuLayer::startGame, this));
    menuItemImg->setPosition(Vec2(winSize.width/2, winSize.height/2));
    auto menu = Menu::create(menuItemImg, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);
    
    return true;
}

void MenuLayer::startGame(Ref *pSender)
{
    auto scene = GameScene::create();
    Director::getInstance()->replaceScene(TransitionFlipY::create(1.0f, scene));
}