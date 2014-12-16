//
//  CurlDemo.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-12-16.
//
//

#include "CurlDemo.h"
#include "curl.h"

USING_NS_CC;

bool CurlDemo::init() {
    if (!Layer::init()) {
        return false;
    }
    
    CURLcode nResCode;
    CURL *pCurl = curl_easy_init();
    if (pCurl != nullptr) {
        auto fileName = FileUtils::getInstance()->getWritablePath() +"ceshi.jpg";
        FILE *pFile = fopen(fileName.c_str(), "wb+");
        CCLOG("filename = %s", fileName.c_str());
        curl_easy_setopt(pCurl, CURLOPT_URL, "http://ww1.sinaimg.cn/large/7f32a2c8jw1e8lyw03zpbj20c8d1ynpd.jpg");
        if (pFile != nullptr) {
            curl_easy_setopt(pCurl, CURLOPT_FILE, pFile); //设置文件指针
        }
        curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, pWriteCallBack); //回调方法
        curl_easy_setopt(pCurl, CURLOPT_VERBOSE, true);
        curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 60); //超时时间
        curl_easy_setopt(pCurl, CURLOPT_NOPROGRESS, 0L);
        curl_easy_setopt(pCurl, CURLOPT_PROGRESSFUNCTION, downloadeProgress);//下载进度
        nResCode = curl_easy_perform(pCurl);
        curl_easy_cleanup(pCurl);
        fclose(pFile);
        if (nResCode == CURLE_OK) {
            CCLOG("download success");
        } else {
            CCLOG("code : %d", nResCode);
        }
    }
    
    return true;
}

Scene *CurlDemo::createScene() {
    auto scene = Scene::create();
    auto layer = CurlDemo::create();
    scene->addChild(layer);
    return scene;
}


size_t CurlDemo::pWriteCallBack(void *pData, size_t n, size_t nDataSize, FILE *stream) {
    size_t nWriten = fwrite(pData, n, nDataSize, (FILE *)stream);
    return nWriten;
}

int CurlDemo::downloadeProgress(void *clienttp, double fDownLoadTotal, double fDownLoaded, double fUpTotal, double fUpLoaded) {
    if (fDownLoaded >= 0 && fDownLoadTotal != 0) {
        CCLOG(">>>>>>>%0.2f%%\n", 100 * (fDownLoaded / fDownLoadTotal));
    }
    
    return 0;
}



