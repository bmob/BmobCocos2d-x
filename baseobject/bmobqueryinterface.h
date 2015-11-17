/**
* create 2015-11
* 查询的接口
*/
#ifndef BMOBSDK_BMOBQUERYINTERFACE_H_
#define BMOBSDK_BMOBQUERYINTERFACE_H_

#include <iostream>
#include <string>
#include "cocos2d.h"

#include "../delegate/bmobdelegate.h"
#include "../jsoncpp/include/json.h"
#include "../util/bmobjsonutil.h"


using namespace std;
USING_NS_CC;


class BmobQueryInterafce:public cocos2d::CCObject{
public:
	/**
	* 操作请求的类型，具体看文档
	*/
	enum class Type{
		IGNORE_CACHE,	
		CACHE_ONLY,
		NETWORK_ONLY,
		NETWORK_ELSE_CACHE,
		CACHE_ELSE_NETWORK,
		CACHE_THEN_NETWORK
	};

	
public:
	/**
	* 通过要操作的表名创建一个Query对象
	*/
	BmobQueryInterafce(string tableName){
		m_tableName = tableName;
		_queryType = Type::IGNORE_CACHE;

		m_pFindDelegate = NULL;
		m_pGetDelegate = NULL;
		m_pCountDelegate = NULL;
		m_pStaticsDelegate = NULL;

		m_isHaving = false;
		m_groupCount = false;

		m_limit = 0;
		m_skip = 0;
	}

	

	/**
	* 查询所有对象
	* @param delegate 查询回调接口
	*/
	virtual void findObjects(BmobFindDelegate* delegate) = 0;
	/**
	* 直接通过表名查询对应表的所有数据
	* @param tableName 表名
	* @param delegate 查询回调接口
	*/
	virtual void findObjects(string tableName,BmobFindDelegate* delegate) = 0;
	/**
	* 通过objectId 查询对应的数据
	* @param objectid 查询的objectId
	* @param delegate 查询的回调接口
	*/
	virtual void getObject(string objectId,BmobGetDelegate* delegate) = 0;
	/**
	* 查询数量
	* @param delegate 回调接口
	* @param sign 是否需要返回数量对应的数据标志 
	*/
	virtual void count(BmobCountDelegate* delegate,bool sign = false) = 0;
	/**
	* 统计操作
	* @param delegate 回调接口
	*/
	virtual void findStatistics(BmobStaticsDelegate* delegate) = 0;

	/**
	* 添加查询满足的where条件
	* @param seg 字段名
	* @param object 对应的值
	* 如：将name="Harrier"添加到查询中
	*/
	virtual void addWhereEqualTo(string seg,CCObject *object) = 0;
	/**
	* 添加查询不满足的where条件
	* @param seg 字段名
	* @param object 对应的值
	* 如：将name!="Harrier"添加到查询中
	*/
	virtual void addWhereNotEqualTo(string seg,CCObject *object) = 0;
	/**
	* 
	*/
	virtual void addWhereGreatorThan(string seg,CCObject *object) = 0;
	/**
	* 添加小于某个值的where条件
	* @param seg 字段名
	* @param object 对应字段的值
	* 如：将age<30添加到查询中
	*/
	virtual void addWhereLessThan(string seg,CCObject *object) = 0;
	/**
	* 添加小于等于某个值的where条件
	* @param seg 字段名
	* @param object 对应字段的值
	* 如：将age<=30添加到查询中
	*/
	virtual void addWhereLessThanOrEqualTo(string seg,CCObject *object) = 0;
	/**
	* 添加大于某个值的where条件
	* @param seg 字段名
	* @param object 对应的值
	* 如：将age>20添加到查询中
	*/
	virtual void addWhereGreaterThan(string seg,CCObject *object) = 0;
	/**
	* 添加大于等于某个值的where条件
	* @param seg 字段名
	* @param object 对应的值
	* 如：将age>=20添加到查询中
	*/
	virtual void addWhereGreaterThanOrEqualTo(string seg,CCObject *object) = 0;
	/**
	* 添加包含数组中某个值的where条件
	* @param seg 字段名
	* @param array 需要查询字段包含的值
	*/
	virtual void addWhereContainedIn(string seg,CCObject* array) = 0;
	/**
	* 添加不包含数组中某个值的where条件
	* @param seg 字段名
	* @param array 需要查询字段不包含的值
	*/
	virtual void addWhereNotContainedIn(string seg,CCObject* array) = 0;
	/**
	* 添加包含数组中所有值的where条件
	* @param seg 字段名
	* @param array 需要查询包含的数组
	*/
	virtual void addWhereContainsAll(string seg,CCArray* array) = 0;
	virtual void addWhereMatches() = 0;
	virtual void addWhereContains() = 0;
	/**
	* 添加查询某个字段存在的where条件
	* @param column	查询的字段名
	*/
	virtual void addWhereExists(string column) = 0;
	/**
	* 添加查询某个字段不存在的where条件
	* @param column 查询的字段名
	*/
	virtual void addWhereDoesNotExists(string column) = 0;
	/**
	* 设置查询返回的字段
	* @param column 字段名
	*/
	virtual void addQueryKeys(string column) = 0;

