#include "bmobhttputil.h"

namespace bmobutil{
    string BmobHttpUtil::BASE_V8_URL              = "http://open.bmob.cn/8/";
    string BmobHttpUtil::BASE_FILE_URL            = "";
    string BmobHttpUtil::BASE_SCHEMAS_URL         = BASE_V8_URL + "schemas";
    string BmobHttpUtil::BASE_INIT_URL            = BASE_V8_URL + "init";//"127.0.0.1:8080/request";
    string BmobHttpUtil::BASE_SECRET_URL          = BASE_V8_URL + "secret";
    string BmobHttpUtil::BASE_CREATE_URL          = BASE_V8_URL + "create";
    string BmobHttpUtil::BASE_UPDATE_URL          = BASE_V8_URL + "update";
    string BmobHttpUtil::BASE_FIND_URL            = BASE_V8_URL + "find";
    string BmobHttpUtil::BASE_BQL_URL             = BASE_V8_URL + "cloud_query";
    string BmobHttpUtil::BASE_DELETE_URL          = BASE_V8_URL + "delete";
    string BmobHttpUtil::BASE_SIGNUP_URL          = BASE_V8_URL + "signup";
    string BmobHttpUtil::BASE_LOGIN_URL           = BASE_V8_URL + "login";
    string BmobHttpUtil::BASE_LOGINORSIGNUP_URL   = BASE_V8_URL + "login_or_signup";
    string BmobHttpUtil::BASE_RESET_URL           = BASE_V8_URL + "reset";
    string BmobHttpUtil::BASE_EMAIL_VERIFY_URL    = BASE_V8_URL + "email_verify";
    string BmobHttpUtil::BASE_UPDATE_USER_PWD_URL = BASE_V8_URL + "update_user_password";
    string BmobHttpUtil::BASE_REQUESTSMS_URL      = BASE_V8_URL + "request_sms";
    string BmobHttpUtil::BASE_REQUESTSMSCODE_URL  = BASE_V8_URL + "request_sms_code";
    string BmobHttpUtil::BASE_VERIFYSMSCODE_URL   = BASE_V8_URL + "verify_sms_code";
    string BmobHttpUtil::BASE_QUERYSMS_URL        = BASE_V8_URL + "query_sms";
    string BmobHttpUtil::BASE_PHONERESET_URL      = BASE_V8_URL + "phone_reset";
    string BmobHttpUtil::BASE_CLOUDQUERY_URL      = BASE_V8_URL + "cloud_query";
    string BmobHttpUtil::BASE_CLOUDCODE_URL       = BASE_V8_URL + "functions";
    string BmobHttpUtil::BASE_DELCLOUDCODE_URL    = BASE_V8_URL + "deletefunctions";
    string BmobHttpUtil::BASE_CRECLOUDCODE_URL    = BASE_V8_URL + "updatefunctions";
    string BmobHttpUtil::BASE_GETTIMESTAMP_URL    = BASE_V8_URL + "timestamp";
    string BmobHttpUtil::BASE_UPDEVICE_URL        = BASE_V8_URL + "device";


    string BmobHttpUtil::HTTP_SECRET_TAG          = "secret";
    string BmobHttpUtil::HTTP_INIT_TAG            = "init";

    string BmobHttpUtil::HTTP_SAVE_TAG            = "save";
    string BmobHttpUtil::HTTP_UPDATE_TAG          = "update";
    string BmobHttpUtil::HTTP_DELETE_TAG          = "delete";
    string BmobHttpUtil::HTTP_RESET_TAG           = "reset";
    string BmobHttpUtil::HTTP_REQUESTCODE_TAG     = "requestcode";
    string BmobHttpUtil::HTTP_RESETBYCODE_TAG     = "resetbycode";
    string BmobHttpUtil::HTTP_EMAILVERIFY_TAG     = "emailveify";
    string BmobHttpUtil::HTTP_LOGIN_TAG           = "login";
    string BmobHttpUtil::HTTP_SIGNUP_TAG          = "signup";

    string BmobHttpUtil::HTTP_FIND_TAG            = "find";
    string BmobHttpUtil::HTTP_GET_TAG             = "get";
    string BmobHttpUtil::HTTP_COUNT_TAG           = "count";
    string BmobHttpUtil::HTTP_STATISTICS_TAG      = "statistics";
    string BmobHttpUtil::HTTP_BQL_TAG             = "bql";

    string BmobHttpUtil::HTTP_CLOUD_EXEC_TAG      = "cloud_exec";
    string BmobHttpUtil::HTTP_CLOUD_CREATE_TAG    = "cloud_create";
    string BmobHttpUtil::HTTP_CLOUD_DELETE_TAG    = "cloud_delete";

    string BmobHttpUtil::HTTP_TIMESTAMP_TAG       = "timestamp";
    string BmobHttpUtil::HTTP_UPDEVICE_TAG        = "device";

