/**
* create 2015-11-6
* 通过SMS码重置密码回调接口
*/

#ifndef BMOBSDK_BMOBRESETPASSWORDBYCODEDELEGATE_H_
#define BMOBSDK_BMOBRESETPASSWORDBYCODEDELEGATE_H_

class BmobResetPasswordByCodeDelegate{
public:
	virtual void onResetDone(int code,const void* data) = 0;
};

#endif