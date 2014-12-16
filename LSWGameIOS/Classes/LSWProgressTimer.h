//
//  LSWProgressTimer.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-28.
//
//

#ifndef __LSWGameIOS__LSWProgressTimer__
#define __LSWGameIOS__LSWProgressTimer__

#include "cocos2d.h"

class LSWProgressTimer : public cocos2d::Layer {
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(LSWProgressTimer);
    
private:
    void scheduleProgressTimer(float dt);
};

#endif /* defined(__LSWGameIOS__LSWProgressTimer__) */
