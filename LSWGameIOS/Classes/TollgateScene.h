//
//  TollgateScene.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-29.
//
//

#ifndef __LSWGameIOS__TollgateScene__
#define __LSWGameIOS__TollgateScene__

#include "cocos2d.h"

class TollgateScene : public cocos2d::LayerColor {
public:
    TollgateScene();
    ~TollgateScene();
    static cocos2d::Scene *createScene();
    virtual bool init();
    virtual void onExit();
    CREATE_FUNC(TollgateScene);
};

#endif /* defined(__LSWGameIOS__TollgateScene__) */
