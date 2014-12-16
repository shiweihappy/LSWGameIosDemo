//
//  GameScene.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-27.
//
//

#include "GameScene.h"
#include "GameLayer.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    auto layer = GameLayer::create();
    addChild(layer);
    return true;
}