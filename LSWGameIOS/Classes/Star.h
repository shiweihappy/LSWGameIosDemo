//
//  Star.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-30.
//
//

#ifndef __LSWGameIOS__Star__
#define __LSWGameIOS__Star__

#include "cocos2d.h"

enum {
    GREEN,
    ORANGE,
    RED,
    PURPLE,
    BLUE
};

class Star : public cocos2d::Sprite {
public:
    static Star *create(int color);
    int getColor();
    void setDesPosition(cocos2d::Vec2 pos);
    cocos2d::Vec2 getDesPosition();
    
    void updatePosition();
    int getIndexI();
    int getIndexJ();
    void setIndexIJ(int i, int j);
    void setSelected(bool isSelected);
    bool isSelected();
    CREATE_FUNC(Star);
private:
    const char *getImage(int color);
public:
    static const int COLOR_MAX_NUM = 5;
    static const int STAR_W = 48;
    static const int STAR_H = 48;
    static const int MOVE_SPEED = 48;
private:
    cocos2d::Vec2 _desPosition;
    int _color;
    int _index_i;
    int _index_j;
    bool _selected;
    
};

#endif /* defined(__LSWGameIOS__Star__) */
