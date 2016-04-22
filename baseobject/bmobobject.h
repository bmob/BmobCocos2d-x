/**
* create by zh_u 2015-10-25
* BmobObject 是所有自定义对象的基类
*/

#ifndef BMOBSDK_BMOBOBJECT_H_
#define BMOBSDK_BMOBOBJECT_H_

#include <iostream>
#include <string>
#include <vector>
#include "cocos2d.h"
#include "network/HttpRequest.h"

#include "../delegate/bmobdelegate.h"
#include "../jsoncpp/include/json.h"
#include "../util/bmobsdkutil.h"
#include "bmobSDKinit.h"


using namespace std;
using namespace bmobdelegate;
using namespace bmobutil;
USING_NS_CC;

namespace bmobsdk{
	class BmobObject:public cocos2d::CCObject{
	public:
		/**
		* 使用对象名来构造函数，也就是后台对应的表名
		* @param tableName 对象表名
		*/
		BmobObject(string tableName);
		/**
		* 虚构函数
		*/
		virtual ~BmobObject();

		/**
		* 调用该方法将对象数据保存到SDK后台
		* @param delegate 保存对象回调接口
		* @return
		*/
		virtual void save(BmobSaveDelegate* delegate);

		/**
		* 更新对象调用方法,该方法值针对整型数据进行操作
		* @param column 更新的字段名或者列名
		* @param value 要更新的值，默认增加1
		* @return
		*/
		virtual void increment(string column,int value = 1);
		/**
		* 设置要更新的字段和值
		* @param key    设置的字段名或者列名
		* @param object 需要设置的值
		* @return
		*/
		void setValue(string key,cocos2d::CCObject *object);
		/**
		* 对数组的操作
		* @param key    要设置的字段名或者列名
		* @param array  数组值
		* @return
		*/
		void setValue(string key,cocos2d::CCArray* array);
		/**
		* 使用objectId更新BmobSDK后台数据
		* @param ObjectId   更新数据对应的objectId
		* @param delegate   更新数据回调接口
		* @return
		*/
		virtual void update(string objectId,BmobUpdateDelegate* delegate);
		/**
		* 更新BmobSDK后台数据
		* @param    delegate    更新数据回调接口
		*/
		virtual void update(BmobUpdateDelegate* delegate);
		/**
		* 设置要移除后台数据对应的字段
		* @param name   字段名
		* @return
		*/
		virtual void remove(string name);
		/**
		* 设置要移除后台数据对应的字段
		* @param array  要移除的字段数组
		* @return
		*/
		virtual void removeAll(string name,CCArray* array);
		/**
		*  删除BmobSDK后台数据
		* @param    delegate    删除数据回调接口
		* @return
		*/
		virtual void del(BmobDeleteDelegate* delegate);
		/**
		* 直接使用objectId来删除数据
		* @param objectId 要删除数据对应的ObjectID
		* @param delegate 删除数据的回调接口
		* @return
		*/
		virtual void del(string objectId,BmobDeleteDelegate* delegate);

		/**
		* 向BmobSDK中添加包含一个数据的数组
		* @param column  字段名
		* @param object  对应字段名的值
		* @return
		*/
		virtual void add(string column,CCObject* object);
		/**
		* 向BmobSDK中添加包含多个数据的数组
		* @param column 要添加的字段名
		* @param array 要添加的数组值
		* @return
		*/
		virtual void add(string column,CCArray* array);
		/**
		* 将对象需要保存的数据压到HTTP请求中
		* @param key 要在后台保存的字段
		* @param object  要在后台保存的字段对应的值
		* @return
		*/
		virtual void enParamsToHttp(std::string key,cocos2d::CCObject *object);

		/**
		* 获取当前HTTP请求的头部
		* @return vector<string>
		*/
		virtual vector<string> getHeader();

		/**
		* 获取key对应的数据
		* @param key 字段名
		* @return CCObject*
		*/
		virtual CCObject* getParams(string key);
		/**
		* 将发送给服务端数据转换成json数据
		* @param value
		* @return
		*/
		virtual void enJson(Json::Value* value);

