#include "bmobquery.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"
#include "network/HttpRequest.h"
#include "../decrypt/include/cryptutil.h"

using namespace Crypt;
using namespace network;

namespace bmobsdk{
    BmobQuery::BmobQuery(string tableName):
    BmobQueryInterafce(tableName){

    }

    BmobQuery::~BmobQuery(){

    }

    void BmobQuery::findObjects(BmobFindDelegate* delegate){
        // if (!BmobSDKInit::getInstance()->isInitialize()　||
        //     BmobHttpUtil::BASE_V8_URL.empty()){
        //     if (delegate != NULL) {
        //         delegate->onFindError(-1,"Error:SDK未初始化或初始化失败");
        //     }
        //
        //     return ;
        // }


      	this->m_pFindDelegate = delegate;
        this->m_url = BmobHttpUtil::BASE_FIND_URL;

      	this->query(BmobHttpUtil::HTTP_FIND_TAG);
    }

    void BmobQuery::findObjects(string tableName,BmobFindDelegate* delegate){
        if (!BmobSDKInit::getInstance()->isInitialize()
            || BmobHttpUtil::BASE_V8_URL.empty()){
            if (delegate != NULL) {
                delegate->onFindError(-1,"Error:SDK未初始化或初始化失败");
            }

            return ;
        }

        this->m_tableName = tableName;
        this->m_pFindDelegate = delegate;
        this->m_url = BmobHttpUtil::BASE_FIND_URL;

        this->query(BmobHttpUtil::HTTP_FIND_TAG);
    }

    void BmobQuery::getObject(string objectId,BmobGetDelegate* delegate){
        if (!BmobSDKInit::getInstance()->isInitialize() ||
            BmobHttpUtil::BASE_V8_URL.empty()){
            if (delegate != NULL) {
                delegate->onGetError(-1,"Error:SDK未初始化或初始化失败");
            }

            return ;
        }

        if (objectId.empty()){
        	return ;
        }

        this->m_objectId = objectId;
        this->m_pGetDelegate = delegate;
        this->m_url = BmobHttpUtil::BASE_FIND_URL;

        this->query(BmobHttpUtil::HTTP_GET_TAG);
    }

    void BmobQuery::count(BmobCountDelegate* delegate,bool sign /*= false*/){
        if (!BmobSDKInit::getInstance()->isInitialize() ||
            BmobHttpUtil::BASE_V8_URL.empty()){
            if (delegate != NULL) {
                delegate->onCountError(-1,"Error:SDK未初始化或初始化失败");
            }
            return ;
        }

        this->m_pCountDelegate = delegate;
        this->m_url = BmobHttpUtil::BASE_FIND_URL;
        this->clear();
        this->m_mapData.insert(pair<string,CCObject*>("count",CCBool::create(sign)));

        this->query(BmobHttpUtil::HTTP_COUNT_TAG);
    }

    void BmobQuery::findStatistics(BmobStaticsDelegate* delegate){
        if (!BmobSDKInit::getInstance()->isInitialize() ||
            BmobHttpUtil::BASE_V8_URL.empty()){
            if (delegate != NULL) {
                delegate->onStaticsError(-1,"Error:SDK未初始化或初始化失败");
            }

            return ;
        }

        this->m_pStaticsDelegate = delegate;
        this->m_url = BmobHttpUtil::BASE_FIND_URL;

        this->query(BmobHttpUtil::HTTP_STATISTICS_TAG);
    }

    void BmobQuery::BSQLFindObjects(string bql,CCObject* values,BmobBQLDelegate* delegate){
      if (!BmobSDKInit::getInstance()->isInitialize() ||
          BmobHttpUtil::BASE_V8_URL.empty()){
          if (delegate != NULL) {
              delegate->onBQLFailure(-1,"Error:SDK未初始化或初始化失败");
          }

          return ;
      }

      this->m_pBQLDelegate = delegate;
      this->m_url = BmobHttpUtil::BASE_BQL_URL;

      this->m_mapData.insert(pair<string,CCObject*>("bql",
                      CCString::createWithFormat("%s",bql.c_str())));
      this->m_mapData.insert(pair<string,CCObject*>("values",values));

      this->query(BmobHttpUtil::HTTP_BQL_TAG);
    }

