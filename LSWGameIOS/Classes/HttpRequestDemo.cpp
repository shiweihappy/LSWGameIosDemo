//
//  HttpRequestDemo.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-12-15.
//
//

#include "HttpRequestDemo.h"

USING_NS_CC;
using namespace cocos2d::network;

bool HttpRequestDemo::init() {
    if (!Layer::init()) {
        return false;
    }
//    auto s = Sprite::create("HelloWorld.png");
//    s->setPosition(Vec2(200, 200));
//    addChild(s);
    auto menuItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HttpRequestDemo::menuCallBack, this));
    auto clickMenu = Menu::create(menuItem, NULL);
    addChild(clickMenu);
    menuItem->setPosition(Vec2(100, 100));
    clickMenu->setPosition(Vec2::ZERO);
    
    index = 0;
    
//    downloadPicture();
    
    
    return true;
}

void HttpRequestDemo::captureScreen() {
    auto winSize = Director::getInstance()->getWinSize();
    auto texture = RenderTexture::create(winSize.width, winSize.height, Texture2D::PixelFormat::RGBA8888);
    auto curScene = Director::getInstance()->getRunningScene();
    auto curAnchorPoint = curScene->getAnchorPoint();
    
    texture->begin();
//    curScene->setScale(0.5f);
//    curScene->setAnchorPoint(curAnchorPoint);
    curScene->visit();
    texture->end();
    auto fileName = FileUtils::getInstance()->getWritablePath() + "img.png";
    CCLOG("fileName = %s" , fileName.c_str());
    texture->saveToFile(fileName.c_str(), Image::Format::PNG);
    
//    curScene->setScale(1.0f);
//    curScene->setAnchorPoint(curAnchorPoint);
}

void HttpRequestDemo::downloadPicture() {
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    request->setTag("downLoad tag 1");
    request->setUrl("http://img12.3lian.com/gaoqing02/06/56/13.jpg");
    request->setResponseCallback(CC_CALLBACK_2(HttpRequestDemo::onDownloadComplete, this));
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
}

void HttpRequestDemo::onDownloadComplete(HttpClient *sender, HttpResponse *response) {
    if (!response) {
        return;
    }
    
    if (!response->isSucceed()) {
        CCLOG("error %s", response->getErrorBuffer());
        return;
    }
    
    std::vector<char> *buffData = response->getResponseData();
    char *buff = (char *)malloc(buffData->size());
    std::copy(buffData->begin(), buffData->end(), buff);
    auto fileName = FileUtils::getInstance()->getWritablePath() +"ceshi.jpg";
    FILE *fp = fopen(fileName.c_str(), "wb+");
    fwrite(buff, 1, buffData->size(), fp);
    fclose(fp);
}

void HttpRequestDemo::menuCallBack(Ref *sender) {
    captureScreen();
    return;
    
    if (index == 0) {
        sendRequestGet();
        index = 1;
    } else if (index == 1) {
        sendRequestPost();
        index = 0;
    }
}


Scene *HttpRequestDemo::createScene() {
    auto scene = Scene::create();
    auto layer = HttpRequestDemo::create();
    scene->addChild(layer);
    return scene;
}

void HttpRequestDemo::sendRequestGet() {
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
//    request->setUrl("http://httpbin.org/get");
    request->setUrl("http://just-make-this-request-failed.com");
//    request->setUrl("http://httpbin.org/ip");
//    request->setUrl("http://www.weather.com.cn/data/cityinfo/101010100.html");
    request->setTag("Request Tag 1");
    request->setResponseCallback(CC_CALLBACK_2(HttpRequestDemo::onHttpRequestComplete, this));
//    HttpClient::getInstance()->setTimeoutForConnect(1);
//    HttpClient::getInstance()->setTimeoutForRead(10);
    HttpClient::getInstance()->send(request);
//    HttpClient::getInstance()->sendImmediate(request);
    request->release();
}

void HttpRequestDemo::sendRequestPost() {
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::POST);
    request->setUrl("http://httpbin.org/post");
    request->setTag("Post Tag 1");
    
    request->setResponseCallback(CC_CALLBACK_2(HttpRequestDemo::onHttpRequestComplete, this));
    const char *postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
    request->setRequestData(postData, strlen(postData));
    HttpClient::getInstance()->send(request);
    request->release();
}

void HttpRequestDemo::onHttpRequestComplete(HttpClient *sender, HttpResponse *response) {
    if (!response) {
        return;
    }
    
    if (0 != strlen(response->getHttpRequest()->getTag())) {
        CCLOG("tag is = %s", response->getHttpRequest()->getTag());
    }
    
    auto statusCode = response->getResponseCode();
    CCLOG("statusCode is %ld", statusCode);
    
    if (!response->isSucceed()) {
        CCLOG("error buff is %s", response->getErrorBuffer());
        return;
    }
    
    
    std::vector<char> *bufferData = response->getResponseData();
    CCLOG("buffData is : ");
//    for (auto i = 0; i<bufferData->size(); i++) {
//        CCLOG("%c", (*bufferData)[i]);
//    }
    
    std::string str(bufferData->begin(), bufferData->end());
    CCLOG("str = %s", str.c_str());
}
