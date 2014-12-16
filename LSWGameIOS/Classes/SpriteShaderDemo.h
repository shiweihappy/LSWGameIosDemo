//
//  SpriteShaderDemo.h
//  LSWGameIOS
//
//  Created by lsw on 14-11-28.
//
//

#ifndef __LSWGameIOS__SpriteShaderDemo__
#define __LSWGameIOS__SpriteShaderDemo__

#include <iostream>
#include "cocos2d.h"

class SpriteShaderDemo : public cocos2d::Layer {
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(SpriteShaderDemo);
};

#endif /* defined(__LSWGameIOS__SpriteShaderDemo__) */