    void BmobQuery::addWhereEqualTo(string seg,CCObject *object){
        if (object == NULL){
            return ;
        }
        this->m_whereData.insert(pair<string,CCObject*>(seg,object));
    }

    void BmobQuery::addWhereNotEqualTo(string seg,CCObject *object){
        //where={"playerName":{"$nin":["Jonathan Walsh","Dario Wunsch","Shawn Simon"]}}'
        if (object == NULL){
            return ;
        }
        CCDictionary* pDict = CCDictionary::create();
        CCArray* array = CCArray::create();
        array->addObject(object);
        pDict->setObject(array, "$nin");

        this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
    }

    void BmobQuery::addWhereGreatorThan(string seg,CCObject *object){

    }

    void BmobQuery::addWhereLessThan(string seg,CCObject *object){
        CCInteger* value = dynamic_cast<CCInteger*>(object);
        if (!value){
            return ;
        }

        CCDictionary* pDict = CCDictionary::create();
        pDict->setObject(value, "$lt");

        this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
    }

    void BmobQuery::addWhereLessThanOrEqualTo(string seg,CCObject *object){
        CCInteger* value = dynamic_cast<CCInteger*>(object);
        if (!value){
            return ;
        }

        CCDictionary* pDict = CCDictionary::create();
        pDict->setObject(value, "$lte");

        this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
    }

    void BmobQuery::addWhereGreaterThan(string seg,CCObject *object){
         CCInteger* value = dynamic_cast<CCInteger*>(object);
        if (!value){
            return ;
        }

        CCDictionary* pDict = CCDictionary::create();
        pDict->setObject(value, "$gt");

        this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
    }

    void BmobQuery::addWhereGreaterThanOrEqualTo(string seg,CCObject *object){
        CCInteger* value = dynamic_cast<CCInteger*>(object);
        if (!value){
            return ;
        }

        CCDictionary* pDict = CCDictionary::create();
        pDict->setObject(value, "$gte");

        this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
    }

    void BmobQuery::addWhereContainedIn(string seg,CCObject* array){
        CCArray* arr = dynamic_cast<CCArray*>(array);
        if (!arr){
            return ;
        }

        CCDictionary* pDict = CCDictionary::create();
        pDict->setObject(arr, "$in");

        this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
    }

    void BmobQuery::addWhereNotContainedIn(string seg,CCObject* array){
        CCArray* arr = dynamic_cast<CCArray*>(array);
        if (!arr){
            return ;
        }

        CCDictionary* pDict = CCDictionary::create();

        pDict->setObject(arr, "$nin");
        this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
    }

    void BmobQuery::addWhereContainsAll(string seg,CCArray* array){
        if (!array){
            return ;
        }

        CCDictionary* pDict = CCDictionary::create();
        pDict->setObject(array, "$all");

        this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
    }

    void BmobQuery::addWhereMatches(){

    }

    void BmobQuery::addWhereContains(){

    }

    void BmobQuery::whereStartsWith(){

    }

    void BmobQuery::whereEndsWith(){

    }

    void BmobQuery::addWhereExists(string column){
        if (column.empty()){
            return ;
        }

        CCDictionary* pDict = CCDictionary::create();
        CCBool* bol = CCBool::create(true);
        pDict->setObject(bol, "$exists");

        this->m_whereData.insert(pair<string,CCObject*>(column,pDict));
    }

    void BmobQuery::addWhereDoesNotExists(string column){
        if (column.empty()){
            return ;
        }
        CCDictionary* pDict = CCDictionary::create();
        CCBool* bol = CCBool::create(false);
        pDict->setObject(bol, "$exists");

        this->m_whereData.insert(pair<string,CCObject*>(column,pDict));
    }

    void BmobQuery::setLimit(int limit){
        if (limit <= 0) {
          return ;
        }

        this->m_mapData.insert(pair<string,CCObject*>("limit",CCInteger::create(limit)));
    }

