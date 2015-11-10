/**
* create 201511-6
* 邮箱验证的回调接口
*/
#ifndef BMOBSDK_BMOBEMAILVERIFYDELEGATE_H_
#define BMOBSDK_BMOBEMAILVERIFYDELEGATE_H_

class BmobEmailVerifyDelegate{
public:
	/**
	* 验证成功的回调接口
	* @param data 返回的数据
	*/
	virtual void onEmailVerifySucess(const void* data) = 0;
	/**
	* 验证失败回调
	* @param code 返回的错误码
	* @param data 返回的错误数据
	*/
	virtual void onEmailVerifyError(int code,const void* data) = 0;
};

#endif