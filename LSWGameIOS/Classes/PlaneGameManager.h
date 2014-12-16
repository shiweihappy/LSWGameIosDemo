//
//  PlaneGameManager.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-20.
//
//

#ifndef LSWGameIOS_PlaneGameManager_h
#define LSWGameIOS_PlaneGameManager_h

#include "cocos2d.h"
#include "EnemyPlane.h"
#include "Bullet.h"
#include "HeroPet.h"
#include "HeroPlane.h"

class PlaneGameManager : public cocos2d::Ref
{
public:
    ~PlaneGameManager();
    static PlaneGameManager* getInstance();
    
    HeroPlane *createHeroPlane();
    HeroPet * createHeroPet();
    void createEnemyPlane();
    void createBullets();
    
    void update(float dt);
    
    bool checkTouchPlane(cocos2d::Vec2 &loc);
    
    void onTouchMoved(cocos2d::Vec2 &loc);
private:
    PlaneGameManager();
    void moveHeroPlane(cocos2d::Vec2 &loc);
    
private:
    cocos2d::Vector<EnemyPlane *> _enemyPlaneVec;
    HeroPet *_heroPet;
    HeroPlane *_heroPlane;
    cocos2d::Vector<Bullet *> _bulletVec;
};

#endif
