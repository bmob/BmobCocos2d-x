/**
* create by zh_u_ 2015-10-25
*/

#ifndef BMOBSDK_BMOBJSONUTIL_H_
#define BMOBSDK_BMOBJSONUTIL_H_

#include <iostream>
#include <string>
#include "cocos2d.h"
#include "../jsoncpp/include/json.h"

using namespace std;
USING_NS_CC;


class BmobJsonUtil{
public:
	/**
	* 将object转换成json数据
    * @param value 存储转换后的数据
    * @param key 对应转换数据的key
    * @param object 转换的数据对象
	*/
    static void object2Json(Json::Value *value, std::string key, cocos2d::CCObject *object);
    /**
    * 将map数据转换成json数据
    * @param value 存储转换后的数据
    * @param mapData 需要转换的数据
    */
    static void dictionary2Json(Json::Value *value,std::map<std::string, cocos2d::CCObject *> *mapData);
   	/**
   	* 将数组数据转换成json数据 
    * @param jarray 存储转换后的数据
    * @param list 需要转换的数组列表
   	*/
    static void array2Json(Json::Value *jarray, std::vector<cocos2d::CCObject *> *list);
    
    /**
    * 将multimap数据转换成json数据
    * @param value 存储转换后的数据
    * @param mapData 需要转换的multimap数据
    */
    static void dictionary2Json_m(Json::Value *value,std::multimap<std::string, cocos2d::CCObject *> *mapData);

    /**
    * 将json数据转换成CCObject
    * @param value 需要转换的json数据
    * @param key json对应的键
    */
    static cocos2d::CCObject* json2Object(Json::Value *value, std::string key);
    /**
    * 将json数据转换成map数据
    * @param value 需要转换的json数据
    * @param mapData 存储转换后的数据
    */
    static void json2Dictionary(Json::Value *value,std::map<std::string, cocos2d::CCObject *> *mapData);
    /**
    * 将json数据转换成数组
    * @param jarray 
    * @param list 
    */
    static void json2Array(Json::Value *jarray, std::vector<cocos2d::CCObject *> *list);
    /**
    * json转换成字符串
    * @param value
    */
    static string json2String(Json::Value *value);
};

#endif