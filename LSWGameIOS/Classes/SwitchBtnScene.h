//
//  SwitchBtnScene.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-17.
//
//

#ifndef LSWGameIOS_SwitchBtnScene_h
#define LSWGameIOS_SwitchBtnScene_h

#include "cocos2d.h"
#include "cocos-ext.h"

class SwitchBtnScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene();
    bool init();
    CREATE_FUNC(SwitchBtnScene);
    
    void valueChanged(cocos2d::Ref *sender, cocos2d::extension::Control::EventType evt);
};

#endif
