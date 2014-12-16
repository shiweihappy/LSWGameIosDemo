//
//  GameLayer.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-27.
//
//

#ifndef __LSWGameIOS__GameLayer__
#define __LSWGameIOS__GameLayer__

#include "cocos2d.h"
#include "FloatWord.h"
#include "StarMatrix.h"

class GameLayer : public cocos2d::Layer {
public:
    virtual bool init();
    void floatLevelWord();
    void floatTargetNumWord();
    void removeFloatWord();
    void showStarMatrix();
    void update(float dt);
    
    void refreshMenu();
    void showLinkNum(int num);
    void hideLinkNum();
    void floatLeftStarNum(int num);
    void nextLevel();
    void gameOver();
    
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event);
    
    CREATE_FUNC(GameLayer);
private:
    FloatWord *_levelWord;
    FloatWord *_targetNumWord;
//    TopMenu *_menu;
    StarMatrix *_matrix;
    cocos2d::Label *_linkLabel;
};

#endif /* defined(__LSWGameIOS__GameLayer__) */
