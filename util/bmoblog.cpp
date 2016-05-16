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

    void BmobLog::bmob_log(string cls,string tag,string msg,BmobLog::LogType type/* = BmobLog::LogType::I*/){
        switch(type){
            case BmobLog::LogType::E:{
                cout<<"[Error]   ["<<cls<<"[ "<<tag<<" ]] "<<getCurrentTime()<<":\t"<<msg<<"\n"<<endl;
            }break;
            case BmobLog::LogType::D:{
                cout<<"[Debug]   ["<<cls<<"[ "<<tag<<" ]] "<<getCurrentTime()<<":\t"<<msg<<"\n"<<endl;
            }break;
            case BmobLog::LogType::I:{
                cout<<"[Info]   ["<<cls<<"[ "<<tag<<" ]] "<<getCurrentTime()<<":\t"<<msg<<"\n"<<endl;
            }break;
            case BmobLog::LogType::W:{
                cout<<"[Warn]   ["<<cls<<"[ "<<tag<<" ]] "<<getCurrentTime()<<":\t"<<msg<<"\n"<<endl;
            }break;
        }
       
    }

    void BmobLog::bmob_log_file(string filename,string cls,string tag,string msg){

    }

    void BmobLog::bmob_log_network(string host,string port,string cls,string tag,string msg){

    }

}
