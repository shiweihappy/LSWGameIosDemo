//
//  HeroPlane.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-20.
//
//

#ifndef LSWGameIOS_HeroPlane_h
#define LSWGameIOS_HeroPlane_h

#include "cocos2d.h"

class HeroPlane : public cocos2d::Sprite
{
public:
    HeroPlane();
    ~HeroPlane();
    
    virtual bool init();
    
    void loseLife();
    bool isDie();
    int getLife();
    
    CREATE_FUNC(HeroPlane);
private:
    int _life;
};

#endif
