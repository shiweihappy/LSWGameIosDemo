//
//  TollgateScene.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-29.
//
//

#include "TollgateScene.h"

USING_NS_CC;

TollgateScene::TollgateScene()
{
    
}

TollgateScene::~TollgateScene()
{
    
}

bool TollgateScene::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    auto body = PhysicsBody::createEdgeBox(winSize/2);
    auto node = Node::create();
    node->setPhysicsBody(body);
    node->setPosition(winSize/2);
    addChild(node);
    return true;
}

Scene *TollgateScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, -0.5f));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = TollgateScene::create();
    scene->addChild(layer);
    return scene;
}

void TollgateScene::onExit()
{
    Layer::onExit();
}

