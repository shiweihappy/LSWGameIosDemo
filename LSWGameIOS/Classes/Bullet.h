//
//  Bullet.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-20.
//
//

#ifndef LSWGameIOS_Bullet_h
#define LSWGameIOS_Bullet_h

#include "cocos2d.h"

enum bulletType {
    BulletType1 = 1,
    BulletType2
};

class Bullet : public cocos2d::Sprite
{
public:
    Bullet();
    ~Bullet();
    
    static Bullet *createBullet();
    static Bullet *createBullet(bulletType type);
    
    cocos2d::Sprite *getBullet();
    void bulletAnimation();
    CREATE_FUNC(Bullet);
protected:
    bool initWithBulletType(bulletType type);
private:
    cocos2d::Animation *f_createAnimation(int count, int fps);
    cocos2d::Sprite *_bullet;
};

#endif
