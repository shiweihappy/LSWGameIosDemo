//
//  SpriteShaderDemo.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-11-28.
//
//

#include "SpriteShaderDemo.h"

USING_NS_CC;

bool SpriteShaderDemo::init() {
    if (!Layer::init()) {
        return false;
    }
    
    auto size = Director::getInstance()->getVisibleSize();
    auto s = Sprite::create("HelloWorld.png");
    s->setAnchorPoint(Vec2(0.5, 0.5));
    s->setPosition(Vec2(size.width/2, size.height/2));
    addChild(s);
    
    
//    auto gl = new GLProgram();
//    gl->initWithFilenames("gray.vsh", "gray.fsh");
//    gl->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
//    gl->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
//    gl->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
//    gl->link();
//    gl->updateUniforms();
//    s->setGLProgram(gl);
    
    //恢复
    //s->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
    
    
    auto gl = new GLProgram();
    gl->initWithFilenames("gray.vsh", "example_outline.fsh");
    auto glState = GLProgramState::getOrCreateWithGLProgram(gl);
//    Vec3 color(1.0f, 0.2f, 0.3f);
//    GLfloat radius = 0.01f;
//    GLfloat threshold = 1.75;
//    
//    glState->setUniformVec3("u_outlineColor", color);
//    glState->setUniformFloat("u_threshold", threshold);
//    glState->setUniformFloat("u_radius", radius);
    gl->link();
    gl->updateUniforms();
    s->setGLProgramState(glState);
    
    return true;
}

Scene *SpriteShaderDemo::createScene() {
    auto scene = Scene::create();
    auto layer = SpriteShaderDemo::create();
    scene->addChild(layer);
    return scene;
}




