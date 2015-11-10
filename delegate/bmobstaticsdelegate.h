/**
* create by zh_u 2015-10-25
* 统计的回调接口
*/
#ifndef BMOBSDK_BMOBSTATICSDELEGATE_H_
#define BMOBSDK_BMOBSTATICSDELEGATE_H_

class BmobStaticsDelegate{
public:
	/**
	* 统计成功的回调接口
	* @param data 返回的数据
	*/
	virtual void onStaticsSucess(const void* data) = 0;
	/**
	* 统计错误的回调接口
	* @param code 返回的错误码
	* @param data 返回的错误数据
	*/
	virtual void onStaticsError(int code,const void* data) = 0;
};

#endif