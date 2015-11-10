/**
* create by zh_u 2015-10-25
* 查询数据的回调接口
*/
#ifndef BMOBSDK_BMOBFINDDELEGATE_H_
#define BMOBSDK_BMOBFINDDELEGATE_H_

class BmobFindDelegate{
public:
	/**
	* 成功回调接口
	* @param data 返回的数据
	*/
	virtual void onFindSucess(const void* data) = 0;
	/**
	* 错误回调
	* @param code 返回的错误码
	* @param data 返回的错误数据
	*/
	virtual void onFindError(int code,const void* data) = 0;
};

#endif