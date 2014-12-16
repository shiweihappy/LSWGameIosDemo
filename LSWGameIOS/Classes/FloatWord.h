//
//  FloatWord.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-27.
//
//

#ifndef __LSWGameIOS__FloatWord__
#define __LSWGameIOS__FloatWord__

#include "cocos2d.h"

class FloatWord : public cocos2d::Node {
public:
    static FloatWord *create(const std::string &word, int fontSize, cocos2d::Vec2 startPos);
    bool init(const std::string &word, int fontSize, cocos2d::Vec2 startPos);
    void fadeIn(float delay, std::function<void()> callback);
    void fadeOut(float delay, std::function<void()> callback);
    void fadeInOut(const float speed, float delay, std::function<void()> callback);
    
private:
    cocos2d::Vec2 _startPos;
    int _fontSize;
    cocos2d::Label *_label;
};

#endif /* defined(__LSWGameIOS__FloatWord__) */
