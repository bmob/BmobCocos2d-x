/**
* create by zhou,2016--03-29
*/
#ifndef BMOBSDK_BMOBLOG_H_
#define BMOBSDK_BMOBLOG_H_

#include <iostream>
#include <string>

using namespace std;

namespace bmobutil{
    class BmobLog{
    public:
        /**
        * 获取当前时间,格式是:year-month-day hour:munite:seconed
        */
        static string getCurrentTime();

        /**
        * 打印出信息
        */
        static void bmob_log(string cls,string tag,string msg);

        static void bmob_log_file(string filename,string cls,string tag,string msg);

        static void bmob_log_network(string host,string port,string cls,string tag,string msg);
    private:
    };
}

#endif
