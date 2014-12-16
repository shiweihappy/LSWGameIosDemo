#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SwitchBtnScene.h"
#include "PlaneGameScene.h"
#include "LSWProgressTimer.h"
#include "TollgateScene.h"
#include "MenuScene.h"
#include "PhysicsDemo.h"
#include "Box2dDemo.h"
#include "SpriteShaderDemo.h"
#include "OpenGLESDemo.h"
#include "HttpRequestDemo.h"
#include "CurlDemo.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
//        glview = GLView::createWithRect("My Game", Rect(0, 0, 320, 480));
        director->setOpenGLView(glview);
        glview->setDesignResolutionSize(800, 600, ResolutionPolicy::SHOW_ALL);
    }
    
    director->setProjection(Director::Projection::_3D);
    director->setDepthTest(true);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    std::vector<std::string> searchPaths = FileUtils::getInstance()->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), "star");
    searchPaths.insert(searchPaths.begin(), "doNotSaveM");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    // create a scene. it's an autorelease object
//    auto scene = HelloWorld::createScene();
    //auto scene = SwitchBtnScene::createScene();
    //auto scene = PlaneGameScene::createScene();
//    auto scene = LSWProgressTimer::createScene();
//    auto scene = TollgateScene::createScene();
   
//    auto scene = MenuScene::create();
    
//    auto scene = PhysicsDemo::createScene();
//    auto scene = Box2dDemo::createScene();
//    auto scene = SpriteShaderDemo::createScene();
//    auto scene = OpenGLESDemo::createScene();
    auto scene = HttpRequestDemo::createScene();
    
//    auto scene = CurlDemo::createScene();
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
