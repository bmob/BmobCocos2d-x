/**
* create by zh_u_ 2015-10-25
* 查询单条数据的回调接口
*/
#ifndef BMOBSDK_BMOBGETDELEGATE_H_
#define BMOBSDK_BMOBGETDELEGATE_H_

class BmobGetDelegate{
public:
	/**
	* 查询成功的回调
	* @param data 返回的数据
	*/
	virtual void onGetSucess(const void* data) = 0;
	/**
	* 失败回调
	* @param code 返回错误码
	* @param data 返回的错误数据
	*/
	virtual void onGetError(int code,const void* data) = 0;
};

#endif