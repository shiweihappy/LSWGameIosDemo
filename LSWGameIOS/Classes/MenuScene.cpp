//
//  MenuScene.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-27.
//
//

#include "MenuScene.h"
#include "MenuLayer.h"

USING_NS_CC;

bool MenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    auto menuLayer = MenuLayer::create();
    addChild(menuLayer);
    return true;
}

