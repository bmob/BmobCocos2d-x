#include <iostream>
#include <sstream>
#include "./include/json/json.h"

using namespace std;


string json2String(Json::Value *value){
    std::string data;
    Json::Value::Members members((*value).getMemberNames());
    for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)  {
        data+=(*it);
        data+="=";
        if ((*value)[*it].isNumeric()) {
            stringstream ss;
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

int main(int argv,const char* argc[]){
	Json::Value value;
	value["key"] = 123;
	value["123"] = "shockerjue";
	cout<<json2String(&value)<<endl;
	return 0;
}