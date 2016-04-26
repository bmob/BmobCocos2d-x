/**
* http处理工具
* create by zhou.2016-02-02
*/
#ifndef BMOBSDK_BMOBHTTPUTIL_H_
#define BMOBSDK_BMOBHTTPUTIL_H_

#include <iostream>
#include <string.h>

using namespace std;

namespace bmobutil{
    class BmobHttpUtil{
    public:
        /**
        *  sdk初始化的HTTP操作的类型，对应于Http请求tag的类型
        *  HttpSecret,请求secret
        *  HttpInit,  请求初始化
        *  HttpTimeStamp, 时间戳
        *  HttpUpDevice, 请求上传设备信息
        *  HttpError
        */
        enum class  InitHttpType{
            HttpSecret,
            HttpInit,
            HttpTimeStamp,
            HttpUpDevice,
            HttpError
        };

        /**
        * sdk基类的HTTP操作的类型，对应于Http请求tag的类型
        ＊　HttpSave          请求保存数据
        ＊　HttpUpdate　      请求更新数据
        ＊　HttpDelete        请求删除数据
        ＊　HttpReset　        请求重置密码
        ＊　HttpRequestCode　  请求验证码
        ＊　HttpResetByCode　  请求通过验证码重置密码
        ＊　HttpEmailVerify　  请求邮箱验证
        ＊　HttpLogin　        请求登陆
        ＊　HttpSignUp　       请求注册
        */
        enum class ObjectHttpType{
            HttpSave,
            HttpUpdate,
            HttpDelete,
            HttpReset,
            HttpRequestCode,
            HttpResetByCode,
            HttpEmailVerify,
            HttpLogin,
            HttpSignUp,
            HttpError
        };

        /**
        * sdk查询的请求操作的类型
        * RequestIgnoreCache　           请求忽略缓存
        * RequestOnlyCache　             只从缓存中读查询
        * RequestOnlyNetwork　           只从网络查询，忽略缓存
        * RequestNetworkElseCache　      先从网络查询，如果没有在查询缓存
        * RequestCacheElseNetwork　      先查询缓存数据，如果没有在从网络获取
        * RequestCacheThenNetwork　      先查询缓存，在查询网络
        * RequestError　                 查询错误
        */
        enum class QueryRequestType{
            RequestIgnoreCache,
            RequestOnlyCache,
            RequestOnlyNetwork,
            RequestNetworkElseCache,
            RequestCacheElseNetwork,
            RequestCacheThenNetwork,
            RequestError
        };

        /**
        * sdk查询的HTTP操作的类型，对应于Http请求的tag
        * HttpFind　         查询请求，查询对应条件的所以信息
        * HttpGet　          查询某个对应objectId的信息
        * HttpCount　        查询count信息
        * HttpStatistics　   查询统计信息
        * HttpBQL　          BQL查询
        */
        enum class QueryHttpType{
            HttpFind,
            HttpGet,
            HttpCount,
            HttpStatistics,
            HttpBQL,
            HttpError
        };

        /**
        * sdk云端代码的HTTP操作类型
        * HttpExec,                                   //执行云端代码
        * HttpCreate,                                 //创建云端代码
        * HttpDelete,                                 //伤处云端代码
        */
        enum class CloudHttpType{
            HttpExec,
            HttpCreate,
            HttpDelete,
            HttpError
        };

    public:
        /**
        * 获取sdk初始化http的tag类型
        * @param tag string
        * @return InitHttpType
        */
        static BmobHttpUtil::InitHttpType getInitHttpType(string tag);
        /**
        * 获取sdk基类对象http的tag类型
        * @param tag string
        * @return ObjectHttpType
        */
        static BmobHttpUtil::ObjectHttpType getObjectHttpType(string tag);

        /**
        * 获取sdk查询http的tag类型
        * @param tag
        * @return QueryHttpType
        */
        static BmobHttpUtil::QueryHttpType getQueryHttpType(string tag);

