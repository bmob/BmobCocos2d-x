#include "bmobobject.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"

#include "../decrypt/include/cryptutil.h"

using namespace network;
using namespace Crypt;

namespace bmobsdk{

    BmobObject::BmobObject(){
        this->m_pSaveDelegate = NULL;
        this->m_pUpdateDelegate = NULL;
        this->m_pSaveDelegate = NULL;


    }

    BmobObject::BmobObject(string tableName){
    	this->m_tableName = tableName;

        this->m_pSaveDelegate = NULL;
        this->m_pUpdateDelegate = NULL;
        this->m_pSaveDelegate = NULL;

    }

    BmobObject::~BmobObject(){

    }

    void BmobObject::save(BmobSaveDelegate* delegate){
      	if (!BmobSDKInit::getInstance()->isInitialize() ||
              BmobHttpUtil::BASE_V8_URL.empty()){
            if (delegate != NULL) {
                delegate->onSaveError(-1,"Error:SDK未初始化或初始化失败");
            }else{
                BmobLog::bmob_log("BmobObject","save","SDK didn't Initialized",BmobLog::LogType::E);
            }

      		return ;
      	}

      	this->m_pSaveDelegate = delegate;
        this->m_url = BmobHttpUtil::BASE_CREATE_URL;

      	this->send(BmobHttpUtil::HTTP_SAVE_TAG);
    }

    void BmobObject::increment(string column,int value /*= 1*/){
      //  this->addParams(column,CCInteger::create(value));
    }

    void BmobObject::setValue(string key,cocos2d::CCObject *object){
        this->enParamsToHttp(key,object);
    }

    void BmobObject::setValue(string key,CCArray* array){
        //'{"skills":{"__op":"AddUnique","objects":["flying","kungfu"]}}'
        if (array == NULL || key.empty()){
            return ;
        }

        CCDictionary* dict = CCDictionary::create();
        string op = "AddUnique";

        dict->setObject(CCString::createWithFormat("%s",op.c_str()),"__op");
        dict->setObject(array,"objects");

        this->enParamsToHttp(key,dict);
    }

    void BmobObject::update(BmobUpdateDelegate* delegate){
        this->update(this->getObjectId(),delegate);
    }


    void BmobObject::update(string objectId,BmobUpdateDelegate* delegate){
      if (!BmobSDKInit::getInstance()->isInitialize() ||
            BmobHttpUtil::BASE_V8_URL.empty()){
            if (delegate != NULL) {
              delegate->onUpdateError(-1,"Error:SDK未初始化或初始化失败");
            }else{
                BmobLog::bmob_log("BmobObject","Update","SDK didn't Initialized",BmobLog::LogType::E);
            }

          return ;
      }

        if (objectId.empty()){
            if (delegate != NULL) {
                delegate->onUpdateError(-1,"Error:objectId为空");
            }

            return ;
        }

        this->m_pUpdateDelegate = delegate;
        this->m_url = BmobHttpUtil::BASE_UPDATE_URL;
        this->m_objectId = objectId;

        /**
        * 如果是更新用户表（_User）时，是否需要先判断用户是否已经登陆
        */

        this->send(HttpRequest::Type::POST,BmobHttpUtil::HTTP_UPDATE_TAG);
    }

    void BmobObject::remove(string name){
        if (name.empty()){
            return ;
        }

        this->clear();

        CCDictionary* pDict = CCDictionary::create();
        CCString* pValue2 = CCString::create("Delete");
        pDict->setObject(pValue2, "__op");

        this->enParamsToHttp(name,pDict);
    }

    void BmobObject::removeAll(string name,CCArray* array){
        if (array == NULL || name.empty()){
            return ;
        }

        CCDictionary* dict = CCDictionary::create();
        string op = "Remove";

        dict->setObject(CCString::createWithFormat("%s",op.c_str()),"__op");
        dict->setObject(array,"objects");

        this->enParamsToHttp(name,dict);
    }

    void BmobObject::del(BmobDeleteDelegate* delegate){
        if (!BmobSDKInit::getInstance()->isInitialize() ||
              BmobHttpUtil::BASE_V8_URL.empty()){
            if (delegate != NULL) {
                delegate->onDeleteError(-1,"Error:SDK未初始化或初始化失败");
            }

            return ;
        }
        this->m_pDeleteDelegate = delegate;
        this->m_url = BmobHttpUtil::BASE_DELETE_URL;
        this->clear();

        this->send(HttpRequest::Type::POST,BmobHttpUtil::HTTP_DELETE_TAG);
    }

