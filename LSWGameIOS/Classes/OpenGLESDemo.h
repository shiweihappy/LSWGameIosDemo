//
//  OpenGLESDemo.h
//  LSWGameIOS
//
//  Created by lsw on 14-12-1.
//
//

#ifndef __LSWGameIOS__OpenGLESDemo__
#define __LSWGameIOS__OpenGLESDemo__

#include <iostream>
#include "cocos2d.h"

class OpenGLESDemo : public cocos2d::Layer {
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    void onDraw();
    
    CREATE_FUNC(OpenGLESDemo);

private:
    cocos2d::CustomCommand _customCommand;
    GLuint vao;
    GLuint vertexVBO;
    GLuint colorVBO;
};

#endif /* defined(__LSWGameIOS__OpenGLESDemo__) */
