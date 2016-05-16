#include "bmobSDKinit.h"

#include "network/HttpClient.h"
#include "network/HttpResponse.h"
#include "../decrypt/include/cryptutil.h"

using namespace network;
using namespace Crypt;

namespace bmobsdk{
	string BmobSDKInit::APP_KEY;
	string BmobSDKInit::USER_TABLE = "_User";


	BmobSDKInit* BmobSDKInit::bmobSDKInit = NULL;
	int BmobSDKInit::initialize_times = 0;
	int BmobSDKInit::initialize_success = 0;


	BmobSDKInit* BmobSDKInit::getInstance(){
		if (bmobSDKInit == NULL) {
			bmobSDKInit = new BmobSDKInit();
			// bmobSDKInit->autorelease();
		}

		return bmobSDKInit;
	}

	void BmobSDKInit::initialize(string app_key,BmobInitDelegate* delegate){
		if (app_key.empty()) {
			if (delegate != NULL) {
				delegate->onInitFail(-1,"Error:AppKey为空");
			}

			BmobLog::bmob_log("BmobSDKInit","initialize","app_key is NULL",BmobLog::LogType::E);
		}

		BmobSDKInit::APP_KEY = app_key;
		this->getSecretKey(delegate);
	}

	bool BmobSDKInit::isInitialize(){
		if (!initialize_success){
			return false;
		}

		return true;
	}

