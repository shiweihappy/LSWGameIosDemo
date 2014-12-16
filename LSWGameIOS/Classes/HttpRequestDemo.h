//
//  HttpRequestDemo.h
//  LSWGameIOS
//
//  Created by lsw on 14-12-15.
//
//

#ifndef __LSWGameIOS__HttpRequestDemo__
#define __LSWGameIOS__HttpRequestDemo__

#include <iostream>

#include "cocos2d.h"
#include "network/HttpClient.h"

class HttpRequestDemo : public cocos2d::Layer {
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(HttpRequestDemo);
private:
    void downloadPicture();
    void sendRequestGet();
    void sendRequestPost();
    void onHttpRequestComplete(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void onDownloadComplete(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void menuCallBack(cocos2d::Ref *sender);
    void captureScreen();
private:
    int index;
};


#endif /* defined(__LSWGameIOS__HttpRequestDemo__) */
