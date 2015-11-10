/**
* 保存数据回调接口
*/
#ifndef BMOBSDK_BMOBSAVEDELGATE_H_
#define BMOBSDK_BMOBSAVEDELGATE_H_

class BmobSaveDelegate{
public:
	/**
	* 保存数据成功的回调接口
	* @param data 返回的数据
	*/
	virtual void onSaveSucess(const void* data) = 0;
	/**
	* 保存错误回调接口
	* @param code 返回的错误码
	* @param data 返回的错误信息
	*/
	virtual void onSaveError(int code,const void* data) = 0;
};

#endif