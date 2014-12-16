//
//  Box2dDemo.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-11-24.
//
//

#include "Box2dDemo.h"

USING_NS_CC;

bool Box2dDemo::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    _world = new b2World(b2Vec2(0, -10));
    _world->SetAllowSleeping(true);
    _world->SetContactListener(this);
    
    
    addFloor();
//    addBox();
    addJoin();
    scheduleUpdate();
    return true;
}

Scene *Box2dDemo::createScene()
{
    auto scene = Scene::create();
    auto layer = Box2dDemo::create();
    scene->addChild(layer);
    return scene;
}

void Box2dDemo::addBox()
{
    b2BodyDef def;
    def.position = b2Vec2(5, 5);
    def.type = b2_dynamicBody;
//    def.type = b2_kinematicBody;
    b2Body *b = _world->CreateBody(&def);
    
    b2PolygonShape shape;
    shape.SetAsBox(0.5, 0.5);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;
    fixtureDef.shape = &shape;
    b->CreateFixture(&fixtureDef);
    
    auto sprite = Sprite::create();
    addChild(sprite);
    sprite->setTextureRect(Rect(0, 0, 0.5*2*RATIO, 0.5*2*RATIO));
    b->SetUserData(sprite);
}

void Box2dDemo::addJoin()
{
    b2Body *b1 = createBox(3, 5);
    b2Body *b2 = createBox(6, 5);
//    b2RevoluteJointDef joinDef;
//    joinDef.Initialize(b1, b2, b2->GetWorldCenter());
//    _world->CreateJoint(&joinDef);
}

b2Body *Box2dDemo::createBox(float x, float y)
{
    b2BodyDef def;
    def.position = b2Vec2(x, y);
    def.type = b2_dynamicBody;
    b2Body *b = _world->CreateBody(&def);
    b2PolygonShape shape;
    shape.SetAsBox(0.5, 0.5);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;
    fixtureDef.shape = &shape;
    b->CreateFixture(&fixtureDef);
    
    auto sprite = Sprite::create();
    addChild(sprite);
    sprite->setTextureRect(Rect(0, 0, 0.5*2*RATIO, 0.5*2*RATIO));
    b->SetUserData(sprite);
    return b;
}

b2Body *Box2dDemo::createCircle(float r)
{
    
}

void Box2dDemo::addFloor()
{
    b2BodyDef def;
    def.position = b2Vec2(400/RATIO, 0);
    def.type = b2_staticBody;
    _floor = _world->CreateBody(&def);
    
    b2PolygonShape shape;
    shape.SetAsBox(400/RATIO, 0.5);
    b2FixtureDef fixturDef;
    fixturDef.density = 1;
    fixturDef.friction = 0.5f;
    fixturDef.shape = &shape;
    _floor->CreateFixture(&fixturDef);
}

void Box2dDemo::update(float dt)
{
    _world->Step(dt, 8, 3);
    for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
//        if (b->GetType() == b2_dynamicBody) {
//            if (b->GetUserData()) {
//                Sprite *s = (Sprite *)b->GetUserData();
//                s->setPosition(b->GetPosition().x * RATIO, b->GetPosition().y * RATIO);
//            }
//        } else if (b->GetType() == b2_kinematicBody) {
            if (b->GetUserData()) {
                Sprite *s = (Sprite *)b->GetUserData();
                s->setPosition(b->GetPosition().x * RATIO, b->GetPosition().y * RATIO);
            }
//        }
    }
}

void Box2dDemo::BeginContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetBody() == _floor ||
       contact->GetFixtureB()->GetBody() == _floor) {
        CCLOG("touch .....");
    }
}