    void BmobObject::del(string objectId,BmobDeleteDelegate* delegate){
        if (objectId.empty()) {
          if (delegate != NULL) {
              delegate->onDeleteError(-1,"Error:objectId为空");
          }
          return ;
        }

        if (!BmobSDKInit::getInstance()->isInitialize() ||
              BmobHttpUtil::BASE_V8_URL.empty()){
            if (delegate != NULL) {
                delegate->onDeleteError(-1,"Error:SDK未初始化或初始化失败");
            }

      		  return ;
      	}

        this->m_objectId = objectId;
        this->del(delegate);
    }

    void BmobObject::add(string column,CCObject* object){
        //{"list":{"__op":"Add","objects":["person1","person2"]}}
        if (object == NULL || column.empty()){
            return ;
        }

        CCDictionary* dict = CCDictionary::create();
        string op = "Add";
        CCArray* array = CCArray::create();

        array->addObject(object);
        dict->setObject(CCString::createWithFormat("%s",op.c_str()),"__op");
        dict->setObject(array,"objects");

        this->enParamsToHttp(column,dict);
    }

    void BmobObject::add(string column,CCArray* array){
        if (column.empty() || array == NULL){
            return ;
        }

        CCDictionary* dict = CCDictionary::create();
        string op = "Add";
        dict->setObject(CCString::createWithFormat("%s",op.c_str()),"__op");
        dict->setObject(array,"objects");

        this->enParamsToHttp(column,dict);

    }


    void BmobObject::enParamsToHttp(string key,cocos2d::CCObject *object){
        this->m_mapData.insert(pair<string, CCObject *>(key, object));
    }

    CCObject* BmobObject::getParams(string key){
        std::map<string, CCObject *>::iterator it = m_mapData.find(key);
        if (it!=m_mapData.end()) {
            return it->second;
        }

        return NULL;
    }

    void BmobObject::setHeader(vector<string> v){
    	// this->m_header = v;
    }

    vector<string> BmobObject::getHeader(){
        if (this->m_header.empty()){
          this->m_header = Crypt::CryptUtil::getCryptRequestHeader(BmobSDKInit::APP_KEY);
        }

        return this->m_header;
    }

    void BmobObject::enJson(Json::Value* value){
        BmobJsonUtil::dictionary2Json(value, &(this->m_mapData));
    }

    void BmobObject::enJson(Json::Value* value,map<string,CCObject*> data){
        BmobJsonUtil::dictionary2Json(value, &data);
    }

    map<string,CCObject*> BmobObject::getSolidRequestData(string tag){
        map<string,CCObject*> temp;
        map<string,string> data = CryptUtil::getCryptRequestData();

        BmobHttpUtil::ObjectHttpType httpType = BmobHttpUtil::getObjectHttpType(tag);
        if (httpType == BmobHttpUtil::ObjectHttpType::HttpUpdate) {
            if (strcmp(m_tableName.c_str(),BmobSDKInit::USER_TABLE.c_str()) == 0) {
                string session = CCUserDefault::sharedUserDefault()->getStringForKey("user_session");
                if (!session.empty()) {
                    data.insert(pair<string,string>("sessionToken",session));
                }
            }
        }


        temp = BmobSDKUtil::mapStringToCCObject(data);
        temp.insert(pair<string, CCObject *>("client",\
      		  BmobSDKUtil::mapStringToCCDirectionary(Crypt::CryptUtil::getClientPlatomData())));
        temp.insert(pair<string,CCObject *>("timestamp",CCInteger::create(Crypt::CryptUtil::getTimeStamp())));

        if (!this->m_tableName.empty()) {
            temp.insert(pair<string,CCObject*>("c",CCString::createWithFormat("%s",this->m_tableName.c_str())));
        }

        if (!this->m_objectId.empty()) {
            temp.insert(pair<string,CCObject*>("objectId",CCString::createWithFormat("%s",this->m_objectId.c_str())));
        }

        return temp;
    }