    void BmobQuery::setSkip(int skip){
        if (skip <= 0) {
          return ;
        }

        this->m_mapData.insert(pair<string,CCObject*>("skip",CCInteger::create(skip)));
    }

    void BmobQuery::order(string key){
        if (key.empty()) {
          return;
        }

        this->m_mapData.insert(pair<string,CCObject*>("order",CCString::createWithFormat("%s",key.c_str())));
    }


    void BmobQuery::setCachePolicy(){

    }

    bool BmobQuery::hasCachedResult(){
        return false;
    }

    void BmobQuery::clearCachedResult(){

    }

    void BmobQuery::clearAllCachedResults(){

    }

    void BmobQuery::addQueryKeys(string column){
        if (column.empty()) {
          return ;
        }

        this->m_mapData.insert(pair<string,CCObject*>("keys",CCString::createWithFormat("%s",column.c_str())));
    }


    void BmobQuery::sum(string column){
        if (column.empty()) {
          return ;
        }

        this->m_mapData.insert(pair<string,CCObject*>("sum",CCString::createWithFormat("%s",column.c_str())));
    }

    void BmobQuery::average(string column){
        if (column.empty()) {
          return ;
        }

        this->m_mapData.insert(pair<string,CCObject*>("average",CCString::createWithFormat("%s",column.c_str())));
    }

    void BmobQuery::max(string column){
        if (column.empty()) {
          return ;
        }

        this->m_mapData.insert(pair<string,CCObject*>("max",CCString::createWithFormat("%s",column.c_str())));
    }

    void BmobQuery::min(string column){
        if (column.empty()) {
          return ;
        }

        this->m_mapData.insert(pair<string,CCObject*>("min",CCString::createWithFormat("%s",column.c_str())));
    }

    void BmobQuery::groupby(string column){
        if (column.empty()) {
          return ;
        }

        this->m_mapData.insert(pair<string,CCObject*>("groupby",CCString::createWithFormat("%s",column.c_str())));
    }

    void BmobQuery::having(bool isHaving /*= false*/){
        this->m_mapData.insert(pair<string,CCObject*>("having",CCBool::create(isHaving)));
    }

    void BmobQuery::setHasGroupCount(bool groupCount){
        this->m_mapData.insert(pair<string,CCObject*>("groupcount",CCBool::create(groupCount)));
    }

    void BmobQuery::setHeader(vector<string> v){
      	if (v.empty())
      	{
      		return ;
      	}

      	this->clear();
      	this->m_header = v;
    }

    vector<string> BmobQuery::getHeader(){
        if (this->m_header.empty()){
            this->m_header = Crypt::CryptUtil::getCryptRequestHeader(BmobSDKInit::APP_KEY);
        }

        return this->m_header;
    }

    void BmobQuery::enJson(Json::Value *value){
        BmobJsonUtil::dictionary2Json_m(value, &(this->m_whereData));
    }

    void BmobQuery::enJson(Json::Value* value,map<string,CCObject*> data){
        BmobJsonUtil::dictionary2Json(value, &data);
    }

    void BmobQuery::deJson(Json::Value *value){
    	 //BmobJsonUtil::json2Dictionary(value, &(this->m_whereData));
    }

