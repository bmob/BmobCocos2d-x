/**
* create by zh_u 2015-10-25
* 删除数据回调接口
*/
#ifndef BMOBSDK_BMOBDELETEDELEGATE_H_
#define BMOBSDK_BMOBDELETEDELEGATE_H_

class BmobDeleteDelegate{
public:
	/**
	* 删除成功的回调方法
	* @param data 返回的数据
	*/
	virtual void onDeleteSucess(const void* data) = 0;
	/**
	* 删除失败回调方法
	* @param code 返回错误码
	* @param data 返回的错误数据
	*/
	virtual void onDeleteError(int code,const void* data) = 0;
};

#endif