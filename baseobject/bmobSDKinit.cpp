#include "bmobSDKinit.h"

string BmobSDKInit::APP_ID;
string BmobSDKInit::APP_KEY;
string BmobSDKInit::BASE_URL = "https://api.bmob.cn";
string BmobSDKInit::URL = BmobSDKInit::BASE_URL + "/1/classes/";
string BmobSDKInit::USER_URL = BmobSDKInit::BASE_URL + "/1/users";
string BmobSDKInit::LOGIN_URL = BmobSDKInit::BASE_URL + "/1/login";
string BmobSDKInit::RESET_URL = BmobSDKInit::BASE_URL + "/1/requestPasswordReset";
string BmobSDKInit::REQUEST_SMS_CODE_URL = BmobSDKInit::BASE_URL + "/1/requestSmsCode";
string BmobSDKInit::RESET_BY_CODE_URL = BmobSDKInit::BASE_URL + "/1/resetPasswordBySmsCode";
string BmobSDKInit::UPDATE_PWD_URL = BmobSDKInit::BASE_URL + "/1/updateUserPassword";
string BmobSDKInit::EMAIL_VERIFY_URL = BmobSDKInit::BASE_URL + "/1/requestEmailVerify";
string BmobSDKInit::CLOUD_CODE_URL = BmobSDKInit::BASE_URL + "/1/functions/";


string BmobSDKInit::USER_TABLE = "_User";

void BmobSDKInit::initialize(string app_id,string app_key){
	BmobSDKInit::APP_ID = app_id;
	BmobSDKInit::APP_KEY = app_key;
}

bool BmobSDKInit::isInitialize(){
	if (BmobSDKInit::APP_ID.empty() || BmobSDKInit::APP_KEY.empty())
	{
		return false;
	}

	 return true;
}
