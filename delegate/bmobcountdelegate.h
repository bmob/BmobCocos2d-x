/**
* create by zh_u 2015-10-25
* 查询数量回调接口
*/
#ifndef BOMSDK_BMOBCOUNTDELEGATE_H_
#define BOMSDK_BMOBCOUNTDELEGATE_H_

class BmobCountDelegate{
public:
	/**
	* 查询成功回调
	* @param data 返回的数据
	*/
	virtual void onCountSucess(const void* data) = 0;
	/**
	* 查询失败回调
	* @param code 返回的错误码
	* @param data 返回的错误信息
	*/
	virtual void onCountError(int code,const void* data) = 0;
};

#endif