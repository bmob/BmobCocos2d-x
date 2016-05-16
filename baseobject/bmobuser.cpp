#include "bmobuser.h"
#include "bmobSDKinit.h"
#include "cocos2d.h"
#include "network/HttpRequest.h"

using namespace bmobutil;
USING_NS_CC;

namespace bmobsdk{

	string BmobUser::__USER_FILE = "cur_user.xml";

	BmobUser* BmobUser::createUser(){
		BmobUser* bu = new BmobUser();

		return bu;
	}
	
	BmobUser* BmobUser::getCurrentUser(){

		string id = CCUserDefault::sharedUserDefault()->getStringForKey("user_id");
		string pwd = CCUserDefault::sharedUserDefault()->getStringForKey("user_pwd");
		string name = CCUserDefault::sharedUserDefault()->getStringForKey("user_name");
		string session = CCUserDefault::sharedUserDefault()->getStringForKey("user_session");

		if (id.empty() || name.empty() || session.empty()){
			return NULL;
		}

		BmobUser* currentUser = new BmobUser();
		currentUser->autorelease();
		
		currentUser->m_objectId = id;
		currentUser->m_username = name;
		currentUser->m_session = session;
		currentUser->setPassword(pwd);

		return currentUser;
	}

	void BmobUser::logOut(){
		CCUserDefault::sharedUserDefault()->setStringForKey("user_id","");
		CCUserDefault::sharedUserDefault()->setStringForKey("user_name","");
		CCUserDefault::sharedUserDefault()->setStringForKey("user_pwd","");
		CCUserDefault::sharedUserDefault()->setStringForKey("user_session","");
	}

	BmobUser::BmobUser():
	BmobObject(BmobSDKInit::USER_TABLE){

	}

	BmobUser::~BmobUser(){

	}