	/**
	* where excute
	*/
	virtual void whereStartsWith() = 0;
	virtual void whereEndsWith() = 0;

	
	/**
	* 设置查询返回的数量 
	*/
	virtual void setLimit(int limit) = 0;

	/**
	* 设置查询跳转的页或者是要查询第几页
	*/
	virtual void setSkip(int skip) = 0;
	/**
	* 设置排序方法
	*/
	virtual void order(string key) = 0;

	/**
	* 
	*/
	virtual void setCachePolicy() = 0;

	virtual bool hasCachedResult() = 0;
	virtual void clearCachedResult() = 0;
	virtual void clearAllCachedResults() = 0;
	
	/**
	* 设置要求和的字段
	* @param column 字段名
	*/
	virtual void sum(string column) = 0;
	/**
	* 设置求平均值的字段
	* @param column 字段名
	*/
	virtual void average(string column) = 0;
	/**
	* 设置要查询最大值的字段
	* @param cloumn 字段名
	*/
	virtual void max(string column) = 0;
	/**
	* 设置要查询的最小值字段
	* @param column 字段名
	*/
	virtual void min(string column) = 0;
	/**
	* 设置按某个字段进行分组查询
	* @param column 字段名
	*/
	virtual void groupby(string column) = 0;
	/**
	*
	*/
	virtual void having(bool isHaving = false) = 0;
	virtual void setHasGroupCount(bool groupCount) = 0;

	/**
	* 设置HTTP请求头部 
	*/
	virtual void setHeader(vector<string> v) {}
	/**
	* 返回HTTP请求头部
	*/
    virtual vector<string> getHeader() {return m_header;}
  
    /**
    * 
    */
    virtual void enJson(Json::Value* value) = 0;
    /**
    * 
    */
    virtual void deJson(Json::Value* value) = 0;

	/**
	* 设置查询请求的类型
	*/
	inline void setQueryType(BmobQueryInterafce::Type type)
    {
        _queryType = type;
    };
   
   	/**
   	* 得到查询请求的类型
   	*/
    inline BmobQueryInterafce::Type getQueryType()
    {
        return _queryType;
    };

    inline void clear(){
    	this->m_whereData.clear();
    }

protected:
	/**
	* HTTP 请求的回调方法
	*/
	virtual void onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data) = 0;
	/**
	* 查询
	*/
	virtual void query() = 0;

	BmobQueryInterafce(){}

protected:
	/**
	* 触发查询操作的类型
	*/
	enum class DelegateType{
		_bFIND_D,
		_bGET_D,
		_bCOUNT_D,
		_bSTATICS_D
	};

protected:
	BmobQueryInterafce::Type _queryType;			//查询请求的类型//
	BmobQueryInterafce::DelegateType _delegateType; //触发查询的类型//

	CC_SYNTHESIZE(string,m_objectId,ObjectId);		//对象objectId //
	CC_SYNTHESIZE(string,m_tableName,TableName);	//对应的表名//

	CC_SYNTHESIZE(BmobFindDelegate*,m_pFindDelegate,FindDelegate);	//查询多条数据的回调接口//
	CC_SYNTHESIZE(BmobGetDelegate* ,m_pGetDelegate,GetDelegate);	//查询一个对象数据的回调接口//
	CC_SYNTHESIZE(BmobCountDelegate* ,m_pCountDelegate,CountDelegate);	//数量查询的回调接口//
	CC_SYNTHESIZE(BmobStaticsDelegate*, m_pStaticsDelegate,StaticDelegate);	 	//统计查询回调接口//

	std::vector<std::string> m_header;						//请求头部//
	std::multimap<string, cocos2d::CCObject *> m_whereData; //请求的数据//
	string m_url;		
	string m_order;		
	string m_queryKey;	
	string m_sum;	
	string m_group;
	string m_min;
	string m_max;
	string m_average;
	bool m_isHaving;
	bool m_groupCount;

	int m_limit;
	int m_skip;
};

#endif