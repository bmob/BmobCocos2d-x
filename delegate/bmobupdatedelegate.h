/**
* create by zh_u 2015-10-25
* 更新数据的回调接口
*/
#ifndef BMOBSDK_BMOBUPDATEDELEGATE_H_
#define BMOBSDK_BMOBUPDATEDELEGATE_H_

class BmobUpdateDelegate{
public:
	/**
	* 更新数据成功回调方法
	* @param data 返回的数据
	*/
	virtual void onUpdateSucess(const void* data) = 0;
	/**
	* 更新失败回调方法
	* @param code 返回的错误码
	* @param data 返回的错误数据
	*/
	virtual void onUpdateError(int code,const void* data) = 0;
};

#endif