	void BmobUser::signUp(BmobSaveDelegate* delegate){
		if (m_username.empty() || m_password.empty()){
			if (delegate != NULL) {
				delegate->onSaveError(-1,"Error:用户名或密码为空");
			}

			return ;
		}

		this->m_url =  BmobHttpUtil::BASE_SIGNUP_URL;
		this->m_pSaveDelegate = delegate;

		this->m_mapData.clear();
		this->m_mapData.insert(pair<string,CCObject*>("username",
						CCString::createWithFormat("%s",m_username.c_str())));
		this->m_mapData.insert(pair<string,CCObject*>("password",
						CCString::createWithFormat("%s",m_password.c_str())));
	   /**
		* 将当前要登陆的用户名和密码保存到本地,一边下次直接登陆
		*/
		CCUserDefault::sharedUserDefault()->setStringForKey("user_name",m_username);
		CCUserDefault::sharedUserDefault()->setStringForKey("user_pwd",m_password);

		this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_SAVE_TAG);
	}

	void BmobUser::login(BmobSaveDelegate* delegate){
		if (this->m_username.empty() || this->m_password.empty()){
			if(delegate != NULL){
				delegate->onSaveError(-1,"Error:用户名或密码为空");
			}

			return ;
		}

		this->m_url = BmobHttpUtil::BASE_LOGIN_URL;
		this->m_pSaveDelegate = delegate;

		this->m_mapData.insert(pair<string,CCObject*>("username",
						CCString::createWithFormat("%s",m_username.c_str())));
		this->m_mapData.insert(pair<string,CCObject*>("password",
						CCString::createWithFormat("%s",m_password.c_str())));

		/**
		* 将登陆的用户 名和密码保存到本地,如果过登陆成功,下次直接使用这个用户名直接登陆
		*/
		CCUserDefault::sharedUserDefault()->setStringForKey("user_name",m_username);
		CCUserDefault::sharedUserDefault()->setStringForKey("user_pwd",m_password);

		this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_SAVE_TAG);
	}

	void BmobUser::loginByAccount(string mebileNumber,string pwd,BmobLoginDelegate* delegate){
		if (mebileNumber.empty() || pwd.empty()){
			if (delegate != NULL) {
				delegate->onLoginDone(-1,"Error:用户名或密码为空");
			}

			return ;
		}

		this->m_url = this->m_url = BmobHttpUtil::BASE_LOGIN_URL;
		this->enParamsToHttp("username",CCString::createWithFormat("%s",mebileNumber.c_str()));
		this->enParamsToHttp("password",CCString::createWithFormat("%s",pwd.c_str()));

		this->m_pLoginDelegate = delegate;
		/**
		* save user
		*/
		CCUserDefault::sharedUserDefault()->setStringForKey("user_name",mebileNumber);
		CCUserDefault::sharedUserDefault()->setStringForKey("user_pwd",pwd);


		this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_LOGIN_TAG);

	}

	void BmobUser::loginBySMSCode(string mebileNumber,string code,BmobLoginDelegate* delegate){
		if (mebileNumber.empty() || code.empty()){
			if (delegate != NULL) {
			 	delegate->onLoginDone(-1,"Error:手机或验证码为空");
			}

			return ;
		}

		this->m_url = BmobHttpUtil::BASE_VERIFYSMSCODE_URL;
		this->m_tableName = BmobSDKInit::USER_TABLE;
		this->enParamsToHttp("MobilePhoneNumber",CCString::createWithFormat("%s",mebileNumber.c_str()));
		this->enParamsToHttp("smsCode",CCString::createWithFormat("%s",code.c_str()));
		this->m_pLoginDelegate = delegate;

		/**
		* save user
		*/
		// CCUserDefault::sharedUserDefault()->setStringForKey("user_name",mebileNumber);
		// CCUserDefault::sharedUserDefault()->setStringForKey("user_pwd",pwd);


		this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_LOGIN_TAG);
	}

	void BmobUser::signOrLoginByMobilePhone(string mebileNumber,string code,BmobLoginDelegate* delegate){
		if (mebileNumber.empty() || code.empty()) {
			return ;
		}

		this->m_url = BmobHttpUtil::BASE_LOGINORSIGNUP_URL;
		this->m_tableName = BmobSDKInit::USER_TABLE;

		this->enParamsToHttp("mobilePhoneNumber",CCString::createWithFormat("%s",mebileNumber.c_str()));
		this->enParamsToHttp("smsCode",CCString::createWithFormat("%s",code.c_str()));

		this->m_pLoginDelegate = delegate;

		this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_LOGIN_TAG);
	}

	void BmobUser::update(string objectId,BmobUpdateDelegate* delegate){
		if(!BmobSDKInit::getInstance()->isInitialize() ||
			BmobHttpUtil::BASE_V8_URL.empty()){
			if (delegate != NULL) {
				delegate->onUpdateError(-1,"Error:SDK没初始化或初始化失败");
			}
			return ;
		}

		if (objectId.empty()){
			if (delegate != NULL) {
				delegate->onUpdateError(-1,"Error:objectId为空");
			}

		  return ;
		}

		this->m_pUpdateDelegate = delegate;
		this->m_url =  BmobHttpUtil::BASE_UPDATE_USER_PWD_URL;
		this->m_tableName = BmobSDKInit::USER_TABLE;

		string session ;
		if (m_session.empty()){
			session = CCUserDefault::sharedUserDefault()->getStringForKey("user_session");
		}else{
			session = m_session;
		}

		this->setSession(session);
		this->enParamsToHttp("username",CCString::createWithFormat("%s",m_username.c_str()));
		this->enParamsToHttp("password",CCString::createWithFormat("%s",m_password.c_str()));

		if (!objectId.empty()){
			this->m_objectId = objectId;
		}

		this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_UPDATE_TAG);
	}

	void BmobUser::update(BmobUpdateDelegate* delegate){
		this->update(this->getObjectId(),delegate);
	}

	void BmobUser::resetPasswordByEmail(string email,BmobResetPasswordDelegate* delegate){
		if(!BmobSDKInit::getInstance()->isInitialize() ||
			BmobHttpUtil::BASE_V8_URL.empty()){
			if (delegate != NULL) {
				delegate->onResetError(-1,"Error:SDK没初始化或初始化失败");
			}
			return ;
		}

		if (email.empty()){
			if (delegate != NULL) {
				delegate->onResetError(-1,"Error:请设置正确邮箱地址");
			}

			return ;
		}

		this->m_pResetDelegate = delegate;
		this->m_url = BmobHttpUtil::BASE_RESET_URL;
		this->clear();
		this->enParamsToHttp("email",CCString::createWithFormat("%s",email.c_str()));

		this->send(BmobHttpUtil::HTTP_RESET_TAG);
	}

	void BmobUser::requestSMSCode(string meblieNumber,string template_name,BmobRequestSMSCodeDelegate* delegate){
		if(!BmobSDKInit::getInstance()->isInitialize() ||
			BmobHttpUtil::BASE_V8_URL.empty()){
			if (delegate != NULL) {
				delegate->onRequestDone(-1,"Error:SDK没初始化或初始化失败");
			}
			return ;
		}

		if (meblieNumber.empty()){
			if (delegate != NULL) {
				delegate->onRequestDone(-1,"Error:输入正确手机号");
			}

			return ;
		}

		this->m_pRequestSMSCodeDelegate = delegate;
		this->m_url = BmobHttpUtil::BASE_REQUESTSMSCODE_URL;
		this->m_tableName = BmobSDKInit::USER_TABLE;
		this->clear();
		this->enParamsToHttp("mobilePhoneNumber",CCString::createWithFormat("%s",meblieNumber.c_str()));

		if (!template_name.empty()){
			this->enParamsToHttp("template",CCString::createWithFormat("%s",template_name.c_str()));
		}

		this->send(BmobHttpUtil::HTTP_REQUESTCODE_TAG);
	}

	void BmobUser::resetPasswordBySMSCode(string pw,string code,BmobResetPasswordByCodeDelegate* delegate){
		if(!BmobSDKInit::getInstance()->isInitialize() ||
			BmobHttpUtil::BASE_V8_URL.empty()){
			if (delegate != NULL) {
				delegate->onResetDone(-1,"Error:SDK没初始化或初始化失败");
			}
			return ;
		}

		if (pw.empty() || code.empty()){
			if (delegate != NULL) {
				delegate->onResetDone(-1,"Error:新密码或验证码为空");
			}

			return ;
		}

		this->m_pResetByMSMCodeDelegate = delegate;
		this->m_url = BmobHttpUtil::BASE_PHONERESET_URL;
		this->clear();
		this->enParamsToHttp("password",CCString::createWithFormat("%s",pw.c_str()));
		this->enParamsToHttp("smsCode",CCString::createWithFormat("%s",code.c_str()));

		CCUserDefault::sharedUserDefault()->setStringForKey("user_pwd",pw);

		this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_RESETBYCODE_TAG);
	}

	void BmobUser::updateCurrentUserPassword(string old_pwd,string new_pwd,BmobUpdateDelegate* delegate){
		if(!BmobSDKInit::getInstance()->isInitialize() ||
			BmobHttpUtil::BASE_V8_URL.empty()){
			if (delegate != NULL) {
				delegate->onUpdateError(-1,"Error:SDK没初始化或初始化失败");
			}
			return ;
		}

		if (old_pwd.empty() || new_pwd.empty() ){//}|| m_objectId.empty()){
			if (delegate != NULL) {
				delegate->onUpdateError(-1,"Error:重置密码信息错误");
			}

			return ;
		}

		this->m_pUpdateDelegate = delegate;
	  this->m_url =  BmobHttpUtil::BASE_UPDATE_USER_PWD_URL;
		this->m_tableName = BmobSDKInit::USER_TABLE;
		this->clear();

		this->enParamsToHttp("oldPassword",CCString::createWithFormat("%s",old_pwd.c_str()));
		this->enParamsToHttp("newPassword",CCString::createWithFormat("%s",new_pwd.c_str()));

		string session ;
		if (m_session.empty()){
			CCUserDefault::sharedUserDefault()->getStringForKey("user_session");
		}else{
			session = m_session;
		}

		this->setSession(session);
		CCUserDefault::sharedUserDefault()->setStringForKey("user_pwd",new_pwd);

		this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_UPDATE_TAG);
	}

	void BmobUser::requestEmailVerify(string email,BmobEmailVerifyDelegate* delegate){
		if(!BmobSDKInit::getInstance()->isInitialize() ||
			BmobHttpUtil::BASE_V8_URL.empty()){
			if (delegate != NULL) {
				delegate->onEmailVerifyError(-1,"Error:SDK没初始化或初始化失败");
			}
			return ;
		}

		if (email.empty()){
			if (delegate != NULL) {
				delegate->onEmailVerifyError(-1,"Error:请输入正确邮箱地址");
			}

			return  ;
		}

		this->m_pEmailVerifyDelegate = delegate;
		this->m_url = BmobHttpUtil::BASE_EMAIL_VERIFY_URL;
		this->enParamsToHttp("email",CCString::createWithFormat("%s",email.c_str()));

		if (this->m_url.empty()) {
			return ;
		}

		this->send(network::HttpRequest::Type::POST,BmobHttpUtil::HTTP_EMAILVERIFY_TAG);
	}
}
