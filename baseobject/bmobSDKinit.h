/**
* create zh_u 2015-10-25
* BmobSDK环境初始化对象
*/

#ifndef BMOBSDK_BMOBSDKINIT_H_
#define BMOBSDK_BMOBSDKINIT_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include "cocos2d.h"
#include "network/HttpRequest.h"

#include "../jsoncpp/include/json.h"
#include "../delegate/bmobdelegate.h"
#include "../util/bmobsdkutil.h"

using namespace std;
using namespace bmobdelegate;
using namespace bmobutil;
USING_NS_CC;

namespace bmobsdk{
	class BmobSDKInit:public cocos2d::CCObject{
	public:
		static BmobSDKInit* getInstance();
		/**
		* 使用appID和appKey初始化环境
		* @param app_id string
		* @param app_key string
		* @return
		*/
		void initialize(string app_id,BmobInitDelegate* delegate);
		/**
		* 查询环境是否已经初始化
		* @param
		* @return bool
		*/
		bool isInitialize();

		/**
		* 请求密钥
		* @param appkey string
		* @param version BmobInitDelegate*
		* @return
		*/
		void getSecretKey(BmobInitDelegate* delegate);

		/**
		* 获取服务器时间
		* @param delegate
		* @return
		*/
		void getTimeStamp(BmobGetTimeDelegate* delegate);

		/**
		* 上传设备信息
		* @param delegate
		* @return
		*/
		void uploadDeviceInfo(map<string,CCObject*> info,BmobUpDeviceInfoDelegate* delegate);

	protected:
		/**
		*
		*/
		void onInit();
		/**
		* @param type HttpRequest::Type
		* @return
		*/
		void send(network::HttpRequest::Type type,string tag);
		/**
		* 网络请求回调函数
		* @param pSender CCNode
		* @param data void*
		* @return
		*/
		void onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data);

		/**
		* 将发送给服务端数据转换成json数据
		* @param value Json::Value*
		* @return
		*/
		void enJson(Json::Value* value);

		/**
	    * 将data数据转换城json数据存储到value中
	    * @param value Json::Value
	    * @param data map<string,CCObject*>
	    * @return
	    */
	    virtual void enJson(Json::Value* value,map<string,CCObject*> data);
		/**
		* 将Json数据解压成map<string,CCObject*>
		* @param value Json::Value*
		* @return
		*/
		void deJson(Json::Value* value);

		/**
		* @param void
		* @return map<String,CCObject*>
		*/
		map<string,CCObject*> setRequestData(BmobHttpUtil::InitHttpType httpType \
				= BmobHttpUtil::InitHttpType::HttpSecret);

		/**
		* 获取http请求头部
		*/
		vector<string> getHeader(BmobHttpUtil::InitHttpType httpType \
				= BmobHttpUtil::InitHttpType::HttpSecret);

	public:
		static string USER_TABLE;
		static string REST_KEY;			//SDK APP_ID//
		static string APP_KEY;			//SDK APP_KEY //


	private:
		static const int MAX_INIT_TIMES = 1;
		static BmobSDKInit* bmobSDKInit;
		static int initialize_times;//初始化次数，最多3次
		static int initialize_success;

		string m_url;
		map<string,CCObject*> m_mapData;

		BmobInitDelegate* m_pDelegate;
		BmobGetTimeDelegate* m_pGetDelegate;
		BmobUpDeviceInfoDelegate *m_pUpdateDelegate;
	};
}
#endif
