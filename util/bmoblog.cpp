#include "bmoblog.h"
#include <stdio.h>
#include <time.h>

namespace bmobutil{
    string BmobLog::getCurrentTime(){
        time_t rawtime;
        struct tm * tm;
        time(&rawtime);
        tm = localtime (&rawtime);

        char tim[20] = {0};
        sprintf(tim,"%d-%d-%d %d:%d:%d",tm->tm_year,tm->tm_mon,tm->tm_mday,
            tm->tm_hour,tm->tm_min,tm->tm_sec);

        return string(tim);
    }

    void BmobLog::bmob_log(string cls,string tag,string msg){
        cout<<"["<<cls<<"[ "<<tag<<" ]] "<<getCurrentTime()<<":\t"<<msg<<"\n"<<endl;
    }

    void BmobLog::bmob_log_file(string filename,string cls,string tag,string msg){

    }

    void BmobLog::bmob_log_network(string host,string port,string cls,string tag,string msg){

    }

}