		/**
		* 将data数据转换城json数据存储到value中
		* @param value Json::Value
		* @param data map<string,CCObject*>
		* @return
		*/
		virtual void enJson(Json::Value* value,map<string,CCObject*> data);
		/**
		* 将Json数据解压成map<string,CCObject*>
		* @param value 要解析的Json数据
		* @return
		*/
		virtual void deJson(Json::Value* value);

		/**
		* 清楚请求缓存中的数据
		* @return
		*/
		void clear(){
		this->m_mapData.clear();
		}

	protected:
	    /**
	    *
	    */
	    BmobObject();
	    /**
	  	* 设置HTTP请求的头部
	    * @param v 自定义HTTP的头部
			* @return
	  	*/
	  	virtual void setHeader(vector<string> v);

	    /**
	    * 设置请求中的固定数据
	    * @param tag
	    * @return map<string,CCObject*>
	    */
	    map<string,CCObject*> getSolidRequestData(string tag);

	protected:
		/**
		* HTTP请求回调函数
		* @param pSender
		* @param data 回调返回数据
		* @return
		*/
		virtual void onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data);

		/**
		* 使用HTTP类型发送请求
		* @param type http请求类型,GET、POST、PUT、DELETE etc.
		* @param 对应http请求的tag
		* @return
		*/
		void send(network::HttpRequest::Type type,string tag);

		/**
		* 发送请求给BmobSDK后台
		* @param tag 对应http请求的tag
		* @return
		*/
	  void send(string tag);

	protected:
	 	CC_SYNTHESIZE(string, m_objectId, ObjectId);   	//对象对应BmobSDK后台ObjectId//
	    CC_SYNTHESIZE(string,m_createdAt,CreatedAt);    //后台对象创建的时间//
	    CC_SYNTHESIZE(string,m_updatedAt,UpdatedAt);    //后台对象更新的时间//
		CC_SYNTHESIZE(string,m_tableName,TableName);    //对象对应的表名//
		CC_SYNTHESIZE(string,m_session,Session);        //用户对象对应的session//
		CC_SYNTHESIZE(string,m_url,Url);                //请求的URL//
	    CC_SYNTHESIZE(string,m_ACL,ACL);

		/**
		* 通过SMS码重置密码的回调接口
		*/
		CC_SYNTHESIZE(BmobResetPasswordByCodeDelegate*,m_pResetByMSMCodeDelegate,ResetByMSMCodeDelegate);
		/**
		* 请求SMS码回调接口
		*/
		CC_SYNTHESIZE(BmobRequestSMSCodeDelegate*,m_pRequestSMSCodeDelegate,RequestSMSCodeDelegate);
		/**
		* 通过邮箱验证的回调接口
		*/
		CC_SYNTHESIZE(BmobEmailVerifyDelegate*,m_pEmailVerifyDelegate,EmailVerifyDelegate);
		/**
		* 重置密码回调接口
		*/
		CC_SYNTHESIZE(BmobResetPasswordDelegate*,m_pResetDelegate,ResetDelegate);
		/**
		* 更新对象回调接口
		*/
		CC_SYNTHESIZE(BmobUpdateDelegate*,m_pUpdateDelegate,UpdateDelegate);
		/**
		* 删除对象回调接口
		*/
		CC_SYNTHESIZE(BmobDeleteDelegate*,m_pDeleteDelegate,DeleteDelegate);
		/**
		* 登录回调接口
		*/
		CC_SYNTHESIZE(BmobLoginDelegate*,m_pLoginDelegate,LoginDelegate);
		/**
		* 保存对象回调接口
		*/
	    CC_SYNTHESIZE(BmobSaveDelegate*,m_pSaveDelegate,SaveDelegate);

	    std::map<string, cocos2d::CCObject *> m_mapData;
	    std::vector<string> m_header;
	};
}

#endif
