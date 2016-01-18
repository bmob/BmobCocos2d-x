#include "bmobcloud.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"

using namespace network;

BmobCloud::BmobCloud(){

}

BmobCloud::~BmobCloud(){

}


void BmobCloud::send(){

}

void BmobCloud::send(network::HttpRequest::Type type){
  HttpRequest* req = new HttpRequest;
  req->setUrl(this->m_url.c_str());
  //req->setTag(m_sTag.c_str());
  req->setResponseCallback(this, cocos2d::SEL_CallFuncND(&BmobCloud::onHttpRequestCompleted));
  req->setRequestType(type);

  req->setHeaders(getHeader());

  //set request header
  Json::Value params;
  std::string data;
  this->enJson(&params);
  data = params.toStyledString();

  if (data.substr(0,4) == "null") {
    /* code */
    data = "{}";
  }
  cout<<data<<":"<<endl;

  req->setRequestData(data.c_str(), strlen(data.c_str()));

  cout<<"request data is:"<<data<<endl;

  HttpClient::getInstance()->send(req);
  req->release();
}

void BmobCloud::onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data){
  HttpResponse *response = (HttpResponse *)data;


  if (!response->isSucceed()) {
      int errorCode = response->getResponseCode();
      string errorInfo = response->getErrorBuffer();
      if (this->m_delegate != NULL) {
        /* code */
        this->m_delegate->onCloudFailure(errorCode,errorInfo.c_str());
      }
      return;

  }else{

    std::vector<char> *buffer = response->getResponseData();
    std::string str((*buffer).begin(),(*buffer).end());
    cout<<"request sucess "<<str<<endl;

    Json::Reader reader;
    Json::Value value;
    if (!reader.parse(str, value)) {
        //parse error
    }else{
      this->m_delegate->onCloudSuccess(str.c_str());
    }
  }
}

vector<string> BmobCloud::getHeader(){
  if (this->m_header.empty())
  {
      /* code */
      vector<string> header_list;
      header_list.push_back("X-Bmob-Application-Id:"+BmobSDKInit::APP_ID);
      header_list.push_back("X-Bmob-REST-API-Key:"+BmobSDKInit::APP_KEY);
      //header_list.push_back("Accept-Encoding:gzip,deflate");
      header_list.push_back("Content-Type: application/json");


      this->m_header = header_list;
  }

  return this->m_header;
}

void BmobCloud::execCloudCode(string cloudName,std::map<string, CCObject*> param,\
  BmobCloudDelegate *delegate,BmobCloud::EXEC_Type type /*= EXEC_Type::EXEC_Exec*/){
    if(!BmobSDKInit::isInitialize()){
      return ;
    }
    if (cloudName.empty() && type != EXEC_Type::EXEC_Create) {
      /* code */
      return ;
    }
    this->m_url.clear();

    this->m_url = BmobSDKInit::CLOUD_CODE_URL;
    this->m_url += cloudName;

    this->m_delegate = delegate;

    switch (type) {
      case EXEC_Type::EXEC_Exec:{
        if (!param.empty()) {
          /* code */
          m_mapData = param;
        }

        this->send(HttpRequest::Type::POST);
      }break;
      case EXEC_Delete:{
        this->send(HttpRequest::Type::DELETE);
      }break;
      case EXEC_Create:{
          if (param.size() != 1) {
            /* code */
            return ;
          }

          m_mapData = param;
          //创建代码
          this->send(HttpRequest::Type::PUT);
      }break;
      default:break;
    }
  }
