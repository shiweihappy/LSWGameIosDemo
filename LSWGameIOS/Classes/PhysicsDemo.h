//
//  PhysicsDemo.h
//  LSWGameIOS
//
//  Created by lsw on 14-11-18.
//
//

#ifndef __LSWGameIOS__PhysicsDemo__
#define __LSWGameIOS__PhysicsDemo__

#include <iostream>
#include "cocos2d.h"

class PhysicsDemo :public cocos2d::LayerColor {
public:
    
    PhysicsDemo();
    ~PhysicsDemo();
    
    virtual bool init();
    static cocos2d::Scene *createScene();
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event);
    void update(float dt);
    CREATE_FUNC(PhysicsDemo);
private:
    void addPlane(cocos2d::Vec2 position);
    
private:
    bool _isTouch;
    cocos2d::Sprite *_block;
    float _blockH;
};

#endif /* defined(__LSWGameIOS__PhysicsDemo__) */
