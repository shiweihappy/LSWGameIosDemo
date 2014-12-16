//
//  OpenGLESDemo.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-12-1.
//
//

#include "OpenGLESDemo.h"

USING_NS_CC;
#define TEX_COORD_MAX   1

//绘制三角
/**
bool OpenGLESDemo::init() {
    if (!Layer::init()) {
        return false;
    }
    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
    return true;
}

Scene *OpenGLESDemo::createScene() {
    auto scene = Scene::create();
    auto layer = OpenGLESDemo::create();
    scene->addChild(layer);
    return scene;
}


void OpenGLESDemo::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    Layer::draw(renderer, transform, flags);
    
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(OpenGLESDemo::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
}

void OpenGLESDemo::onDraw() {
    auto gl = getGLProgram();
    gl->use();
    gl->setUniformsForBuiltins();
    
    auto size = Director::getInstance()->getWinSize();
    float vertices[] = {0, 0,
        size.width, 0,
        size.width/2, size.height};
    float color [] = {1, 0, 0, 1,
        0, 1, 0, 1,
        0, 0, 1, 1};
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
    
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
    CHECK_GL_ERROR_DEBUG();
}

*/


//编写自己的shader
/**
bool OpenGLESDemo::init() {
    if (!Layer::init()) {
        return false;
    }
    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
    return true;
}

Scene *OpenGLESDemo::createScene() {
    auto scene = Scene::create();
    auto layer = OpenGLESDemo::create();
    scene->addChild(layer);
    return scene;
}


void OpenGLESDemo::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    Layer::draw(renderer, transform, flags);
    
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(OpenGLESDemo::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
}

void OpenGLESDemo::onDraw() {
    auto myGL = new GLProgram();
    myGL->initWithFilenames("shaderRes/myVertextShader.vsh", "shaderRes/myFragmentShader.fsh");
    myGL->link();
    myGL->updateUniforms();
    myGL->use();
    myGL->setUniformsForBuiltins();
    
    auto size = Director::getInstance()->getWinSize();
    float vertices[] = {0, 0,
        size.width, 0,
        size.width/2, size.height};
    float color [] = {1, 0, 0, 1,
        0, 1, 0, 1,
        0, 0, 1, 1};
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
    
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
    CHECK_GL_ERROR_DEBUG();
}
*/

/**
bool OpenGLESDemo::init() {
    if (!Layer::init()) {
        return false;
    }
    auto myGL = new GLProgram();
    myGL->initWithFilenames("shaderRes/myVertextShader.vsh", "shaderRes/myFragmentShader.fsh");
    myGL->link();
    myGL->updateUniforms();
    this->setGLProgram(myGL);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    
    auto size = Director::getInstance()->getWinSize();
    float vertices[] = {0, 0,
        size.width, 0,
        size.width/2, size.height};
    float color [] = {1, 0, 0, 1,
        0, 1, 0, 1,
        0, 0, 1, 1};
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLuint positionLocation = glGetAttribLocation(myGL->getProgram(), "a_position");
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    
    GLuint colorLocation = glGetAttribLocation(myGL->getProgram(), "a_color");
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    myGL->autorelease();
    return true;
}

Scene *OpenGLESDemo::createScene() {
    auto scene = Scene::create();
    auto layer = OpenGLESDemo::create();
    scene->addChild(layer);
    return scene;
}


void OpenGLESDemo::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    Layer::draw(renderer, transform, flags);
    
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(OpenGLESDemo::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
}

void OpenGLESDemo::onDraw() {
    auto myGL = getGLProgram();
    myGL->use();
    myGL->setUniformsForBuiltins();
    
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
    CHECK_GL_ERROR_DEBUG();
}
*/


