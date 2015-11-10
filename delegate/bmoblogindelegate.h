/**
* create 2015-11-8
* 登录回调接口
*/
#ifndef BMOBSDK_BMOBLOGINDELEGATE_H_
#define BMOBSDK_BMOBLOGINDELEGATE_H_

class BmobLoginDelegate{
public:
	/**
	*
	*/
	virtual void onLoginDone(int code,const void* data) = 0;
};

#endif