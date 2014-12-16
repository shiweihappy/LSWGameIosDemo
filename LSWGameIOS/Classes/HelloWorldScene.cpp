#include "HelloWorldScene.h"
#include "OvalAction.h"
#include "SpriteShaderDemo.h"

USING_NS_CC;
using namespace ui;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");

//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    
//    auto stencil = Sprite::create("CloseNormal.png");
//    auto clipper = ClippingNode::create();
//    clipper->setStencil(stencil);
//    clipper->setAlphaThreshold(100);
//    clipper->setInverted(true);
//    this->addChild(clipper);
//    
//    clipper->addChild(sprite);
//    clipper->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
//    _richText = CwaRichText::create();
//    _richText->ignoreContentAdaptWithSize(false);
//    _richText->setSize(Size(100, 500));
//    _richText->setAnchorPoint(Vec2(0.5, 0.5));
//    
//    CwaRichElementText *ret1 = CwaRichElementText::create(1, Color3B::BLUE, 255, "第为深深的在南京市的佛山的佛陪我说对方l;udofewnocxzv是飞机了哈\n放\nTEXT", "Arial", 30);
//    CwaRichElementText *ret2 = CwaRichElementText::create(2, Color3B::WHITE, 255, "第\np   2", "Arial", 35);
//    CwaRichElementText *ret3 = CwaRichElementText::create(3, Color3B::RED, 255, "第\n3句话", "Arial", 20);
//    CwaRichElementText *ret4 = CwaRichElementText::create(4, Color3B::BLUE, 255, "第4句话", "Arial", 40);
//    
//    _richText->pushBackElement(ret1);
//    _richText->pushBackElement(ret2);
//    _richText->pushBackElement(ret3);
//    _richText->pushBackElement(ret4);
//    
//    addChild(_richText);
//    _richText->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    
//    LayerColor *layerColor = LayerColor::create(Color4B(255, 0, 255, 255), visibleSize.width, visibleSize.height);
//    addChild(layerColor);
//    
//    LayerGradient *layerGradient = LayerGradient::create(Color4B(255, 0, 0, 0), Color4B(0, 255, 0, 255));
//    addChild(layerGradient);
//    layerGradient->setVector(Vec2(0, 1));
    
    
    list = __Array::createWithCapacity(3);
    list->retain();
    
    for (auto i = 0; i<3; i++)
    {
        auto s = Sprite::create("CloseSelected.png");
        list->addObject(s);
    }
    
    auto ss = Sprite::create("CloseNormal.png");
    list->insertObject(ss, 1);
    
    Ref *obj = nullptr;
    CCARRAY_FOREACH(list, obj)
    {
        auto s = (Sprite *)obj;
        
        auto x = CCRANDOM_0_1() * visibleSize.width;
        auto y = CCRANDOM_0_1() * visibleSize.height;
        
        s->setPosition(Vec2(x, y));
        //addChild(s);
    }
    
    auto l = Label::createWithBMFont("10secGreen.fnt", "123456789");
    l->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
//    addChild(l);
    auto font_1 = (Sprite*)l->getLetter(0);
    auto font_3 = (Sprite*)l->getLetter(2);
    auto font_8 = (Sprite*)l->getLetter(7);
    
    auto rotate = RotateBy::create(1.5f, 360);
    auto rot_1 = RepeatForever::create(rotate);
    
    auto scaleBig = ScaleBy::create(2, 0.5f);
    auto scaleSmall = scaleBig->reverse();
    auto scale_3 = RepeatForever::create(Sequence::create(scaleBig, scaleSmall, NULL));
    
    auto jump = JumpBy::create(1.0f, Vec2::ZERO, 60, 1);
    auto jump_8 = RepeatForever::create(jump);
    
    font_1->runAction(rot_1);
    font_3->runAction(scale_3);
    font_8->runAction(jump_8);
    
    
    auto drawNode = DrawNode::create();
    Vec2 points[] = {Vec2(100, 100), Vec2(100, 300), Vec2(300, 300), Vec2(300, 100)};
    drawNode->drawPolygon(points, sizeof(points)/sizeof(points[0]), Color4F(1, 0, 0, 0.5), 4, Color4F(0, 0, 1, 1));
//    addChild(drawNode);
    
    
    
    auto s1 = Sprite::create("CloseSelected.png");
    addChild(s1);
    s1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    auto s2 = Sprite::create("CloseNormal.png");
    addChild(s2);
    OvalConfig c;
    c.a = 100;
    c.b = 10;
    c.centerPos = s1->getPosition();
    c.moveClockDir = true;
    c.zOrder.first = -1;
    c.zOrder.second = 1;
    s2->runAction(RepeatForever::create(MoveOvalBy::create(1.0f, c)));
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
