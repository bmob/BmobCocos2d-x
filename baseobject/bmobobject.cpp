/**
* create 2015-11
*/
#include "bmobobject.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"
#include "../util/bmobstrutil.h"

using namespace network;

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
	if (!BmobSDKInit::isInitialize())
	{
		/* code */
		return ;
	}
    _opType = HTTP_OP_Type::_bHTTP_SAVE;

	this->m_pSaveDelegate = delegate;

    this->m_url = BmobSDKInit::URL + m_tableName;

	this->send();
}

void BmobObject::increment(string column,int value /*= 1*/){
   // this->addParams(column,CCInteger::create(value));
}

void BmobObject::setValue(string key,cocos2d::CCObject *object){
    this->enParamsToHttp(key,object);
}

void BmobObject::setValue(string key,CCArray* array){
    //'{"skills":{"__op":"AddUnique","objects":["flying","kungfu"]}}'
    if (array == NULL || key.empty())
    {
        /* code */
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
    if (objectId.empty())
    {
        /* code */
        return ;
    }
    _opType = HTTP_OP_Type::_bHTTP_UPDATE;
    this->m_pUpdateDelegate = delegate;

    this->m_url = BmobSDKInit::URL + m_tableName ;

    if (!objectId.empty())
    {
        /* code */
        this->m_url += + "/" + objectId;
    }

    this->send(HttpRequest::Type::PUT);
}

void BmobObject::remove(string name){
    if (name.empty())
    {
        /* code */
        return ;
    }

    this->clear();
    CCDictionary* pDict = CCDictionary::create();
    CCString* pValue2 = CCString::create("Delete");
    pDict->setObject(pValue2, "__op");

    this->enParamsToHttp(name,pDict);
}

void BmobObject::removeAll(string name,CCArray* array){
    if (array == NULL)
    {
        /* code */
        return ;
    }

    CCDictionary* dict = CCDictionary::create();
    string op = "Remove";

    dict->setObject(CCString::createWithFormat("%s",op.c_str()),"__op");
    dict->setObject(array,"objects");

    this->enParamsToHttp(name,dict);
}

void BmobObject::del(BmobDeleteDelegate* delegate){
    _opType = HTTP_OP_Type::_bHTTP_DELETE;
    this->m_pDeleteDelegate = delegate;

    this->m_url = BmobSDKInit::URL + m_tableName + "/" + m_objectId;
    this->send(HttpRequest::Type::DELETE);
}

void BmobObject::del(string objectId,BmobDeleteDelegate* delegate){
    this->m_objectId = objectId;
    this->del(delegate);
}

void BmobObject::add(string column,CCObject* object){
    //{"list":{"__op":"Add","objects":["person1","person2"]}}
    if (object == NULL)
    {
        /* code */
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
    if (column.empty() == NULL)
    {
        /* code */
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
	this->m_header = v;
}

vector<string> BmobObject::getHeader(){
    if (this->m_header.empty())
    {
        /* code */
        vector<string> header_list;
        header_list.push_back("X-Bmob-Application-Id:"+BmobSDKInit::APP_ID);
        header_list.push_back("X-Bmob-REST-API-Key:"+BmobSDKInit::APP_KEY);
        //header_list.push_back("Accept-Encoding:gzip,deflate");
        header_list.push_back("Content-Type: application/json");

        if (strcmp(m_tableName.c_str(),BmobSDKInit::USER_TABLE.c_str()) == 0) {
            if (!m_session.empty())
            {
                /* code */
                string se = "X-Bmob-Session-Token:" + m_session;
                header_list.push_back(se);
            }
        }

        this->m_header = header_list;
    }

    return this->m_header;
}

void BmobObject::enJson(Json::Value* value){
    BmobJsonUtil::dictionary2Json(value, &(this->m_mapData));
}

void BmobObject::deJson(Json::Value* value){
    this->clear();
    BmobJsonUtil::json2Dictionary(value, &(this->m_mapData));
    this->m_objectId = (*value)["objectId"].asString();
    this->m_createdAt = (*value)["createdAt"].asString();
    this->m_updatedAt = (*value)["updatedAt"].asString();
}

void BmobObject::send(){
	this->send(HttpRequest::Type::POST);
}

void BmobObject::send(HttpRequest::Type type){
	HttpRequest* req = new HttpRequest;
    req->setUrl(this->m_url.c_str());
    //req->setTag(m_sTag.c_str());
    req->setResponseCallback(this, cocos2d::SEL_CallFuncND(&BmobObject::onHttpRequestCompleted));
    req->setRequestType(type);

    req->setHeaders(getHeader());

    //set request header
    Json::Value params;
    std::string data;
    this->enJson(&params);
    data = params.toStyledString();
    //data = BmobStrUtil::remove_tab_enter_space(&data);

    req->setRequestData(data.c_str(), strlen(data.c_str()));

    cout<<"request data is:"<<data<<endl;

    HttpClient::getInstance()->setTimeoutForConnect(3000);
		HttpClient::getInstance()->setTimeoutForRead(3000);
    
    HttpClient::getInstance()->send(req);
    req->release();
}

void BmobObject::onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data){
    HttpResponse *response = (HttpResponse *)data;


    if (!response->isSucceed()) {
        int errorCode = response->getResponseCode();
        
        std::vector<char> *buffer = response->getResponseData();
        std::string errorInfo((*buffer).begin(),(*buffer).end());
        if (errorInfo.size() <= 0) {
            errorInfo = response->getErrorBuffer();
        }
        
        switch(_opType){
            case HTTP_OP_Type::_bHTTP_SAVE:{
                if (m_pSaveDelegate != NULL)
                {
                    /* code */
                    this->m_pSaveDelegate->onSaveError(errorCode,errorInfo.c_str());
                }
            }break;
            case HTTP_OP_Type::_bHTTP_UPDATE:{
                if (m_pUpdateDelegate != NULL)
                {
                    /* code */
                    this->m_pUpdateDelegate->onUpdateError(errorCode,errorInfo.c_str());
                }

            }break;
            case HTTP_OP_Type::_bHTTP_DELETE:{
                if (m_pDeleteDelegate != NULL)
                {
                    /* code */
                    this->m_pDeleteDelegate->onDeleteError(errorCode,errorInfo.c_str());
                }
            }break;
            case HTTP_OP_Type::_bHTTP_RESET:{
                if (m_pResetDelegate != NULL)
                {
                    /* code */
                    this->m_pResetDelegate->onResetError(errorCode,errorInfo.c_str());
                }
            }break;
            case HTTP_OP_Type::_bHTTP_REQUEST_CODE:{
                if(m_pRequestSMSCodeDelegate != NULL){
                    this->m_pRequestSMSCodeDelegate->onRequestDone(errorCode,errorInfo.c_str());
                }
            }break;
            case HTTP_OP_Type::_bHTTP_RESET_BY_CODE:{
                if(m_pResetByMSMCodeDelegate != NULL){
                    this->m_pResetByMSMCodeDelegate->onResetDone(errorCode,errorInfo.c_str());
                }
            }break;
            case HTTP_OP_Type::_bHTTP_EMAIL_VERIFY:{
                if (m_pEmailVerifyDelegate != NULL)
                {
                    /* code */
                    this->m_pEmailVerifyDelegate->onEmailVerifyError(errorCode,errorInfo.c_str());
                }
            }break;
            case HTTP_OP_Type::_bHTTP_LOGIN:{
                if(m_pLoginDelegate != NULL){
                    this->m_pLoginDelegate->onLoginDone(errorCode,errorInfo.c_str());
                }
            }break;
            default:break;
        }

        return;

    }else{

        std::vector<char> *buffer = response->getResponseData();
        std::string str((*buffer).begin(),(*buffer).end());
        cout<<"request sucess "<<str<<endl;
        // if (m_sTag == kTagHttpEndpoint) {
        //     isSuccess = true;
        //     bmobResult = new CCString(str);
        // }else{
        //     str = unGzip(str);
            Json::Reader reader;
            Json::Value value;
            if (!reader.parse(str, value)) {
                //parse error
            }else{
                switch(_opType){
                    case HTTP_OP_Type::_bHTTP_SAVE:{
                        if (strcmp(m_tableName.c_str(),BmobSDKInit::USER_TABLE.c_str()) == 0)
                        {
                            /* code */
                            string objectId = value["objectId"].asString();
                            string session = value["sessionToken"].asString();
                            CCUserDefault::sharedUserDefault()->setStringForKey("user_id",objectId);
                            CCUserDefault::sharedUserDefault()->setStringForKey("user_session",session);

                        }
                        if (m_pSaveDelegate != NULL)
                        {
                            /* code */
                            this->m_pSaveDelegate->onSaveSucess(str.c_str());
                        }
                    }break;
                    case HTTP_OP_Type::_bHTTP_UPDATE:{
                        if (m_pUpdateDelegate != NULL)
                        {
                            /* code */
                            this->m_pUpdateDelegate->onUpdateSucess(str.c_str());
                        }
                    }break;
                    case HTTP_OP_Type::_bHTTP_DELETE:{
                        if (m_pDeleteDelegate != NULL)
                        {
                            /* code */
                            this->m_pDeleteDelegate->onDeleteSucess(str.c_str());
                        }
                    }break;
                    case HTTP_OP_Type::_bHTTP_RESET:{
                        if (m_pResetDelegate != NULL)
                        {
                            /* code */
                            this->m_pResetDelegate->onResetSucess(str.c_str());
                        }
                    }break;
                     case HTTP_OP_Type::_bHTTP_REQUEST_CODE:{
                        if(m_pRequestSMSCodeDelegate != NULL){
                            this->m_pRequestSMSCodeDelegate->onRequestDone(200,str.c_str());
                        }
                    }break;
                     case HTTP_OP_Type::_bHTTP_RESET_BY_CODE:{
                        if(m_pResetByMSMCodeDelegate != NULL){
                            this->m_pResetByMSMCodeDelegate->onResetDone(200,str.c_str());
                        }
                    }break;
                    case HTTP_OP_Type::_bHTTP_EMAIL_VERIFY:{
                        if (m_pEmailVerifyDelegate != NULL)
                        {
                            /* code */
                            this->m_pEmailVerifyDelegate->onEmailVerifySucess(str.c_str());
                        }
                    }break;
                    case HTTP_OP_Type::_bHTTP_LOGIN:{
                        if(m_pLoginDelegate != NULL){
                            this->m_pLoginDelegate->onLoginDone(200,str.c_str());
                        }
                    }break;
                    default:break;
                }

            }
        // }
    }
}
