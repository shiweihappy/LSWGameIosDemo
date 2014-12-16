//
//  PhysicsDemo.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-11-18.
//
//

#include "PhysicsDemo.h"

USING_NS_CC;

PhysicsDemo::PhysicsDemo()
:_isTouch(false)
,_blockH(0)
{
    
}

PhysicsDemo::~PhysicsDemo()
{
    
}

bool PhysicsDemo::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    
    auto edge = Sprite::create();
    edge->setPosition(winSize/2);
    edge->setPhysicsBody(PhysicsBody::createEdgeBox(winSize));
    addChild(edge);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(PhysicsDemo::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(PhysicsDemo::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(PhysicsDemo::onTouchEnded, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    auto physicsListener = EventListenerPhysicsContact::create();
    physicsListener->onContactBegin = [](PhysicsContact &contact) {
        auto spriteA = (Sprite *)contact.getShapeA()->getBody()->getNode();
        auto spriteB = (Sprite *)contact.getShapeB()->getBody()->getNode();
        
        if (spriteA && spriteA->getTag() == 1
            && spriteB && spriteB->getTag() == 1)
        {
            spriteA->setColor(Color3B::YELLOW);
            spriteB->setColor(Color3B::YELLOW);
        }
        
        return true;
    };
    
    physicsListener->onContactPostSolve = [](PhysicsContact& contact, const PhysicsContactPostSolve& solve) {
        log("onContactPostSolve");
    };
    
    physicsListener->onContactPreSolve = [] (PhysicsContact& contact, PhysicsContactPreSolve& solve) {
        log("onContactPreSolve");
        return true;
    };
    
    physicsListener->onContactSeperate = [] (PhysicsContact& contact) {
        auto spriteA = (Sprite *)contact.getShapeA()->getBody()->getNode();
        auto spriteB = (Sprite *)contact.getShapeB()->getBody()->getNode();
        if (spriteA && spriteA->getTag() == 1
            && spriteB && spriteB->getTag() == 1)
        {
            spriteA->setColor(Color3B::WHITE);
            spriteB->setColor(Color3B::WHITE);
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(physicsListener, 1);
    
    _block = Sprite::create();
    addChild(_block);
    scheduleUpdate();
    return true;
}

Scene *PhysicsDemo::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, -100));
    auto layer = PhysicsDemo::create();
    scene->addChild(layer);
    return scene;
}

bool PhysicsDemo::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto loc = touch->getLocation();
    addPlane(loc);
//    _isTouch = true;
    return true;
}

void PhysicsDemo::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}

void PhysicsDemo::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    _isTouch = false;
}

void PhysicsDemo::addPlane(Vec2 position)
{
    auto plane = Sprite::create("plane/mplane.png");
    plane->setTag(1);
    addChild(plane);
    plane->setAnchorPoint(Vec2(0, 0));
    //    PhysicsBody *planeBody = PhysicsBody::createBox(plane->getContentSize());
    PhysicsBody *planeBody = PhysicsBody::createCircle(plane->getContentSize().width/2);
    planeBody->setContactTestBitmask(0xffffff);
    plane->setPhysicsBody(planeBody);
    
    plane->setPosition(position);
    
//    auto plane1 = Sprite::create("plane/mplane.png");
//    plane1->setTag(2);
//    PhysicsBody *rectBody = PhysicsBody::createBox(plane1->getContentSize());
//    rectBody->setContactTestBitmask(0xffffff);
//    plane1->setPhysicsBody(rectBody);
//    addChild(plane1);
//    plane1->setPosition(Vec2(position.x - 100, position.y));
//    
//    auto world = this->getScene()->getPhysicsWorld();
//    auto joint = PhysicsJointDistance::construct(planeBody, rectBody, Vec2(0, 0), Vec2(0, plane1->getContentSize().width/2));
//    world->addJoint(joint);
}

void PhysicsDemo::update(float dt)
{
    if (_isTouch)
    {
        _blockH += 1;
        _block->setColor(Color3B(0, 0, 0));
        _block->setTextureRect(Rect(0, 0, 20, _blockH));
//        _block->setContentSize(Size(20, _blockH));
        _block->setPhysicsBody(PhysicsBody::createBox(Size(20, _blockH)));
        _block->getPhysicsBody()->setContactTestBitmask(0xffffff);
        _block->getPhysicsBody()->setDynamic(false);
        _block->setPosition(Vec2(200, 100 + (_blockH/2)));
    }
}

