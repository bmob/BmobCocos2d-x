/**
* create 2015-11-6
* 请求SMS码回调接口
*/
#ifndef BMOBSDK_BMOBREQUESTSMSCODEDELEGATE_H_
#define BMOBSDK_BMOBREQUESTSMSCODEDELEGATE_H_

class BmobRequestSMSCodeDelegate{
public:
	virtual void onRequestDone(int code,const void* data) = 0;
};

#endif