//
//  StarMatrix.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-31.
//
//

#ifndef __LSWGameIOS__StarMatrix__
#define __LSWGameIOS__StarMatrix__

#include "cocos2d.h"
#include "Star.h"

class GameLayer;
class StarMatrix : public cocos2d::Node {
public:
    static StarMatrix* create(GameLayer *layer);
    bool init(GameLayer *layer);
    void initMatrix();
    cocos2d::Vec2 getPositionByIndex(int i, int j);
    void updateStar(float dt);
    
    void onTouch(cocos2d::Vec2 position);
    bool isEnded();
public:
    static const int ROW_NUM = 10;
    static const int COL_NUM = 10;
    
private:
    Star *getStarByTouch(cocos2d::Vec2 position);
    void genSelectedList(Star *s);
    void deleteSelectedList();
    void adjustMatrix();
private:
    Star* m_star[ROW_NUM][COL_NUM];
    GameLayer* m_layer;
    cocos2d::Vector<Star *> m_selectedList;
};

#endif /* defined(__LSWGameIOS__StarMatrix__) */
