/**
* create by 2015-11-09
* 关于用户注册的类，主要用于注册、登陆、验证、绑定、更新用户信息、获取当前用户
*/
#ifndef BMOBSDK_BMOBUSER_H_
#define BMOBSDK_BMOBUSER_H_

#include <iostream>
#include "cocos2d.h"

#include "bmobobject.h"
#include "../delegate/bmobdelegate.h"
#include "../util/bmobsdkutil.h"


using namespace std;
using namespace bmobdelegate;
using namespace bmobutil;
USING_NS_CC;

namespace bmobsdk{
	class BmobUser:public BmobObject{
	public:

		BmobUser();
		virtual ~BmobUser();

		/**
		* 用户注册
		* @param delegate  监听注册回调接口
		* @return void
		*/
		virtual void signUp(BmobSaveDelegate* delegate) final;
		/**
		* 用户使用用户名和密码登陆
		* @param delegate 监听登陆回调接口
		* @return void
		*/
		virtual void login(BmobSaveDelegate* delegate) final;
		/**
		* 通过用户objectId更新用户信息
		* @param objectId 	用户objectId
		* @return void
		*/
		virtual void update(string objectId,BmobUpdateDelegate* delegate)  final;
		/**
		* 更新用户数据
		* @param delegate 更新回调接口
		* @return void
		*/
	    virtual void update(BmobUpdateDelegate* delegate)  final;

	    /**
	    * 通过发送邮件重置密码
	    * @param email 邮箱地址
	    * @param delegate 重置回调接口
			* @return void
	    */
	    void resetPasswordByEmail(string email,BmobResetPasswordDelegate* delegate);
	    /**
	    * 请求SMS码
	    * @param meblieNumber 手机号码
	    * @param template_name 模板名
	    * @param delegate 请求回调接口
			* @return void
	    */
	    void requestSMSCode(string meblieNumber,string template_name,BmobRequestSMSCodeDelegate* delegate);
	    /**
	    * 通过SMS码重置密码
	    * @param pw 密码
	    * @param code SMS码
	    * @param delegate 重置回调接口
			* @return void
	    */
	    void resetPasswordBySMSCode(string pw,string code,BmobResetPasswordByCodeDelegate* delegate);
	    /**
	    * 更新当前用户的密码
	    * @param old_pwd 原密码
	    * @param new_pwd 新密码
	    * @param delegate 回调接口
			* @return void
	    */
	    void updateCurrentUserPassword(string old_pwd,string new_pwd,BmobUpdateDelegate* delegate);
	    /**
	    * 请求邮箱验证
	    * @param email 邮箱地址
	    * @param delegate 回调接口
			* @return void
	    */
	    void requestEmailVerify(string email,BmobEmailVerifyDelegate* delegate);

	    /**
	    * 使用账号直接登录
	    * @param meblieNumber  账号名（手机，邮箱..）
	    * @param pwd 密码
			* @return void
	    */
	    void loginByAccount(string mebileNumber,string pwd,BmobLoginDelegate* delegate);
	    /**
	    * 使用SMS码一键注册登陆登录
	    * @param mebileNumber 手机号
	    * @param code SMS码
	    * @param delegate 回调接口
			* @return void
	    */
	    void loginBySMSCode(string mebileNumber,string code,BmobLoginDelegate* delegate);
	    /**
	    * 使用手机号注册并直接登录
	    * @param mebileNumber 手机号
	    * @param code SMS码
	    * @param delegate 回调接口
			* @return void
	    */
	    void signOrLoginByMobilePhone(string mebileNumber,string code,BmobLoginDelegate* delegate);
		/**
		* 获取当前用户
		*/
		static BmobUser* getCurrentUser();
		static BmobUser* currentUser;
		static string __USER_FILE;

		/**
		* 退出登录
		*/
		static void logOut();

	private:
		CC_SYNTHESIZE(bool,m_mobilePhoneNumberVerified,MobilePhoneNumberVerified);
		CC_SYNTHESIZE(string,m_mobilePhoneNumber,MobilePhoneNumber);
		CC_SYNTHESIZE(string,m_emailVerified,EmailVerified);
		CC_SYNTHESIZE(string,m_username,UserName);
		CC_SYNTHESIZE(string,m_email,Email);
		CC_SYNTHESIZE(string,m_password,Password);
	};
}

#endif
