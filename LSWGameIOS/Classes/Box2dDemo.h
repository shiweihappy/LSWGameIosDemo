//
//  Box2dDemo.h
//  LSWGameIOS
//
//  Created by lsw on 14-11-24.
//
//

#ifndef __LSWGameIOS__Box2dDemo__
#define __LSWGameIOS__Box2dDemo__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"

#define RATIO 80.0f

class Box2dDemo : public cocos2d::Layer, public b2ContactListener{
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    
    virtual void update(float dt);
    void BeginContact(b2Contact* contact);
    CREATE_FUNC(Box2dDemo);
    
private:
    void addBox();
    void addFloor();
    void addJoin();
    b2Body *createCircle(float r);
    b2Body *createBox(float x, float y);
private:
    b2World *_world;
    b2Body *_floor;
};

#endif /* defined(__LSWGameIOS__Box2dDemo__) */
