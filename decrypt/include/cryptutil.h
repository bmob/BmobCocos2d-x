/**
* create by zhou,2016-01-20
*/
#ifndef BMOBSDK_BMOBUTIL_H_
#define BMOBSDK_BMOBUTIL_H_

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <map>
#include <iostream>

/**
* 这是用于存储发送数据缓冲区大小,默认为8KB,如果发送的数据比较大时,可以修改这个值
*/
#define MAX_DECRYPT_BUFFERED 8192 //8KB

using namespace std;

namespace Crypt{
    class CryptUtil{
    public:
        /**
        * 获取不加密的请求头,用于测试用
        * 请求返回数据类型,如:"application/json、application/xml和text/html"
        * @param appkey string
        * @param secretKey string
        * @param type string
        * @return vector<string>
        */
        static vector<string> getHeader(string appkey);

        /**
        * 获得secret请求接口的http头部
        * @param appkey string
        * @return vector<string>
        */
        static vector<string> getSecretHeader();

        /**
        * 获得数据操作请求的HTTP头部
        * @param appkey string
        * @return vector<string>
        */
        static vector<string> getCryptRequestHeader(string appkey);

        /**
        * @param appkey
        * @return string
        */
        static string getKey1Str();

        /**
        * @param appkey string
        * @return map<string,string>
        */
        static map<string,string> getSecretRequestData(string appkey);

        /**
        * 得到对应平台的数据
        * @param void
        * @return map<string,string>
        */
        static map<string,string> getClientPlatomData();

        /**
        * 获取secret请求clint的扩展数据
        * @param
        * @return map<string,string>
        */
        static map<string,string> getSecretExData();

        /**
        * @return map<string,string>
        */
        static map<string,string> getCryptRequestData();

        /**
        * crypt data
        * @param src string
        * @return string
        */
        static string cryptData(string src);

        /**
        * @param src string
        * @return string
        */
        static string cryptSecretRequestData(string src);
        static string decryptSecretRequestData(string src);
        /**
        * decrypt data
        * @param src string
        * @return string
        */
        static string decryptData(string src);

        /**
        * 解码secret接口返回的数据
        * @param src string
        * @return string
        */
        static string decryptSecretData(string src);

        /**
        * 获取当前的时间戳
        * @param void
        * @return string
        */
        static long getTimeStamp();

        /**
        * @param  string
        * @return void
        */
        static void set1(string y);
        static void set2(string s);
        static void set3(string s);
        static void setS(string s);
        static void setSession(string s);

        static string get3();

        /**
        * 输出数据map<string,string>数据
        * @pram data map<string,string>
        * @return
        */
        static void outputMap(map<string,string> data);
        /**
        * 输出vector<string>类型的数据
        * @pram data vector<string>
        * @return
        */
        static void outputVector(vector<string> data);

        private:
        /**
        * 获取加密的头部
        * @param agent string
        * @param id string
        * @return vector<string>
        */
        static vector<string> getHeaderSSL(string agent,string appkey);
        /**
        * @param src string
        * @param key string
        * @return string
        */
        static string cryptUsekey(string src,string key);
        /**
        * @param src string
        * @param key string
        * @return string
        */
        static string decryptUseKey(string src,string key);

    public:


    public:
        static string M_S;

    public:
        static string SDK_VERSION;
        /**
        * 密钥仅仅获取一次
        */
        static int ONLY_ONCE;
        static string KEY_STR;
        static char CHAR[];
    };
};
#endif
