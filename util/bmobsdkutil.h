/**
* create by zhou,2016-01-20
*/
#ifndef BMOBSDK_BMOBSDKUTIL_H_
#define BMOBSDK_BMOBSDKUTIL_H_
#include <iostream>
#include <time.h>

#include "cocos2d.h"

#include "bmobhttputil.h"
#include "bmobjsonutil.h"
#include "bmobstrutil.h"
#include "bmoblog.h"

using namespace std;
USING_NS_CC;

namespace bmobutil{
    class BmobSDKUtil{
    public:
        /**
        * 得到平台的类型：Android、IOS、WP
        * @param void
        */
        static string getPlatomType();

        /**
        * 将string类型的map转为CCObject类型的map
        * @param  data  将转换的数据
        * @return CCDictionary* 返回转换后的数据
        */
        static map<string,CCObject*> mapStringToCCObject(map<string,string> data);

        /**
        * 将string类型的map转为CCDictionary类型
        * @param data   将转换的数据
        * @return CCDictionary* 返回转换后的数据
        */
        static CCDictionary* mapStringToCCDirectionary(map<string,string> data);

        /**
        * 获取当前时间,格式是:year-month-day hour:munite:seconed
        */
        static string getCurrentTime();


    public:
    };
}
#endif
