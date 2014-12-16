//
//  MenuLayer.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-27.
//
//

#ifndef __LSWGameIOS__MenuLayer__
#define __LSWGameIOS__MenuLayer__

#include "cocos2d.h"

class MenuLayer : public cocos2d::Layer {
public:
    virtual bool init();
    
    CREATE_FUNC(MenuLayer);

private:
    void startGame(cocos2d::Ref *pSender);
};

#endif /* defined(__LSWGameIOS__MenuLayer__) */