    map<string,CCObject*> BmobQuery::getSolidRequestData(){
        map<string,CCObject*> temp;
        map<string,string> data = CryptUtil::getCryptRequestData();
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

    void BmobQuery::query(string tag){
        HttpRequest* req = new HttpRequest;
        req->setResponseCallback(this, cocos2d::SEL_CallFuncND(&BmobQuery::onHttpRequestCompleted));
        req->setRequestType(HttpRequest::Type::POST);
        req->setHeaders(getHeader());
        req->setTag(tag.c_str());
        req->setUrl(this->m_url.c_str());

        Json::Value where;
        this->enJson(&where);

        Json::Value data;
        this->enJson(&data,this->m_mapData);
        string wh = where.toStyledString();
        if (wh.substr(0,4) != "null") {
            BmobJsonUtil::json2json(&data,"where",where);
        }


        map<string,CCObject*> solid = this->getSolidRequestData();
        Json::Value reqData;
        this->enJson(&reqData,solid);
        BmobJsonUtil::json2json(&reqData,"data",data);

        string strdata = reqData.toStyledString();
        BmobLog::bmob_log("BmobQuery::query",tag,where.toStyledString());
        string tdata = Crypt::CryptUtil::cryptData(strdata);
        req->setRequestData(tdata.c_str(), strlen(tdata.c_str()));

        /**
        * 设置连接和读取数据超时时间
        */
        HttpClient::getInstance()->setTimeoutForRead(3000);
        // HttpClient::getInstance()->setTimeoutForConnect(3000);

        HttpClient::getInstance()->send(req);
        req->release();
    }

    void BmobQuery::onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data){
        HttpResponse *response = (HttpResponse *)data;
        HttpRequest *request = response->getHttpRequest();

        /**
        * 获取对应的http请求的tag类型
        */
        string tag(request->getTag());
        BmobHttpUtil::QueryHttpType httpType = BmobHttpUtil::getQueryHttpType(tag);

        vector<char>* v = response->getResponseHeader();
        string header(v->begin(),v->end());
      	string mothed = BmobHttpUtil::responseMethod(header);

        if (!response->isSucceed()) {
            int errorCode = response->getResponseCode();
            string temp = response->getErrorBuffer();

            string errorInfo;
            if (errorCode != -1) {
              errorInfo = Crypt::CryptUtil::decryptData(temp);
            }else{
              errorInfo = temp;
            }

            BmobLog::bmob_log("BmobQuery","errorinfo",errorInfo);
           switch(httpType){
              case BmobHttpUtil::QueryHttpType::HttpFind:{
                  if (this->m_pFindDelegate != NULL){
                      this->m_pFindDelegate->onFindError(errorCode,errorInfo.c_str());
                  }
              }break;
              case BmobHttpUtil::QueryHttpType::HttpGet:{
                  if (this->m_pGetDelegate != NULL){
                      this->m_pGetDelegate->onGetError(errorCode,errorInfo.c_str());
                  }
              }break;
              case BmobHttpUtil::QueryHttpType::HttpCount:{
                  if (this->m_pCountDelegate != NULL){
                      this->m_pCountDelegate->onCountError(errorCode,errorInfo.c_str());
                  }
              }break;
              case BmobHttpUtil::QueryHttpType::HttpStatistics:{
                  if (this->m_pStaticsDelegate != NULL){
                      this->m_pStaticsDelegate->onStaticsError(errorCode,errorInfo.c_str());
                  }
              }break;
              case BmobHttpUtil::QueryHttpType::HttpBQL:{
                  if (this->m_pBQLDelegate != NULL) {
                      this->m_pBQLDelegate->onBQLFailure(errorCode,errorInfo.c_str());
                  }
              }break;
              default:break;
            }

          return;
        }else{

            std::vector<char> *buffer = response->getResponseData();
            std::string temp((*buffer).begin(),(*buffer).end());
            string str = Crypt::CryptUtil::decryptData(temp);

            switch(httpType){
                 case BmobHttpUtil::QueryHttpType::HttpFind:{
                     if (this->m_pFindDelegate != NULL){
                         this->m_pFindDelegate->onFindSucess(str.c_str());
                     }
                 }break;
                 case BmobHttpUtil::QueryHttpType::HttpGet:{
                     if (this->m_pGetDelegate != NULL){
                         this->m_pGetDelegate->onGetSucess(str.c_str());
                     }
                 }break;
                 case BmobHttpUtil::QueryHttpType::HttpCount:{
                     if(this->m_pCountDelegate != NULL){
                         this->m_pCountDelegate->onCountSucess(str.c_str());
                     }
                 }break;
                 case BmobHttpUtil::QueryHttpType::HttpStatistics:{
                     if (this->m_pStaticsDelegate != NULL){
                         this->m_pStaticsDelegate->onStaticsSucess(str.c_str());
                     }
                 }break;
                 case BmobHttpUtil::QueryHttpType::HttpBQL:{
                     if (this->m_pBQLDelegate != NULL) {
                         this->m_pBQLDelegate->onBQLSuccess(str.c_str());
                     }
                 }break;
                 default:break;
             }
        }
    }
}
