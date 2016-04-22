#include "bmobjsonutil.h"
#include "../cocos/base/ccMacros.h"

namespace bmobutil{
    void BmobJsonUtil::object2Json(Json::Value *value, std::string key, CCObject *object){
        if (!object) {
            return;
        }
        if (dynamic_cast<CCInteger *>(object)) {

            (*value)[key] = dynamic_cast<CCInteger *>(object)->getValue();

        }else if (dynamic_cast<CCString *>(object)) {

            (*value)[key] = dynamic_cast<CCString *>(object)->getCString();

        }else if (dynamic_cast<CCFloat *>(object)) {

            (*value)[key] = dynamic_cast<CCFloat *>(object)->getValue();

        }else if (dynamic_cast<CCDouble *>(object)) {

            (*value)[key] = dynamic_cast<CCDouble *>(object)->getValue();

        }else if (dynamic_cast<CCBool *>(object)) {

            (*value)[key] = dynamic_cast<CCBool *>(object)->getValue();

        }else if(dynamic_cast<CCDictionary*>(object)){
            Json::Value data;
            CCDictionary* dict = dynamic_cast<CCDictionary*>(object);
            CCArray* array = dict->allKeys();
            CCObject* pObj;

            CCARRAY_FOREACH(array,pObj)
            {
                CCString* key2 = (CCString*)pObj;
                string nkey = key2->getCString();
                CCObject* obj = (dict->objectForKey(nkey));

                if (dynamic_cast<CCInteger *>(obj)) {

                    data[nkey] = dynamic_cast<CCInteger *>(obj)->getValue();

                }else if (dynamic_cast<CCString *>(obj)) {

                    data[nkey] = dynamic_cast<CCString *>(obj)->getCString();

                }else if (dynamic_cast<CCFloat *>(obj)) {

                    data[nkey] = dynamic_cast<CCFloat *>(obj)->getValue();

                }else if (dynamic_cast<CCDouble *>(obj)) {

                    data[nkey] = dynamic_cast<CCDouble *>(obj)->getValue();

                }else if (dynamic_cast<CCBool *>(obj)) {

                    data[nkey] = dynamic_cast<CCBool *>(obj)->getValue();

                }else if(dynamic_cast<CCArray*>(obj)){
                    CCArray* pArray = dynamic_cast<CCArray*>(obj);
                    CCObject* ppObj;
                    vector<CCObject*> array;

                    CCARRAY_FOREACH(pArray,ppObj)
                    {
                        array.push_back(ppObj);
                    }

                    Json::Value data1;
                    array2Json(&data1,&array);
                    data[nkey] = data1;
                }
            }

            (*value)[key] = data;
        }else if(dynamic_cast<CCArray*>(object)){
            CCArray* pArray = dynamic_cast<CCArray*>(object);
            CCObject* pObj;
            vector<CCObject*> array;

            CCARRAY_FOREACH(pArray,pObj)
            {
                array.push_back(pObj);
            }

            Json::Value data;
            array2Json(&data,&array);
            (*value)[key] = data;
        }
    }

    void BmobJsonUtil::dictionary2Json(Json::Value *value,std::map<std::string, cocos2d::CCObject *> *mapData){
        for (map<string, CCObject*>::iterator it = (*mapData).begin(); it!=(*mapData).end(); ++it) {
            object2Json(value, it->first, it->second);
        }
    }

    void BmobJsonUtil::dictionary2Json_m(Json::Value *value,std::multimap<std::string, cocos2d::CCObject *> *mapData){
        for (multimap<string, CCObject*>::iterator it = (*mapData).begin(); it!=(*mapData).end(); ++it) {

            multimap<string, CCObject*>::iterator beg = (*mapData).lower_bound(it->first);
            multimap<string, CCObject*>::iterator end = (*mapData).upper_bound(it->first);
            map<string,CCObject*> temp;
            CCArray* noArray = NULL;
            Json::Value data;

            while(beg != end)
             {
                CCDictionary* dict = dynamic_cast<CCDictionary*>((*beg).second);
                if (dict)
                {
                    CCArray* array = dict->allKeys();
                    CCString* key = (CCString*)(array->objectAtIndex(0));
                    CCObject* obj = (dict->objectForKey(key->getCString()));
                    temp.insert(pair<string,CCObject*>(key->getCString(),obj));
                }else if(dynamic_cast<CCArray*>((*beg).second)){
                    // if(array == NULL){
                    //     array = CCArray::create();
                    // }
                    // array->addObject((*beg).second);
                }else{
                    if (noArray == NULL)
                    {
                        noArray = CCArray::create();
                    }

                    noArray->addObject((*beg).second);
                }
                ++beg;
             }

             if (noArray == NULL){
                dictionary2Json(&data,&temp);
                (*value)[it->first] = data;
             }else{
                if (noArray->count() == 1){
                    CCObject* obj = noArray->objectAtIndex(0);
                    object2Json(value, it->first, obj);
                }else{
                    object2Json(&data, it->first, noArray);
                    (*value)[it->first] = data;
                }
             }
        }
    }

