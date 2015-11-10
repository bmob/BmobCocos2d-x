/**
* 字符串操作工具类
*/
#ifndef BMOBSDK_BMOBSTUTIL_H_
#define BMOBSDK_BMOBSTUTIL_H_

#include <iostream>
#include <string>

using namespace std;

class BmobStrUtil{
public:
	/**
	* 移除字符串中的tab、enter、space资产
	* @param str 要操作的字符串
	*/
	static string remove_tab_enter_space(string* str);
};

#endif