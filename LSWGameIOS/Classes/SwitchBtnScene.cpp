//
//  SwitchBtnScene.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-17.
//
//

#include "SwitchBtnScene.h"
#include "GUI/CCControlExtension/CCControlSwitch.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene *SwitchBtnScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SwitchBtnScene::create();
    scene->addChild(layer);
    return scene;
}

bool SwitchBtnScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    auto onLabel = Label::createWithSystemFont("on", "Arail", 20);
    auto offLabel = Label::createWithSystemFont("off", "Arail", 20);
    onLabel->setColor(Color3B(0, 0, 0));
    offLabel->setColor(Color3B(0, 0, 0));
    
    auto maskSprite = Sprite::create("switchButton/switchGreen.png");
    auto onSprite = Sprite::create("switchButton/switchGreen.png");
    auto offSprite = Sprite::create("switchButton/switchRed.png");
    auto thumbSprite = Sprite::create("switchButton/switchBtn.png");
    //设置按钮的截取范围 开关图片和显示文字以及按钮
    ControlSwitch *switchBtn = ControlSwitch::create(maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel);
    addChild(switchBtn);
    switchBtn->setPosition(Vec2(winSize.width/2, winSize.height/2));
    //设置监听事件
    switchBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(SwitchBtnScene::valueChanged), Control::EventType::VALUE_CHANGED);
    
    return true;
}

void SwitchBtnScene::valueChanged(Ref *sender, Control::EventType evt)
{
    if (evt == Control::EventType::VALUE_CHANGED)
    {
        ControlSwitch *btn = (ControlSwitch *)sender;
        if (btn->isOn())
        {
            CCLOG("btn is on");
        }
        else
        {
            CCLOG("btn is off");
        }
    }
    else
    {
        CCLOG("is other state");
    }
}