        /**
        * 获取sdk云端代码http的tag类型
        * @param tag string
        * @return CloudHttpType
        */
        static BmobHttpUtil::CloudHttpType getCloudHttpType(string tag);

        /**
        * 将响应头解析出来变成json字符串，其中去除响应状态，并且跳过\r和\n
        * 返回解析后的json字符串
        * @param str    要解析的字符串
        * @return string  解析后的字符串
        */
        static string responseHeaderToJson(string str);

        /**
        * 解析出响应头部中的响应状态行
        * @param str  将解析的响应头部数据
        * @return string  返回解析后的状态行数据
        */
        static string responseMethod(string str);


    public:
        static string BASE_V8_URL;                    //  api interface
        static string BASE_FILE_URL;                  //  file url
        static string BASE_SCHEMAS_URL;               //  schemas url
        static string BASE_INIT_URL;                  //  init
        static string BASE_SECRET_URL;                //  secret
        static string BASE_CREATE_URL;                //  create
        static string BASE_UPDATE_URL;                //  update
        static string BASE_FIND_URL;                  //  find
        static string BASE_BQL_URL;                   //  BQL
        static string BASE_DELETE_URL;                //  delete
        static string BASE_SIGNUP_URL;                //  signup
        static string BASE_LOGIN_URL;                 //  login
        static string BASE_LOGINORSIGNUP_URL;         //  login or signup
        static string BASE_RESET_URL;                 //  reset
        static string BASE_EMAIL_VERIFY_URL;          //  emal verify
        static string BASE_UPDATE_USER_PWD_URL;       //  update user pwd
        static string BASE_REQUESTSMS_URL;            //  request sms
        static string BASE_REQUESTSMSCODE_URL;        //  request sms code
        static string BASE_VERIFYSMSCODE_URL;         //  verify sms code
        static string BASE_QUERYSMS_URL;              //  query sms
        static string BASE_PHONERESET_URL;            //  phoneset
        static string BASE_CLOUDQUERY_URL;            //  cloud query
        static string BASE_CLOUDCODE_URL;             //  cloud exec
        static string BASE_DELCLOUDCODE_URL;          //  cloud delete
        static string BASE_CRECLOUDCODE_URL;          //  cloud create
        static string BASE_GETTIMESTAMP_URL;          //  timestamp
        static string BASE_UPDEVICE_URL;              //  upload device info


        /**
        * 定义了http请求的tag
        */
        static string HTTP_SECRET_TAG;                //  secret tag
        static string HTTP_INIT_TAG;                  //  init tag

        static string HTTP_SAVE_TAG;                  //  save tag
        static string HTTP_UPDATE_TAG;                //  update tag
        static string HTTP_DELETE_TAG;                //  delete tag
        static string HTTP_RESET_TAG;                 //  reset tag
        static string HTTP_REQUESTCODE_TAG;           //  request  code  tag
        static string HTTP_RESETBYCODE_TAG;           //  reset by code tag
        static string HTTP_EMAILVERIFY_TAG;           //  email verify tag
        static string HTTP_LOGIN_TAG;                 //  login tag
        static string HTTP_SIGNUP_TAG;                //  signup tag

        static string HTTP_FIND_TAG;                  //  find tag
        static string HTTP_GET_TAG;                   //  get tag
        static string HTTP_COUNT_TAG;                 //  count tag
        static string HTTP_STATISTICS_TAG;            //  statistics  tag
        static string HTTP_BQL_TAG;                   //  BQL tag

        static string HTTP_CLOUD_EXEC_TAG;            //  cloud exec tag
        static string HTTP_CLOUD_CREATE_TAG;          //  cloud create tag
        static string HTTP_CLOUD_DELETE_TAG;          //  cloud delete tag

        static string HTTP_TIMESTAMP_TAG;             //  timestamp tag
        static string HTTP_UPDEVICE_TAG;              //  upload device info tag

    };
}

#endif
