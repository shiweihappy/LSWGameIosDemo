//
//  OvalAction.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-27.
//
//

#ifndef __LSWGameIOS__OvalAction__
#define __LSWGameIOS__OvalAction__

#include "cocos2d.h"

typedef struct OvalConfig {
    cocos2d::Vec2 centerPos;
    float a;
    float b;
    bool moveClockDir;
    std::pair<int, int> zOrder;
}LOvalConfig;

class MoveOvalBy : public cocos2d::ActionInterval {
public:
    MoveOvalBy();
    ~MoveOvalBy();
    
    bool initWithDuration(float dt, const OvalConfig& c);
    virtual MoveOvalBy* clone() const override;
    virtual MoveOvalBy* reverse() const override;
    virtual void update(float dt);
    virtual void startWithTarget(cocos2d::Node *target) override;
    
    static MoveOvalBy* create(float dt, const OvalConfig& c);
    
protected:
    OvalConfig _config;
    
    inline float getPosXAtOval(float dt) {
        if (_config.moveClockDir) {
            return _config.a * cos(4 * MATH_PIOVER2 * dt);
        }
        return _config.a * cos(4 * MATH_PIOVER2 * (1 - dt));
    }
    
    inline float getPosYAtOval(float dt) {
        if (_config.moveClockDir) {
            return _config.b * sin(4 * MATH_PIOVER2 * dt);
        }
        return _config.b * sin(4 * MATH_PIOVER2 * (1 - dt));
    }
    
    
};

#endif /* defined(__LSWGameIOS__OvalAction__) */