	void BmobSDKInit::onInit(){
		this->m_url = BmobHttpUtil::BASE_INIT_URL;

		this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_INIT_TAG);
	}

	vector<string> BmobSDKInit::getHeader(BmobHttpUtil::InitHttpType httpType \
		/* = BmobHttpUtil::InitHttpType::HttpSecret */){
		vector<string> temp;
		if (httpType == BmobHttpUtil::InitHttpType::HttpSecret) {
			temp = Crypt::CryptUtil::getSecretHeader();
		}else{
			temp = Crypt::CryptUtil::getCryptRequestHeader(BmobSDKInit::APP_KEY);
		}

		return temp;
	}

	void BmobSDKInit::enJson(Json::Value* value){
	    BmobJsonUtil::dictionary2Json(value, &(this->m_mapData));
	}

	void BmobSDKInit::enJson(Json::Value* value,map<string,CCObject*> data){
    	BmobJsonUtil::dictionary2Json(value, &data);
	}

	void BmobSDKInit::deJson(Json::Value* value){
	    BmobJsonUtil::json2Dictionary(value, &(this->m_mapData));
	}

	map<string,CCObject*> BmobSDKInit::setRequestData(BmobHttpUtil::InitHttpType httpType \
		/* = BmobHttpUtil::InitHttpType::HttpSecret */){

		map<string,string> temp;
		map<string,CCObject*> data;

		if (httpType == BmobHttpUtil::InitHttpType::HttpSecret) {
			temp = Crypt::CryptUtil::getSecretRequestData(BmobSDKInit::APP_KEY);
		}else{
			temp = Crypt::CryptUtil::getCryptRequestData();
		}

		data = BmobSDKUtil::mapStringToCCObject(temp);

		if (httpType != BmobHttpUtil::InitHttpType::HttpSecret &&
			httpType != BmobHttpUtil::InitHttpType::HttpInit) {
			data.insert(pair<string,CCObject*>("timestamp",CCInteger::create(Crypt::CryptUtil::getTimeStamp())));
		}

		data.insert(pair<string, CCObject *>("client",\
			BmobSDKUtil::mapStringToCCDirectionary(Crypt::CryptUtil::getClientPlatomData())));

		return data;
	}

	void BmobSDKInit::send(network::HttpRequest::Type type,string tag){
		HttpRequest* req = new HttpRequest;
	  	req->setUrl(this->m_url.c_str());
	  	req->setResponseCallback(this, cocos2d::SEL_CallFuncND(&BmobSDKInit::onHttpRequestCompleted));
	  	req->setRequestType(type);
		req->setTag(tag.c_str());

		BmobHttpUtil::InitHttpType httpType = BmobHttpUtil::getInitHttpType(tag);
		req->setHeaders(getHeader(httpType));
		map<string,CCObject*> soildData;
		switch (httpType) {
			case BmobHttpUtil::InitHttpType::HttpSecret:{
				soildData = this->setRequestData(BmobHttpUtil::InitHttpType::HttpSecret);
			}break;
			case BmobHttpUtil::InitHttpType::HttpInit:{
				soildData = this->setRequestData(BmobHttpUtil::InitHttpType::HttpInit);
			}break;
			case BmobHttpUtil::InitHttpType::HttpTimeStamp:{
				soildData = this->setRequestData(BmobHttpUtil::InitHttpType::HttpTimeStamp);
			}break;
			case BmobHttpUtil::InitHttpType::HttpUpDevice:{
				soildData = this->setRequestData(BmobHttpUtil::InitHttpType::HttpUpDevice);
			}break;
		}

		Json::Value params;
		this->enJson(&params);

		BmobLog::bmob_log("BmobSDKInit::send",tag,params.toStyledString());
		
		Json::Value solidJson;
		this->enJson(&solidJson,soildData);
		BmobJsonUtil::json2json(&solidJson,"data",params);

		std::string data;
		data = solidJson.toStyledString();

		string rData;
		if (httpType == BmobHttpUtil::InitHttpType::HttpSecret) {
			rData = Crypt::CryptUtil::cryptSecretRequestData(data);
		}else{
			rData = Crypt::CryptUtil::cryptData(data);
		}


	  	req->setRequestData(rData.c_str(), rData.size());

		/**
		* 设置连接和读取数据超时时间
		*/
		HttpClient::getInstance()->setTimeoutForConnect(3000);
		// HttpClient::getInstance()->setTimeoutForConnect(3000);

		HttpClient::getInstance()->send(req);
		req->release();
	}

	void BmobSDKInit::onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data){
		HttpResponse *response = (HttpResponse *)data;
		HttpRequest * request = response->getHttpRequest();

		vector<char> *v = response->getResponseHeader();
		string header(v->begin(),v->end());
		string mothed = BmobHttpUtil::responseMethod(header);
		string param = BmobHttpUtil::responseHeaderToJson(header);

		/**
		* 获取对应的http的tag类型
		*/
		string tag(request->getTag());
		BmobHttpUtil::InitHttpType httpType = BmobHttpUtil::getInitHttpType(tag);

		BmobLog::bmob_log("BmobSDKInit::" + tag,"mothed",mothed);

		string key2;
		if (httpType == BmobHttpUtil::InitHttpType::HttpSecret) {
			Json::Reader reader;
			Json::Value value;

			if (!reader.parse(param, value)) {
				//parse error
			}else{
				key2 = value["Response-Id"].asString();
			}
		}

	  	if (!response->isSucceed()) {
			/**
			* 错误码返回-1代表超时
			*/
			int errorCode = response->getResponseCode();
			string errorInfo = response->getErrorBuffer();

			if (httpType == BmobHttpUtil::InitHttpType::HttpSecret) {
				BmobSDKInit::initialize_times++;
				if (BmobSDKInit::initialize_times < BmobSDKInit::MAX_INIT_TIMES) {
					this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_SECRET_TAG);
					return ;
				}
			}


			std::vector<char> *buffer = response->getResponseData();
			std::string str((*buffer).begin(),(*buffer).end());
			std::string decrypt ;

			if (errorCode == -1) {
				if (errorInfo.empty()) {
					errorInfo = "Error:网络连接或超时错误";
				}
				BmobLog::bmob_log("BmobSDKInit",tag,"网络连接或超时错误",BmobLog::LogType::E);
			}
			BmobLog::bmob_log("BmobSDKInit",tag,str + "   " + errorInfo,BmobLog::LogType::E);
			switch (httpType) {
				case BmobHttpUtil::InitHttpType::HttpSecret:{
					if (errorCode != -1 && !str.empty()) {
						const char* p = key2.c_str();
						int len = key2.size() - 16;
						char lk[17] = {0};
						if (len > 0) {
							memcpy(lk,p + len,16);
						}

						string k(lk);
						Crypt::CryptUtil::set2(k);
						decrypt = Crypt::CryptUtil::decryptSecretData(str);
					}else{
						decrypt = errorInfo;
					}

					if (this->m_pDelegate != NULL) {
							this->m_pDelegate->onInitFail(errorCode,decrypt.c_str());
						}

					}break;

				case BmobHttpUtil::InitHttpType::HttpInit:{
					if (errorCode != -1 && !str.empty()) {
						decrypt = Crypt::CryptUtil::decryptData(str);
					}else{
						decrypt = errorInfo;
					}

					if (this->m_pDelegate != NULL) {
						this->m_pDelegate->onInitFail(errorCode,decrypt.c_str());
					}

				}break;

				case BmobHttpUtil::InitHttpType::HttpTimeStamp:{
					if (errorCode != -1 && !str.empty()) {
						decrypt = Crypt::CryptUtil::decryptData(str);
					}else{
						decrypt = errorInfo;
					}
					if (this->m_pGetDelegate != NULL) {
						this->m_pGetDelegate->onGetTime(errorCode,decrypt.c_str());
					}
				}break;
				case BmobHttpUtil::InitHttpType::HttpUpDevice:{
					if (errorCode != -1 && !str.empty()) {
						decrypt = Crypt::CryptUtil::decryptData(str);
					}else{
						decrypt = errorInfo;
					}
					if (this->m_pUpdateDelegate != NULL) {
						this->m_pUpdateDelegate->onUpload(errorCode,decrypt.c_str());
					}
				}break;
				default:break;
			}

			BmobLog::bmob_log("BmobSDKInit",tag,decrypt,BmobLog::LogType::E);
	    }else{
			std::vector<char> *buffer = response->getResponseData();
			std::string str((*buffer).begin(),(*buffer).end());
			std::string decrypt;

            int code = 301;
            string msg = "";

			/**
			* 获取secret和初始化的解码方式是不一样的
			*/
			switch (httpType) {
				case BmobHttpUtil::InitHttpType::HttpSecret:{
					const char* p = key2.c_str();
					int len = key2.size() - 16;
					char lk[17] = {0};
					if (len > 0) {
						memcpy(lk,p + len,16);
					}

					string k(lk);
					Crypt::CryptUtil::set2(k);
					try{
						decrypt = Crypt::CryptUtil::decryptSecretData(str);
		            }catch(exception e){
		                decrypt = "返回数据出错";
		            }   

				}break;
				default:{
					try{
						decrypt = Crypt::CryptUtil::decryptData(str);
		            }catch(exception e){
		                decrypt = "返回数据出错";
		            }   
				}break;
			}
			

			Json::Reader reader;
			Json::Value value;
			if (!reader.parse(decrypt, value)) {
				msg = decrypt;
			}else{
				code = value["result"]["code"].asInt();
				msg = value["result"]["message"].asString();
			}

			switch (httpType) {

				case BmobHttpUtil::InitHttpType::HttpSecret:{
					if(code == 200){
						string ke = value["data"]["secretKey"].asString();
						Crypt::CryptUtil::setS(ke);
						this->onInit();
					}else {
						this->m_pDelegate->onInitFail(code,"初始化失败");
					}
				}break;

				case BmobHttpUtil::InitHttpType::HttpInit:{
					initialize_success = 1;

					string api = value["data"]["api"].asString();
					string file = value["data"]["file"].asString();
					int timestamp = value["data"]["timestamp"].asInt();
					if (!api.empty()) {
						BmobHttpUtil::BASE_V8_URL = api;
					}

					if (!file.empty()) {
						BmobHttpUtil::BASE_FILE_URL = file;
					}

					if (this->m_pDelegate != NULL) {
						if(code == 200){
							this->m_pDelegate->onInitSuccess(decrypt.c_str());
						}else {
							this->m_pDelegate->onInitFail(code,msg.c_str());
						}
					}

				}break;

				case BmobHttpUtil::InitHttpType::HttpTimeStamp:{
					if (this->m_pGetDelegate != NULL) {
						if (code != 200)
						{
							this->m_pGetDelegate->onGetTime(code,decrypt.c_str());
						}else{
							this->m_pGetDelegate->onGetTime(code,msg.c_str());
						}
					}
				}break;

				case BmobHttpUtil::InitHttpType::HttpUpDevice:{
					if (this->m_pUpdateDelegate != NULL) {
						if(code != 200){
							this->m_pUpdateDelegate->onUpload(200,decrypt.c_str());
						}else {
							this->m_pUpdateDelegate->onUpload(code,msg.c_str());
						}
					}
					
				}break;
			}
				
		}
	}

	void BmobSDKInit::getSecretKey(BmobInitDelegate* delegate){
		if (this->isInitialize()) {
			if (delegate != NULL) {
				BmobLog::bmob_log("BmobSDKInit","getSecretKey","SDK已初始化",BmobLog::LogType::E);
				delegate->onInitFail(-1,"Error:SDK已初始化");
				return ;
			}
			
		}

		BmobSDKInit::initialize_times = 0;
		this->m_pDelegate = delegate;
		this->m_url = BmobHttpUtil::BASE_SECRET_URL;

		this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_SECRET_TAG);
	}

	void BmobSDKInit::getTimeStamp(BmobGetTimeDelegate* delegate){
		if (!this->isInitialize()) {
			BmobLog::bmob_log("BmobSDKInit","getTimeStamp","SDK没有初始化",BmobLog::LogType::E);
			if (delegate != NULL) {
				delegate->onGetTime(-1,"Error:SDK没有初始化");
				return ;
			}
		}

		this->m_pGetDelegate = delegate;
		this->m_url = BmobHttpUtil::BASE_GETTIMESTAMP_URL;

		this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_TIMESTAMP_TAG);
	}

	void BmobSDKInit::uploadDeviceInfo(map<string,CCObject*> info,BmobUpDeviceInfoDelegate* delegate){
		if (!this->isInitialize()) {
			BmobLog::bmob_log("BmobSDKInit","uploadDeviceInfo","SDK没有初始化",BmobLog::LogType::E);
			if (delegate != NULL) {
				delegate->onUpload(-1,"Error:SDK没有初始化");
				return ;
			}
		}


		this->m_pUpdateDelegate = delegate;
		this->m_url = BmobHttpUtil::BASE_UPDEVICE_URL;
		this->m_mapData = info;

		this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_UPDEVICE_TAG);
	}
}
