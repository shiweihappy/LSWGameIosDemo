//
//  HeroPet.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-20.
//
//

#ifndef LSWGameIOS_HeroPet_h
#define LSWGameIOS_HeroPet_h

#include "cocos2d.h"

class HeroPet : public cocos2d::Sprite
{
public:
    HeroPet();
    ~HeroPet();
    static HeroPet *createHeroPet();
    cocos2d::Sprite *getPet();
    void petFollowHero(cocos2d::Vec2 pos);
    void petAnimation();
    CREATE_FUNC(HeroPet);
private:
    bool initHeroPet();
    
private:
    cocos2d::Sprite *_pet;
};

#endif