    void BmobObject::deJson(Json::Value* value){
        this->clear();
        BmobJsonUtil::json2Dictionary(value, &(this->m_mapData));

        this->m_objectId = (*value)["objectId"].asString();
        this->m_createdAt = (*value)["createdAt"].asString();
        this->m_updatedAt = (*value)["updatedAt"].asString();
    }

    void BmobObject::send(string tag){
    	 this->send(HttpRequest::Type::POST,tag);
    }

    void BmobObject::send(HttpRequest::Type type,string tag){
        HttpRequest* req = new HttpRequest;
        req->setUrl(this->m_url.c_str());
        req->setTag(tag.c_str());
        req->setResponseCallback(this, cocos2d::SEL_CallFuncND(&BmobObject::onHttpRequestCompleted));
        req->setRequestType(type);
        req->setHeaders(getHeader());

        Json::Value dataJson;
        this->enJson(&dataJson);
        map<string,CCObject*> solid = this->getSolidRequestData(tag);

        Json::Value solidJson;
        this->enJson(&solidJson,solid);
        BmobJsonUtil::json2json(&solidJson,"data",dataJson);

        std::string data;
        data = solidJson.toStyledString();

        BmobLog::bmob_log("BmobObject::send",tag,data);

        string tdata = Crypt::CryptUtil::cryptData(data);
        req->setRequestData(tdata.c_str(), strlen(tdata.c_str()));
        /**
        * 设置连接和读取数据超时时间
        */
        HttpClient::getInstance()->setTimeoutForConnect(3000);
    		// HttpClient::getInstance()->setTimeoutForRead(3000);

        HttpClient::getInstance()->send(req);
        req->release();
    }

