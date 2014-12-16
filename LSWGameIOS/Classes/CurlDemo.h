//
//  CurlDemo.h
//  LSWGameIOS
//
//  Created by lsw on 14-12-16.
//
//

#ifndef __LSWGameIOS__CurlDemo__
#define __LSWGameIOS__CurlDemo__

#include <stdio.h>
#include "cocos2d.h"

class CurlDemo : public cocos2d::Layer {
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(CurlDemo);
private:
    void downLoadPic();
    static size_t pWriteCallBack(void *pData, size_t n, size_t nDataSize, FILE *stream);
    static int downloadeProgress(void *clienttp, double fDownLoadTotal,double fDownLoaded,double fUpTotal,double fUpLoaded);
};

#endif /* defined(__LSWGameIOS__CurlDemo__) */
