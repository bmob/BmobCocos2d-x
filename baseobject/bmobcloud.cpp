#include "bmobcloud.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"
#include "../decrypt/include/cryptutil.h"

using namespace network;
using namespace Crypt;

namespace bmobsdk{
    BmobCloud::BmobCloud(){

    }

    BmobCloud::~BmobCloud(){

    }

    vector<string> BmobCloud::getHeader(){
        if (this->m_header.empty())
        {
          this->m_header = Crypt::CryptUtil::getCryptRequestHeader(BmobSDKInit::APP_KEY);
        }


        return this->m_header;
    }

    map<string,CCObject*> BmobCloud::getSolidRequestData(){
        map<string,CCObject*> temp;
        map<string,string> data = Crypt::CryptUtil::getCryptRequestData();

        temp = BmobSDKUtil::mapStringToCCObject(data);
        temp.insert(pair<string, CCObject *>("client",\
          BmobSDKUtil::mapStringToCCDirectionary(Crypt::CryptUtil::getClientPlatomData())));
        temp.insert(pair<string,CCObject *>("timestamp",CCInteger::create(Crypt::CryptUtil::getTimeStamp())));


        return temp;
    }

    void BmobCloud::send(string tag){

    }

    void BmobCloud::send(network::HttpRequest::Type type,string tag){
        HttpRequest* req = new HttpRequest;
        req->setUrl(this->m_url.c_str());
        req->setTag(tag.c_str());
        req->setResponseCallback(this, cocos2d::SEL_CallFuncND(&BmobCloud::onHttpRequestCompleted));
        req->setRequestType(type);
        req->setHeaders(getHeader());

        Json::Value dataJson;
        this->enJson(&dataJson);
        map<string,CCObject*> solid = this->getSolidRequestData();
        Json::Value solidJson;
        this->enJson(&solidJson,solid);
        BmobJsonUtil::json2json(&solidJson,"data",dataJson);

        std::string data;
        data = solidJson.toStyledString();

        if (data.substr(0,4) == "null") {
            data = "{}";
        }

        BmobLog::bmob_log("BmobCloud::send",tag,dataJson.toStyledString());

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

    void BmobCloud::onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data){
        HttpResponse *response = (HttpResponse *)data;
        HttpRequest *request = response->getHttpRequest();

        /**
        * 获取http对应的tag类型
        */
        string tag(request->getTag());
        BmobHttpUtil::CloudHttpType httpType = BmobHttpUtil::getCloudHttpType(tag);

        if (!response->isSucceed()) {
            int errorCode = response->getResponseCode();
            string errorInfo = response->getErrorBuffer();
            std::vector<char> *buffer = response->getResponseData();
            std::string str((*buffer).begin(),(*buffer).end());
            string temp;

            if (errorCode != -1 && !str.empty()) {
              temp = Crypt::CryptUtil::decryptData(str);
            }else{
              temp = errorInfo;
            }

            switch(httpType){
                case BmobHttpUtil::CloudHttpType::HttpExec:{
                    if (this->m_delegate != NULL) {
                        this->m_delegate->onExecCloud(errorCode,temp.c_str());
                    }
                }break;
                case BmobHttpUtil::CloudHttpType::HttpCreate:{
                    if (this->m_delegate != NULL) {
                        this->m_delegate->onCreateCloud(errorCode,temp.c_str());
                    }
                }break;
                case BmobHttpUtil::CloudHttpType::HttpDelete:{
                    if (this->m_delegate != NULL) {
                        this->m_delegate->onDeleteCloud(errorCode,temp.c_str());
                    }
                }break;
                default:break;
            }

            return;

        }else{
            std::vector<char> *buffer = response->getResponseData();
            std::string data((*buffer).begin(),(*buffer).end());

            string str;
            int code = 301;
            string msg = "";
            try{
                str = Crypt::CryptUtil::decryptData(data);
            }catch(exception e){
                str = "返回数据出错";
            }   
            Json::Reader reader;
            Json::Value value;
            if (!reader.parse(str, value)) {
                msg = str;
            }else{
                code = value["result"]["code"].asInt();
                msg = value["result"]["message"].asString();
            }

            switch(httpType){
                case BmobHttpUtil::CloudHttpType::HttpExec:{
                    if (this->m_delegate != NULL) {
                        if(code == 200){
                            this->m_delegate->onExecCloud(code,str.c_str());
                        }else {
                            this->m_delegate->onExecCloud(code,msg.c_str());
                        }
                    }
                }break;
                case BmobHttpUtil::CloudHttpType::HttpCreate:{
                    if (this->m_delegate != NULL) {
                        if(code == 200){
                            this->m_delegate->onCreateCloud(200,str.c_str());
                        }else {
                            this->m_delegate->onCreateCloud(code,msg.c_str());
                        }
                    }
                }break;
                case BmobHttpUtil::CloudHttpType::HttpDelete:{
                    if (this->m_delegate != NULL) {
                        if(code == 200){
                            this->m_delegate->onDeleteCloud(200,str.c_str());
                        }else {
                            this->m_delegate->onDeleteCloud(code,msg.c_str());
                        }
                    }
                }break;
                default:break;           
            }
            
        }
    }

    void BmobCloud::execCloudCode(string cloudName,std::map<string, CCObject*> param,\
        BmobCloudDelegate *delegate,BmobHttpUtil::CloudHttpType type /*
        = BmobHttpUtil::CloudHttpType::HttpExec */){

        if(!BmobSDKInit::getInstance()->isInitialize() ||
            BmobHttpUtil::BASE_V8_URL.empty()){
            if (delegate != NULL) {
                delegate->onCloudError(-1,"Error:SDK没初始化或初始化失败");
            }
            BmobLog::bmob_log("BmobCloud","execCloudCode","SDK没初始化或初始化失败",BmobLog::LogType::E);
            return ;
        }

        if (cloudName.empty()){
            if (delegate != NULL) {
                delegate->onCloudError(-1,"Error:云端方法名为空");
            }
            return ;
        }

        this->m_url.clear();
        this->m_delegate = delegate;
        this->m_mapData.insert(param.begin(),param.end());
        this->m_mapData.insert(pair<string,CCObject*>("_e",
                CCString::createWithFormat("%s",cloudName.c_str())));

        switch (type) {
            case BmobHttpUtil::CloudHttpType::HttpExec:{
                /**
                * 执行云端代码
                */
                this->m_url = BmobHttpUtil::BASE_CLOUDCODE_URL;
                this->send(HttpRequest::Type::POST,BmobHttpUtil::HTTP_CLOUD_EXEC_TAG);

            }break;
            case BmobHttpUtil::CloudHttpType::HttpDelete:{
                /**
                * 删除云端代码
                */
                this->m_url = BmobHttpUtil::BASE_DELCLOUDCODE_URL;
                this->send(HttpRequest::Type::DELETE,BmobHttpUtil::HTTP_CLOUD_DELETE_TAG);

            }break;
            case BmobHttpUtil::CloudHttpType::HttpCreate:{
                /**
                * 创建远端代码
                */
                if (param.size() != 1) {
                  return ;
                }

                this->m_url = BmobHttpUtil::BASE_CRECLOUDCODE_URL;
                this->send(HttpRequest::Type::POST,BmobHttpUtil::HTTP_CLOUD_CREATE_TAG);
            }break;
            default:break;
          }
      }

}