    void BmobJsonUtil::json2json(Json::Value *value,string key,Json::Value src){
      if (key.empty()) {
        return ;
      }

      (*value)[key] = src;
    }

    void BmobJsonUtil::array2Json(Json::Value *jarray,vector<cocos2d::CCObject *> *list){
        int count = (*list).size();
        for (int i = 0; i<count; ++i) {
            int size = (*jarray).size();
            CCObject *object = (*list)[i];

            if (dynamic_cast<CCInteger *>(object)) {

                (*jarray)[size] = dynamic_cast<CCInteger *>(object)->getValue();

            }else if (dynamic_cast<CCString *>(object)) {

                (*jarray)[size] = dynamic_cast<CCString *>(object)->getCString();

            }else if (dynamic_cast<CCFloat *>(object)) {

                (*jarray)[size] = dynamic_cast<CCFloat *>(object)->getValue();

            }else if (dynamic_cast<CCDouble *>(object)) {

                (*jarray)[size] = dynamic_cast<CCDouble *>(object)->getValue();

            }else if (dynamic_cast<CCBool *>(object)) {

                (*jarray)[size] = dynamic_cast<CCBool *>(object)->getValue();
            }
        }
    }


    CCObject* BmobJsonUtil::json2Object(Json::Value *value, std::string key){
        if ((*value)[key].isBool()) {

            return CCBool::create((*value)[key].asBool());

        }else if ((*value)[key].isString()) {

            return CCString::create((*value)[key].asString());

        }else if ((*value)[key].isNumeric()) {

            return CCDouble::create((*value)[key].asInt());

        }else {
            // BmobParams *params = NULL;
            // if ((*value)[key].type() == Json::arrayValue){
            //     params = new BmobArray();
            // }else if ((*value)[key].type() == Json::objectValue){
            //     string type = (*value)[key]["__type"].asString();
            //     if (type == "") {
            //         params = new BmobObject();
            //     }else if (type == kTagParamTypeDate) {
            //         params = new BmobDate();
            //     }else if (type == kTagParamTypeGeopoint) {
            //         params = new BmobGeopoint(0,0);
            //     }else if (type == kTagParamTypeFile) {
            //         params = new BmobFile();
            //     }
            // }
            // if (params) {
            //     params->autorelease();
            //     params->deJson(&(*value)[key]);
            //     return params;
            // }

        }

        return NULL;
    }

    void BmobJsonUtil::json2Dictionary(Json::Value *value,std::map<std::string,
                                        cocos2d::CCObject *> *mapData){
        Json::Value::Members members = (*value).getMemberNames();

        for (Json::Value::Members::iterator it = members.begin();
                          it != members.end(); ++it){
            string key = *it;
            CCObject *object = json2Object(value, key);

            if (object) {
                (*mapData).insert(pair<string, CCObject*>(key,object));
            }
        }
    }

    void BmobJsonUtil::json2Array(Json::Value *jarray, vector<cocos2d::CCObject *> *list){
        int size = (*jarray).size();
        for (int i=0; i<size; ++i) {

            if ((*jarray)[i].isBool()) {

                (*list).push_back(CCBool::create((*jarray)[i].asBool()));

            }else if ((*jarray)[i].isString()) {

                (*list).push_back(CCString::create((*jarray)[i].asString()));

            }else if ((*jarray)[i].isNumeric()) {
                (*list).push_back(CCDouble::create((*jarray)[i].asInt()));
            }
        }
    }

    string BmobJsonUtil::json2String(Json::Value *value){
        std::string data;
        Json::Value::Members members((*value).getMemberNames());

        for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)  {
            data+=(*it);
            data+="=";

            if ((*value)[*it].isNumeric()) {
                std::stringstream ss;
                ss<<(*value)[*it];
                data+=ss.str();
            }else{
                data+=(*value)[*it].asString();
            }

            data+="&";
        }

        data = data.substr(0,data.length()-1);

        return data;
    }
}
