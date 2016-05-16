/**
* create by zhou,2016-01-18
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
#include "../util/bmobsdkutil.h"
#include "bmobSDKinit.h"

using namespace std;
using namespace bmobutil;
using namespace bmobdelegate;
USING_NS_CC;

namespace bmobsdk{
    class BmobCloud:public CCObject{
    public:
        BmobCloud();
        ~BmobCloud();

        /**
        * 执行云端代码
        * 注：当执行创建云端代码的时候，参数中存储的是方法的主题，其中使用键值的对应关系
        * 键为code，值是代码，param 仅存储一个值;如果调用的是创建代码，那么cloudName
        * 传递NULL即可
        * @param cloudName  string 云端代码的方法名，如果是创建代码，传递NULL
        * @param param   map<string,string>   云端代码的参数
        * @param  delegate  BmobCloudDelegate* 代码执行的回调函数
        * @param  type BmobCloud::EXEC_Type (默认是EXEC_Exec)     执行的操作，执行代码、创建代码、删除代码
        * @return
        */
        void execCloudCode(string cloudName,std::map<string, CCObject*> param,\
          BmobCloudDelegate *delegate,BmobHttpUtil::CloudHttpType
          type = BmobHttpUtil::CloudHttpType::HttpExec);

    protected:

        /**
        * 发送默认的POST请求给BmobSDK后台
        * @param tag 对应http请求的tag
        * @return
        */
        void send(string tag);

        /**
        * 使用HTTP类型发送请求
        * @param type HttpRequest::Type http请求类型,GET、POST、PUT、DELETE etc.
        * @param tag 对应http请求的tag
        * @return
        */
        void send(network::HttpRequest::Type type,string tag);

        /**
        * 获取固定的请求数据
        */
        map<string,CCObject*> getSolidRequestData();

        /**
        * HTTP请求回调函数
        * @param pSender CCNode*
        * @param data void* 云端代码http请求的回调返回数据
        * @return
        */
        virtual void onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data);

    private:
        /**
        * 设置云端代码的HTTP请求头部
        * @param v vector<string>
        * @return
        */
        inline void setHeader(std::vector<string> v){
          this->m_header = v;
        }
        /**
        * 得到云端代码HTTP请求头部
        * @param void
        * @return vector<string>
        */
        std::vector<string> getHeader();

        /**
        * @param value Json::value
        * @return
        */
        inline void enJson(Json::Value* value){
            BmobJsonUtil::dictionary2Json(value, &(this->m_mapData));
        }

        /**
        * 将data的数据编码到value中
        * @param value 目标存储空间
        * @param data  编码的数据
        */
        inline void enJson(Json::Value* value,map<string,CCObject*> data){
            BmobJsonUtil::dictionary2Json(value, &data);
        }

    private:

        std::map<string, cocos2d::CCObject *> m_mapData;    //请求的数据//
        std::vector<string> m_header;   //请求头部//
        BmobCloudDelegate* m_delegate;
        string m_url;
    };
}

#endif
