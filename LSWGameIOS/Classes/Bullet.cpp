//
//  Bullet.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-20.
//
//

#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet()
{
    
}

Bullet::~Bullet()
{
    
}

Bullet *Bullet::createBullet()
{
    auto bullet = new Bullet();
    if (bullet && bullet->initWithBulletType(BulletType1))
    {
        bullet->autorelease();
        return bullet;
    }
    
    return nullptr;
}

Bullet *Bullet::createBullet(bulletType type)
{
    auto bullet = new Bullet();
    if (bullet && bullet->initWithBulletType(type))
    {
        bullet->autorelease();
        return bullet;
    }
    
    return nullptr;
}

bool Bullet::initWithBulletType(bulletType type)
{
    if (!Sprite::init())
    {
        return false;
    }
    switch (type) {
        case BulletType1:
            _bullet = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet_1.png"));
            break;
        default:
            _bullet = nullptr;
            break;
    }
    
    if (_bullet)
    {
        return true;
    }
    return false;
}

void Bullet::bulletAnimation()
{
    auto animation = f_createAnimation(2, 60);
    getBullet()->runAction(RepeatForever::create(Animate::create(animation)));
}

Animation *Bullet::f_createAnimation(int count, int fps)
{
    char buff[16];
    Vector<SpriteFrame *> frames;
    for (auto i = 1; i<=count; i++)
    {
        sprintf(buff, "bullet_%d.png", i);
        frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(buff));
    }
    
    auto *pAnimation = Animation::createWithSpriteFrames(frames, 1/fps);
    return pAnimation;
}

Sprite *Bullet::getBullet()
{
    return _bullet;
}