/**
//vbo vao
bool OpenGLESDemo::init() {
    if (!Layer::init()) {
        return false;
    }
    auto myGL = new GLProgram();
    myGL->initWithFilenames("shaderRes/myVertextShader.vsh", "shaderRes/myFragmentShader.fsh");
    myGL->link();
    myGL->updateUniforms();
    this->setGLProgram(myGL);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    
    auto size = Director::getInstance()->getWinSize();
    float vertices[] = {0, 0,
        size.width, 0,
        size.width/2, size.height};
    float color [] = {1, 0, 0, 1,
        0, 1, 0, 1,
        0, 0, 1, 1};
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLuint positionLocation = glGetAttribLocation(myGL->getProgram(), "a_position");
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    
    GLuint colorLocation = glGetAttribLocation(myGL->getProgram(), "a_color");
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    
    GLuint uColorLocation = glGetUniformLocation(myGL->getProgram(), "u_color");
    float uColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glUniform4fv(uColorLocation, 1, uColor);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    myGL->autorelease();
    return true;
}

Scene *OpenGLESDemo::createScene() {
    auto scene = Scene::create();
    auto layer = OpenGLESDemo::create();
    scene->addChild(layer);
    return scene;
}


void OpenGLESDemo::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    Layer::draw(renderer, transform, flags);
    
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(OpenGLESDemo::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
}

void OpenGLESDemo::onDraw() {
    auto myGL = getGLProgram();
    myGL->use();
    myGL->setUniformsForBuiltins();
    
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
    CHECK_GL_ERROR_DEBUG();
}
*/


//bool OpenGLESDemo::init() {
//    if (!Layer::init()) {
//        return false;
//    }
//    auto myGL = new GLProgram();
//    myGL->initWithFilenames("shaderRes/myVertextShader.vsh", "shaderRes/myFragmentShader.fsh");
//    myGL->link();
//    myGL->updateUniforms();
//    this->setGLProgram(myGL);
//    
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//    
//    glGenBuffers(1, &vertexVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
//    
//    auto size = Director::getInstance()->getWinSize();
//    float vertices[] =
//    {-1, -1,
//    1, -1,
//    -1, 1,
//    -1, 1,
//    1, 1,
//    1, -1};
//    float color [] =
//        {1, 0, 0, 1,
//        0, 1, 0, 1,
//        0, 0, 1, 1,
//        1, 0, 0, 1,
//        0, 1, 0, 1,
//        0, 0, 1, 1};
//    
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    GLuint positionLocation = glGetAttribLocation(myGL->getProgram(), "a_position");
//    glEnableVertexAttribArray(positionLocation);
//    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
//    
//    glGenBuffers(1, &colorVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
//    
//    GLuint colorLocation = glGetAttribLocation(myGL->getProgram(), "a_color");
//    glEnableVertexAttribArray(colorLocation);
//    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
//    
//    
//    GLuint uColorLocation = glGetUniformLocation(myGL->getProgram(), "u_color");
//    float uColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
//    glUniform4fv(uColorLocation, 1, uColor);
//    
//    glBindVertexArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    
//    myGL->autorelease();
//    return true;
//}


Scene *OpenGLESDemo::createScene() {
    auto scene = Scene::create();
    auto layer = OpenGLESDemo::create();
    scene->addChild(layer);
    return scene;
}

