#include "bmobquery.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"
#include "network/HttpRequest.h"
#include "../util/bmobstrutil.h"


using namespace network;

BmobQuery::BmobQuery(string tableName):
BmobQueryInterafce(tableName){

}

BmobQuery::~BmobQuery(){

}

void BmobQuery::findObjects(BmobFindDelegate* delegate){
    if (!BmobSDKInit::isInitialize())
    {
        /* code */
        return ;
    }

	this->m_pFindDelegate = delegate;
	this->_delegateType = DelegateType::_bFIND_D;

    this->m_url = getBaseUrl() +"?" \
        + getLimit() + getSkip() + getOrder() + getQueryKey();

	this->query();
}

void BmobQuery::findObjects(string tableName,BmobFindDelegate* delegate){
    if (!BmobSDKInit::isInitialize())
    {
        /* code */
        return ;
    }

    this->m_pFindDelegate = delegate;
    this->_delegateType = DelegateType::_bFIND_D;

    this->m_url = getBaseUrl() +"?" \
        + getLimit() + getSkip() + getOrder() + getQueryKey();

    this->query();
}

void BmobQuery::getObject(string objectId,BmobGetDelegate* delegate){
    if (!BmobSDKInit::isInitialize())
    {
        /* code */
        return ;
    }

	if (objectId.empty())
	{
		/* code */
		return ;
	}

	this->m_pGetDelegate = delegate;
	this->_delegateType = DelegateType::_bGET_D;
	this->m_url = getBaseUrl() + "/" + objectId +"?" + getQueryKey();
	this->query();
}

void BmobQuery::count(BmobCountDelegate* delegate,bool sign /*= false*/){
    if (!BmobSDKInit::isInitialize())
    {
        /* code */
        return ;
    }

    this->m_pCountDelegate = delegate;
    this->_delegateType = DelegateType::_bCOUNT_D;
    if (sign)
    {
        /* code */
        this->m_url = getBaseUrl() + "?count=1&" + getLimit() + \
                        getSkip() + getOrder();
    }else{
        this->m_url = getBaseUrl() + "?count=1&limit=0&";
    }

    this->query();

}

void BmobQuery::findStatistics(BmobStaticsDelegate* delegate){
    if (!BmobSDKInit::isInitialize())
    {
        /* code */
        return ;
    }

    this->m_pStaticsDelegate = delegate;
    this->_delegateType = DelegateType::_bSTATICS_D;

    this->m_url = getBaseUrl() + "?" + getSum() + getGroup() +\
                    getOrder() + getLimit() + getSkip() + getQueryKey() + \
                    getGroupCount() + getMax() + getMin() + getAverage();

    this->query();
}

void BmobQuery::addWhereEqualTo(string seg,CCObject *object){
    if (object == NULL)
    {
        /* code */
        return ;
    }
    this->m_whereData.insert(pair<string,CCObject*>(seg,object));
}

