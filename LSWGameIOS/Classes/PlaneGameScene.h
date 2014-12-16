//
//  PlaneGameScene.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-20.
//
//

#ifndef LSWGameIOS_PlaneGameScene_h
#define LSWGameIOS_PlaneGameScene_h

#include "cocos2d.h"

class PlaneGameScene : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *pEvent);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *pEvent);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *pEvent);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *pEvent);
    
    void update(float dt);
    
    CREATE_FUNC(PlaneGameScene);
private:
    void closeMenuCallBack(cocos2d::Ref *pSender);
};

#endif
