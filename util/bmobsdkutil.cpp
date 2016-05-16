#include "bmobsdkutil.h"

namespace bmobutil{
    string BmobSDKUtil::getPlatomType(){
        TargetPlatform target = CCApplication::sharedApplication()->getTargetPlatform();

        if (target == kTargetAndroid) {

            return "Android";

        }else if (target == kTargetIphone) {

            return "iphone";

        }else if (target == kTargetLinux) {

            return "linux";

        }else{
            return "Other";
        }
    }

    map<string,CCObject*> BmobSDKUtil::mapStringToCCObject(map<string,string> data){
        map<string,CCObject*> param;

        if (data.size() < 1) {
            return param;
        }

        map<string,string>::const_iterator it = data.begin();

        while(it != data.end()){
            param.insert(pair<string,CCObject*>(it->first,\
                CCString::createWithFormat("%s",it->second.c_str())));
            it++;
        }

        return param;
    }

    CCDictionary* BmobSDKUtil::mapStringToCCDirectionary(map<string,string> data){
        CCDictionary* dirct = CCDictionary::create();

        if (!data.empty()) {
            map<string,string>::const_iterator it = data.begin();

            while(it != data.end()){
                dirct->setObject(CCString::createWithFormat("%s",it->second.c_str()),\
                  it->first.c_str());
                it++ ;
            }
        }

        return dirct;
    }

    string BmobSDKUtil::getCurrentTime(){
        time_t rawtime;
        struct tm * tm;
        time(&rawtime);
        tm = localtime (&rawtime);

        char tim[20] = {0};
        sprintf(tim,"%d-%d-%d %d:%d:%d",tm->tm_year,tm->tm_mon,tm->tm_mday,
            tm->tm_hour,tm->tm_min,tm->tm_sec);

        return string(tim);
    }
}