    BmobHttpUtil::InitHttpType BmobHttpUtil::getInitHttpType(string tag){
        if (tag == BmobHttpUtil::HTTP_SECRET_TAG) {

          return InitHttpType::HttpSecret;

        }else if(tag == BmobHttpUtil::HTTP_INIT_TAG){

          return InitHttpType::HttpInit;

        }else if(tag == BmobHttpUtil::HTTP_TIMESTAMP_TAG){

          return InitHttpType::HttpTimeStamp;

        }else if(tag == BmobHttpUtil::HTTP_UPDEVICE_TAG){

          return InitHttpType::HttpUpDevice;

        }else{

            return InitHttpType::HttpError;
        }
    }

    BmobHttpUtil::ObjectHttpType BmobHttpUtil::getObjectHttpType(string tag){
        if (tag == BmobHttpUtil::HTTP_SAVE_TAG) {

          return ObjectHttpType::HttpSave;

        }else if (tag == BmobHttpUtil::HTTP_UPDATE_TAG) {

          return ObjectHttpType::HttpUpdate;

        }else if(tag == BmobHttpUtil::HTTP_DELETE_TAG){

          return ObjectHttpType::HttpDelete;

        }else if (tag == BmobHttpUtil::HTTP_RESET_TAG) {

          return ObjectHttpType::HttpReset;

        }else if (tag == BmobHttpUtil::HTTP_REQUESTCODE_TAG) {

          return ObjectHttpType::HttpRequestCode;

        }else if (tag == BmobHttpUtil::HTTP_RESETBYCODE_TAG) {

          return ObjectHttpType::HttpResetByCode;

        }else if (tag == BmobHttpUtil::HTTP_EMAILVERIFY_TAG) {

          return ObjectHttpType::HttpEmailVerify;

        }else if (tag == BmobHttpUtil::HTTP_LOGIN_TAG) {

          return ObjectHttpType::HttpLogin;

        }else{

          return ObjectHttpType::HttpError;

        }
    }

    BmobHttpUtil::QueryHttpType BmobHttpUtil::getQueryHttpType(string tag){
        if (tag == BmobHttpUtil::HTTP_FIND_TAG) {

          return QueryHttpType::HttpFind;

        }else if (tag == BmobHttpUtil::HTTP_GET_TAG) {

          return QueryHttpType::HttpGet;

        }else if (tag == BmobHttpUtil::HTTP_COUNT_TAG) {

          return QueryHttpType::HttpCount;

        }else if (tag == BmobHttpUtil::HTTP_STATISTICS_TAG) {

          return QueryHttpType::HttpStatistics;

        }else if(tag == BmobHttpUtil::HTTP_BQL_TAG){

          return QueryHttpType::HttpBQL;

        }else{

          return QueryHttpType::HttpError;

        }
    }

    BmobHttpUtil::CloudHttpType BmobHttpUtil::getCloudHttpType(string tag){
        if (tag == BmobHttpUtil::HTTP_CLOUD_EXEC_TAG) {

          return CloudHttpType::HttpExec;

        }else if (tag == BmobHttpUtil::HTTP_CLOUD_CREATE_TAG) {

          return CloudHttpType::HttpCreate;

        }else if(tag == BmobHttpUtil::HTTP_CLOUD_DELETE_TAG){

          return CloudHttpType::HttpDelete;

        }else{

          return CloudHttpType::HttpError;

        }
    }

    string BmobHttpUtil::responseHeaderToJson(string str){
        if (str.empty()) {
            return string("{}");
        }

        const char* p = str.c_str();

        while(*p != '\n' && *p != '\0'){
            p++;
        }

        if (*p == '\n') {
            p++;
        }

        int len = (str.size() * 3) / 2;
        char* q = new char[len];
        if (q == NULL) {
          return "{}";
        }
        memset(q,0,len);

        int i = 0;
        int j = 0;

        q[j++] = '{';
        q[j++] = '\"';

        while(i++ < len && *p != '\0'){
            if (*p == '\n' || *p == '\r') {

                if (*p == '\n' && *(p + 1) != '\0') {
                    q[j++] = '\"';
                    if (*(p + 1) == '\r' && *(p + 2) == '\n') {
                        break;
                    }

                    q[j++] = ',';
                    q[j++] = '\"';
                }

                p++;
                continue;
            }

            if(*p == ':' && ((*(p - 1) < '0') || (*(p -1) > '9'))){
                q[j++] = '\"';
                q[j++] = *p++;
                q[j++] = '\"';
            }else{
                q[j++] = *p++;
            }
        }

        q[j++] = '}';

        string temp(q);

        if (q != NULL) {
            delete[] q;
            q = NULL;
        }

        return temp;
    }

    string BmobHttpUtil::responseMethod(string str){
        if (str.empty()) {
            return string("{}");
        }

        const char* q = str.c_str();
        int len = (strlen(q) * 2) / 3;
        char* p = new char[len];
        if (p == NULL) {
            return "{}";
        }
        memset(p,0,len);

        int i = 0;
        while(*q != '\n' && *q != '\0' && i < len){
            p[i++] = *q++;
        }

        string temp(p);

        if (p != NULL) {
            delete[] p;
            p = NULL;
        }

        return temp;
    }
}