bool OpenGLESDemo::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //create my own program
    auto program = new GLProgram;
    program->initWithFilenames("shaderRes/myVertextShader.vsh", "shaderRes/myFragmentShader.fsh");
    program->link();
    //set uniform locations
    program->updateUniforms();
    
    
    //    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
    this->setGLProgram(program);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    
    
    typedef struct {
        float Position[3];
        float Color[4];
        float TexCoord[2];
    } Vertex;
    
    //    auto size = Director::getInstance()->getVisibleSize();
    Vertex data[] =
    {
        // Front
        {{1, -1, 0}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{1, 1, 0}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{-1, 1, 0}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, -1, 0}, {0, 0, 0, 1}, {0, 0}},
        // Back
        {{1, 1, -2}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{-1, -1, -2}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{1, -1, -2}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, 1, -2}, {0, 0, 0, 1}, {0, 0}},
        // Left
        {{-1, -1, 0}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{-1, 1, 0}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{-1, 1, -2}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, -1, -2}, {0, 0, 0, 1}, {0, 0}},
        // Right
        {{1, -1, -2}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{1, 1, -2}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{1, 1, 0}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{1, -1, 0}, {0, 0, 0, 1}, {0, 0}},
        // Top
        {{1, 1, 0}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{1, 1, -2}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{-1, 1, -2}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, 1, 0}, {0, 0, 0, 1}, {0, 0}},
        // Bottom
        {{1, -1, -2}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{1, -1, 0}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{-1, -1, 0}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, -1, -2}, {0, 0, 0, 1}, {0, 0}}
    };
    
    GLubyte indices[] =
    {
        // Front
        0, 1, 2,
        2, 3, 0,
        // Back
        4, 5, 6,
        4, 5, 7,
        // Left
        8, 9, 10,
        10, 11, 8,
        // Right
        12, 13, 14,
        14, 15, 12,
        // Top
        16, 17, 18,
        18, 19, 16,
        // Bottom
        20, 21, 22,
        22, 23, 20
    };
    
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    GLuint positionLocation = glGetAttribLocation(program->getProgram(), "a_position");
    //    CCLOG("position =%d", positionLocation);
    glEnableVertexAttribArray(positionLocation);
    
    
    glVertexAttribPointer(positionLocation,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex,Position));
    
    //set for color
    //    glGenBuffers(1, &colorVBO);
    //    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    
    GLuint colorLocation = glGetAttribLocation(program->getProgram(), "a_color");
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation,
                          4,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex,Color));
    
    GLuint indexVBO;
    glGenBuffers(1, &indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) , indices, GL_STATIC_DRAW);
    
    
    GLuint uColorLocation = glGetUniformLocation(program->getProgram(), "u_color");
    
    float uColor[] = {1.0, 1.0, 1.0, 1.0};
    glUniform4fv(uColorLocation,1, uColor);
    
    GLuint textureId;
    glGenBuffers(1, &textureId);
    
    
    program->autorelease();
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // 使用vao    http://blog.sina.com.cn/s/blog_4a657c5a01016f8s.html
    return true;
}

void OpenGLESDemo::draw(cocos2d::Renderer *renderer, const Mat4 &transform, uint32_t transformUpdated)
{
    Layer::draw(renderer, transform, transformUpdated);
    
    //send custom command to tell the renderer to call opengl commands
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(OpenGLESDemo::onDraw, this);
    renderer->addCommand(&_customCommand);
    
    
}

void OpenGLESDemo::onDraw()
{
    //question1: why the triangle goes to the up side
    //如果使用对等矩阵，则三角形绘制会在最前面
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    Mat4 projectionMatrix;
    Mat4::createPerspective(60, 480/320, 1.0, 42, &projectionMatrix);
    Director::getInstance()->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, projectionMatrix);
    
    Mat4 modelViewMatrix;
    Mat4::createLookAt(Vec3(0,0,1), Vec3(0,0,0), Vec3(0,1,0), &modelViewMatrix);
    modelViewMatrix.translate(0, 0, -5);
    
    static float rotation = 0;
    modelViewMatrix.rotate(Vec3(1,1,1),CC_DEGREES_TO_RADIANS(rotation));
    rotation++;
    if (rotation > 360) {
        rotation = 0;
    }
    Director::getInstance()->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, modelViewMatrix);
    
    
    auto glProgram = getGLProgram();
    glProgram->use();
    //set uniform values, the order of the line is very important
    glProgram->setUniformsForBuiltins();

    //use vao
    glBindVertexArray(vao);
    
    //    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE,(GLvoid*)0);
    
    glBindVertexArray(0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 6);
    CHECK_GL_ERROR_DEBUG();
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}