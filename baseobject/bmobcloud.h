/**
* create by zhou,2016-01-18
* cloud code operator
* 对云端代码的操作
*/
#ifndef BMOBSDK_BMOBCLOUD_H_
#define BMOBSDK_BMOBCLOUD_H_

#include <iostream>
#include <string>
#include "cocos2d.h"
#include "network/HttpRequest.h"

#include "../delegate/bmobdelegate.h"
#include "../jsoncpp/include/json.h"
#include "bmobSDKinit.h"
#include "../util/bmobjsonutil.h"

using namespace std;
USING_NS_CC;

class BmobCloud:public CCObject{
public:
  /**
  * 云端代码的操作类型，执行代码、创建代码、删除代码
  */
  enum EXEC_Type{
    EXEC_Exec,
    EXEC_Create,
    EXEC_Delete,
  };

public:
  BmobCloud();
  ~BmobCloud();

  /**
  * 执行云端代码
  * @param cloudName  云端代码的方法名，如果是创建代码，传递NULL
  * @param param      云端代码的参数
  * @param  delegate  代码执行的回调函数
  * @param  type (默认是EXEC_Exec)     执行的操作，执行代码、创建代码、删除代码
  * 注：当执行创建云端代码的时候，参数中存储的是方法的主题，其中使用键值的对应关系
  * 键为code，值是代码，param 仅存储一个值;如果调用的是创建代码，那么cloudName
  * 传递NULL即可
  */
  void execCloudCode(string cloudName,std::map<string, CCObject*> param,\
    BmobCloudDelegate *delegate,BmobCloud::EXEC_Type type = EXEC_Type::EXEC_Exec);

protected:

  /**
	* 发送请求给BmobSDK后台
	*/
  void send();

  /**
  * 使用HTTP类型发送请求
  * @param type http请求类型,GET、POST、PUT、DELETE etc.
  */
  void send(network::HttpRequest::Type type);

  /**
  * HTTP请求回调函数
  * @param pSender
  * @param data 回调返回数据
  */
  virtual void onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data);

private:
  void setHeader(std::vector<string> v){}
  std::vector<string> getHeader();

  void enJson(Json::Value* value){
      BmobJsonUtil::dictionary2Json(value, &(this->m_mapData));
  }

private:
  EXEC_Type m_exec_type;

  BmobCloudDelegate* m_delegate;
  std::map<string, cocos2d::CCObject *> m_mapData;    //请求的数据//
  std::vector<string> m_header;   //请求头部//
  string m_url;
};

#endif
