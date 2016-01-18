/**
* create by zhou,2016-01
* 云端代码执行回调接口
*/
#ifndef BMOBSDK_BMOBCLOUDDELEGATE_H_
#define BMOBSDK_BMOBCLOUDDELEGATE_H_

class BmobCloudDelegate{
public:
  /**
  * 执行云端代码成功的回调函数
  * @param data   成功以后的返回数据
  */
  virtual void onCloudSuccess(const void* data) = 0;
  /**
  * 执行云端代码失败的回调函数
  * @param code   失败的返回代码
  * @param mas    失败的返回信息
  */
  virtual void onCloudFailure(const int code,const void* msg) = 0;
};

#endif