void BmobQuery::addWhereNotEqualTo(string seg,CCObject *object){
    //where={"playerName":{"$nin":["Jonathan Walsh","Dario Wunsch","Shawn Simon"]}}'
    if (object == NULL)
    {
        /* code */
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
    if (!value)
    {
        /* code */
        return ;
    }

    CCDictionary* pDict = CCDictionary::create();
    pDict->setObject(value, "$lt");
    this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
}

void BmobQuery::addWhereLessThanOrEqualTo(string seg,CCObject *object){
    CCInteger* value = dynamic_cast<CCInteger*>(object);
    if (!value)
    {
        /* code */
        return ;
    }

    CCDictionary* pDict = CCDictionary::create();
    pDict->setObject(value, "$lte");
    this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
}

void BmobQuery::addWhereGreaterThan(string seg,CCObject *object){
     CCInteger* value = dynamic_cast<CCInteger*>(object);
    if (!value)
    {
        /* code */
        return ;
    }

    CCDictionary* pDict = CCDictionary::create();
    pDict->setObject(value, "$gt");
    this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
}

void BmobQuery::addWhereGreaterThanOrEqualTo(string seg,CCObject *object){
     CCInteger* value = dynamic_cast<CCInteger*>(object);
    if (!value)
    {
        /* code */
        return ;
    }

    CCDictionary* pDict = CCDictionary::create();
    pDict->setObject(value, "$gte");
    this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
}

void BmobQuery::addWhereContainedIn(string seg,CCObject* array){
    CCArray* arr = dynamic_cast<CCArray*>(array);
    if (!arr)
    {
        /* code */
        return ;
    }
    CCDictionary* pDict = CCDictionary::create();

    pDict->setObject(arr, "$in");
    this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
}

void BmobQuery::addWhereNotContainedIn(string seg,CCObject* array){
    CCArray* arr = dynamic_cast<CCArray*>(array);
    if (!arr)
    {
        /* code */
        return ;
    }
    CCDictionary* pDict = CCDictionary::create();

    pDict->setObject(arr, "$nin");
    this->m_whereData.insert(pair<string,CCObject*>(seg,pDict));
}

void BmobQuery::addWhereContainsAll(string seg,CCArray* array){
     if (!array)
    {
        /* code */
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
    if (column.empty())
    {
        /* code */
        return ;
    }
    CCDictionary* pDict = CCDictionary::create();
    CCBool* bol = CCBool::create(true);
    pDict->setObject(bol, "$exists");
    this->m_whereData.insert(pair<string,CCObject*>(column,pDict));
}

void BmobQuery::addWhereDoesNotExists(string column){
    if (column.empty())
    {
        /* code */
        return ;
    }
    CCDictionary* pDict = CCDictionary::create();
    CCBool* bol = CCBool::create(false);
    pDict->setObject(bol, "$exists");
    this->m_whereData.insert(pair<string,CCObject*>(column,pDict));
}

void BmobQuery::setLimit(int limit){
    this->m_limit = limit;
}

void BmobQuery::setSkip(int skip){
    this->m_skip = skip;
}

void BmobQuery::order(string key){
    this->m_order = key;
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
    this->m_queryKey = column;
}


void BmobQuery::sum(string column){
    this->m_sum = column;
}

void BmobQuery::average(string column){
    this->m_average = column;
}

void BmobQuery::max(string column){
    this->m_max = column;
}

void BmobQuery::min(string column){
    this->m_min = column;
}

void BmobQuery::groupby(string column){
    this->m_group = column;
}

void BmobQuery::having(bool isHaving /*= false*/){
    this->m_isHaving = isHaving;
}

void BmobQuery::setHasGroupCount(bool groupCount){
    this->m_groupCount = groupCount;
}

void BmobQuery::setHeader(vector<string> v){
	if (v.empty())
	{
		/* code */
		return ;
	}
	this->clear();

	this->m_header = v;
}

vector<string> BmobQuery::getHeader(){
	if (this->m_header.empty())
    {
        /* code */
        vector<string> header_list;
        header_list.push_back("X-Bmob-Application-Id:"+BmobSDKInit::APP_ID);
        header_list.push_back("X-Bmob-REST-API-Key:"+BmobSDKInit::APP_KEY);
        header_list.push_back("Accept-Encoding:gzip,deflate,sdch");
        header_list.push_back("Content-Type: application/json");

        // if (m_sTableName == TABLE_USER) {
        //     header_list.push_back("X-Bmob-Session-Token:"+s_SettionToken);
        // }

        this->m_header = header_list;
    }

    return this->m_header;
}

void BmobQuery::enJson(Json::Value *value){
	BmobJsonUtil::dictionary2Json_m(value, &(this->m_whereData));
}

void BmobQuery::deJson(Json::Value *value){
	 //BmobJsonUtil::json2Dictionary(value, &(this->m_whereData));
}

void BmobQuery::query(){
	HttpRequest* req = new HttpRequest;

    req->setResponseCallback(this, cocos2d::SEL_CallFuncND(&BmobQuery::onHttpRequestCompleted));
    req->setRequestType(HttpRequest::Type::GET);


    req->setHeaders(getHeader());

    Json::Value params;
    std::string data;
    this->enJson(&params);
    data = params.toStyledString();
    string st = "null\n";
    /**
    *
    */
    if (!data.empty() && strcmp(data.c_str(),st.c_str()) != 0)
    {
    	/* code */
    	 if(m_isHaving){
            data = "having=" + data;
            m_isHaving = false;
        }else{
           data = "where=" + data;
        }
        data = BmobStrUtil::remove_tab_enter_space(&data);
        this->m_url += data;
    	//req->setRequestData(data.c_str(), strlen(data.c_str()));
    }
    req->setUrl(this->m_url.c_str());

    HttpClient::getInstance()->setTimeoutForConnect(3000);
		HttpClient::getInstance()->setTimeoutForRead(3000);
    
    HttpClient::getInstance()->send(req);
    req->release();
}

void BmobQuery::onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data){
    HttpResponse *response = (HttpResponse *)data;

    vector<char>* reh = response->getResponseHeader();
    std::vector<char>::iterator it = reh->begin();
    while(it != reh->end()){
        cout<<*it++;
    }

    if (!response->isSucceed()) {
        int errorCode = response->getResponseCode();
        string errorInfo = response->getErrorBuffer();
         switch(_delegateType){
            case DelegateType::_bFIND_D:{
                if (this->m_pFindDelegate != NULL)
                {
                    /* code */
                    this->m_pFindDelegate->onFindError(errorCode,errorInfo.c_str());
                }
            }break;
            case DelegateType::_bGET_D:{
                if (this->m_pGetDelegate != NULL)
                {
                    /* code */
                    this->m_pGetDelegate->onGetError(errorCode,errorInfo.c_str());
                }
            }break;
            case DelegateType::_bCOUNT_D:{
                if (this->m_pCountDelegate != NULL)
                {
                    /* code */
                    this->m_pCountDelegate->onCountError(errorCode,errorInfo.c_str());
                }
            }break;
            case DelegateType::_bSTATICS_D:{
                if (this->m_pStaticsDelegate != NULL)
                {
                    /* code */
                    this->m_pStaticsDelegate->onStaticsError(errorCode,errorInfo.c_str());
                }
            }break;
            default:break;
        }

        return;
    }else{

        std::vector<char> *buffer = response->getResponseData();
        std::string str((*buffer).begin(),(*buffer).end());
        cout<<"request sucess "<<str<<endl;
        //str = unGzip(str);
        Json::Reader reader;
        Json::Value value;
        if (!reader.parse(str, value)) {
            //parse error
        }else{
           switch(_delegateType){
                case DelegateType::_bFIND_D:{
                    if (this->m_pFindDelegate != NULL)
                    {
                        /* code */
                        this->m_pFindDelegate->onFindSucess(str.c_str());
                    }
                }break;
                case DelegateType::_bGET_D:{
                    if (this->m_pGetDelegate != NULL)
                    {
                        /* code */
                        this->m_pGetDelegate->onGetSucess(str.c_str());
                    }
                }break;
                case DelegateType::_bCOUNT_D:{
                    if(this->m_pCountDelegate != NULL){
                        this->m_pCountDelegate->onCountSucess(str.c_str());
                    }
                }break;
                case DelegateType::_bSTATICS_D:{
                    if (this->m_pStaticsDelegate != NULL)
                    {
                        /* code */
                        this->m_pStaticsDelegate->onStaticsSucess(str.c_str());
                    }
                }break;
                default:break;
            }

        }
    }
}
