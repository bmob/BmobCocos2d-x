/**
* create 2015-11-6
* 重置密码回调接口
*/

#ifndef BMOBSDK_BMOBRESETPASSWORDDELEGATE_H_
#define BMOBSDK_BMOBRESETPASSWORDDELEGATE_H_

class BmobResetPasswordDelegate{
public:
	/**
	* 重置成功的回调接口
	*/
	virtual void onResetSucess(const void* data) = 0;
	/**
	* 重置失败回调接口
	*/
	virtual void onResetError(int code,const void* data) = 0;
};


#endif