    void BmobObject::onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data){
        HttpResponse *response = (HttpResponse *)data;
        HttpRequest *request = response->getHttpRequest();

        /**
        * 获取http请求对应的tag类型
        */
        string tag(request->getTag());
        BmobHttpUtil::ObjectHttpType httpType = BmobHttpUtil::getObjectHttpType(tag);

        vector<char> *v = response->getResponseHeader();
      	string header(v->begin(),v->end());
      	string mothed = BmobHttpUtil::responseMethod(header);
      	// string param = BmobSDKUtil::responseHeaderToJson(header);

        BmobLog::bmob_log("BmobObject::onHttpRequestCompleted",tag,mothed);

        if (!response->isSucceed() || response->getResponseCode() == -1) {
            int errorCode = response->getResponseCode();
            string errorInfo = response->getErrorBuffer();

            /**
            * 是否是连接超时
            */
            if (errorCode != -1) {
                errorInfo = Crypt::CryptUtil::decryptData(errorInfo);
            }

            switch(httpType){
                case BmobHttpUtil::ObjectHttpType::HttpSave:{
                    if (this->m_pSaveDelegate != NULL){
                        this->m_pSaveDelegate->onSaveError(errorCode,errorInfo.c_str());
                    }
                }break;
                case BmobHttpUtil::ObjectHttpType::HttpUpdate:{
                    if (this->m_pUpdateDelegate != NULL){
                        this->m_pUpdateDelegate->onUpdateError(errorCode,errorInfo.c_str());
                    }

                }break;
                case BmobHttpUtil::ObjectHttpType::HttpDelete:{
                    if (this->m_pDeleteDelegate != NULL){
                        this->m_pDeleteDelegate->onDeleteError(errorCode,errorInfo.c_str());
                    }
                }break;
                case BmobHttpUtil::ObjectHttpType::HttpReset:{
                    if (this->m_pResetDelegate != NULL){
                        this->m_pResetDelegate->onResetError(errorCode,errorInfo.c_str());
                    }
                }break;
                case BmobHttpUtil::ObjectHttpType::HttpRequestCode:{
                    if(this->m_pRequestSMSCodeDelegate != NULL){
                        this->m_pRequestSMSCodeDelegate->onRequestDone(errorCode,errorInfo.c_str());
                    }
                }break;
                case BmobHttpUtil::ObjectHttpType::HttpResetByCode:{
                    if(this->m_pResetByMSMCodeDelegate != NULL){
                        this->m_pResetByMSMCodeDelegate->onResetDone(errorCode,errorInfo.c_str());
                    }
                }break;
                case BmobHttpUtil::ObjectHttpType::HttpEmailVerify:{
                    if (this->m_pEmailVerifyDelegate != NULL){
                        this->m_pEmailVerifyDelegate->onEmailVerifyError(errorCode,errorInfo.c_str());
                    }
                }break;
                case BmobHttpUtil::ObjectHttpType::HttpLogin:{
                    if(this->m_pLoginDelegate != NULL){
                        this->m_pLoginDelegate->onLoginDone(errorCode,errorInfo.c_str());
                    }
                }break;
                default:break;
            }

            return;

        }else{

            std::vector<char> *buffer = response->getResponseData();
            std::string temp((*buffer).begin(),(*buffer).end());
            string data = Crypt::CryptUtil::decryptData(temp);

            BmobLog::bmob_log("BmobObject::onHttpRequestCompleted",tag,data);
            // if (m_sTag == kTagHttpEndpoint) {
            //     isSuccess = true;
            //     bmobResult = new CCString(str);
            // }else{
            //     str = unGzip(str);

            switch(httpType){
                case BmobHttpUtil::ObjectHttpType::HttpUpdate:{
                    if (this->m_pUpdateDelegate != NULL){
                        this->m_pUpdateDelegate->onUpdateSucess(data.c_str());
                    }
                }break;
                case BmobHttpUtil::ObjectHttpType::HttpDelete:{
                    if (this->m_pDeleteDelegate != NULL){
                        this->m_pDeleteDelegate->onDeleteSucess(data.c_str());
                    }
                }break;
                case BmobHttpUtil::ObjectHttpType::HttpReset:{
                    if (this->m_pResetDelegate != NULL){
                        this->m_pResetDelegate->onResetSucess(data.c_str());
                    }
                }break;
                 case BmobHttpUtil::ObjectHttpType::HttpRequestCode:{
                    if(this->m_pRequestSMSCodeDelegate != NULL){
                        this->m_pRequestSMSCodeDelegate->onRequestDone(200,data.c_str());
                    }
                }break;
                 case BmobHttpUtil::ObjectHttpType::HttpResetByCode:{
                    if(this->m_pResetByMSMCodeDelegate != NULL){
                        this->m_pResetByMSMCodeDelegate->onResetDone(200,data.c_str());
                    }
                }break;
                case BmobHttpUtil::ObjectHttpType::HttpEmailVerify:{
                    if (this->m_pEmailVerifyDelegate != NULL){
                        this->m_pEmailVerifyDelegate->onEmailVerifySucess(data.c_str());
                    }
                }break;

                default:{
                    Json::Reader reader;
                    Json::Value value;
                    if (!reader.parse(data, value)) {
                        //parse error
                        return;
                    }else{
                        switch (httpType) {
                          case BmobHttpUtil::ObjectHttpType::HttpSave:{
                              if (strcmp(this->m_tableName.c_str(),BmobSDKInit::USER_TABLE.c_str()) == 0){
                                  string objectId = value["data"]["objectId"].asString();
                                  string session = value["data"]["sessionToken"].asString();
                                  CCUserDefault::sharedUserDefault()->setStringForKey("user_id",objectId);
                                  CCUserDefault::sharedUserDefault()->setStringForKey("user_session",session);
                              }
                              this->m_objectId = value["data"]["objectId"].asString();
                              BmobLog::bmob_log("BmobObject::onHttpRequestCompleted","objectID",this->m_objectId);
                              if (this->m_pSaveDelegate != NULL){
                                  this->m_pSaveDelegate->onSaveSucess(data.c_str());
                              }

                          }break;
                          case BmobHttpUtil::ObjectHttpType::HttpLogin:{
                              /**
                              * 登陆获取sessionToken
                              */
                              string objectId = value["data"]["objectId"].asString();
                              string session = value["data"]["sessionToken"].asString();
                              CCUserDefault::sharedUserDefault()->setStringForKey("user_id",objectId);
                              CCUserDefault::sharedUserDefault()->setStringForKey("user_session",session);

                              if(this->m_pLoginDelegate != NULL){
                                  this->m_pLoginDelegate->onLoginDone(200,data.c_str());
                              }
                          }break;
                        }
                    }
                }break;
            }
        }
    }
}
