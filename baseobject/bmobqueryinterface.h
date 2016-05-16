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
#include "../util/bmobsdkutil.h"


using namespace std;
using namespace bmobdelegate;
using namespace bmobutil;
USING_NS_CC;

namespace bmobsdk{
	class BmobQueryInterafce:public cocos2d::CCObject{
	public:
		/**
		* 通过要操作的表名创建一个Query对象
		*/
		BmobQueryInterafce(string tableName){
			m_tableName = tableName;
			_queryType = BmobHttpUtil::QueryRequestType::RequestIgnoreCache;

			m_pFindDelegate = NULL;
			m_pGetDelegate = NULL;
			m_pCountDelegate = NULL;
			m_pStaticsDelegate = NULL;
		}

		/**
		* 查询所有对象
		* @param delegate 查询回调接口
		* @return
		*/
		virtual void findObjects(BmobFindDelegate* delegate) = 0;
		/**
		* 直接通过表名查询对应表的所有数据
		* @param tableName 表名
		* @param delegate 查询回调接口
		* @return
		*/
		virtual void findObjects(string tableName,BmobFindDelegate* delegate) = 0;
		/**
		* 查询表的结构
		* @param tableName 表名
		* @param delegate 查询回调接口
		*/
		virtual void findTableStruct(string tableName,BmobFindDelegate* delegate) = 0;
		/**
		* 通过objectId 查询对应的数据
		* @param objectid 查询的objectId
		* @param delegate 查询的回调接口
		* @return
		*/
		virtual void getObject(string objectId,BmobGetDelegate* delegate) = 0;
		/**
		* 查询数量
		* @param delegate 回调接口
		* @param sign 是否需要返回数量对应的数据标志
		* @return
		*/
		virtual void count(BmobCountDelegate* delegate,bool sign = false) = 0;
		/**
		* 统计操作
		* @param delegate 回调接口
		* @return void
		*/
		virtual void findStatistics(BmobStaticsDelegate* delegate) = 0;
		/**
		* 执行sdk定义的sql查询
		* @param bql 查询语句
		* @param value sql语句对应的值
		* @param delegate 回调接口
		* @return
		*/
		virtual void BSQLFindObjects(string bql,CCObject* values,BmobBQLDelegate* delegate) = 0;
		/**
		* 添加查询满足的where条件,如：name = "Harrier"添加到查询中
		* @param seg 字段名
		* @param object 对应的值
		* @return
		*/
		virtual void addWhereEqualTo(string seg,CCObject *object) = 0;
		/**
		* 添加查询不满足的where条件,如：name != "Harrier"添加到查询中
		* @param seg 字段名
		* @param object 对应的值
		* @return
		*/
		virtual void addWhereNotEqualTo(string seg,CCObject *object) = 0;
		/**
		* 添加大于某个值的where条件
		* @param seg string 	字段名
		* @param object CCObject*	对应的值
		* @return
		*/
		virtual void addWhereGreatorThan(string seg,CCObject *object) = 0;
		/**
		* 添加小于某个值的where条件
		* @param seg 字段名
		* @param object 对应字段的值
		* @return
		*/
		virtual void addWhereLessThan(string seg,CCObject *object) = 0;
		/**
		* 添加小于等于某个值的where条件
		* @param seg 字段名
		* @param object 对应字段的值
		* @return
		*/
		virtual void addWhereLessThanOrEqualTo(string seg,CCObject *object) = 0;
		/**
		* 添加大于某个值的where条件
		* @param seg 字段名
		* @param object 对应的值
		* @return
		*/
		virtual void addWhereGreaterThan(string seg,CCObject *object) = 0;
		/**
		* 添加大于等于某个值的where条件
		* @param seg 字段名
		* @param object 对应的值
		* @return
		*/
		virtual void addWhereGreaterThanOrEqualTo(string seg,CCObject *object) = 0;
		/**
		* 添加包含数组中某个值的where条件
		* @param seg 字段名
		* @param array 需要查询字段包含的值
		* @return
		*/
		virtual void addWhereContainedIn(string seg,CCObject* array) = 0;
		/**
		* 添加不包含数组中某个值的where条件
		* @param seg 字段名
		* @param array 需要查询字段不包含的值
		* @return
		*/
		virtual void addWhereNotContainedIn(string seg,CCObject* array) = 0;
		/**
		* 添加包含数组中所有值的where条件
		* @param seg 字段名
		* @param array 需要查询包含的数组
		* @return void
		*/
		virtual void addWhereContainsAll(string seg,CCArray* array) = 0;
		virtual void addWhereMatches() = 0;
		virtual void addWhereContains() = 0;
		/**
		* 添加查询某个字段存在的where条件
		* @param column	查询的字段名
		* @return
		*/
		virtual void addWhereExists(string column) = 0;
		/**
		* 添加查询某个字段不存在的where条件
		* @param column 查询的字段名
		* @return
		*/
		virtual void addWhereDoesNotExists(string column) = 0;
		/**
		* 设置查询返回的字段
		* @param column 字段名
		* @return
		*/
		virtual void addQueryKeys(string column) = 0;

		/**
		* where excute
		*/
		virtual void whereStartsWith() = 0;
		virtual void whereEndsWith() = 0;


		/**
		* 设置查询返回的数量
		* @param limit int查询返回的数量
		* @return
		*/
		virtual void setLimit(int limit) = 0;

		/**
		* 设置查询跳转的页或者是要查询第几页
		* @param skip设置要跳转页
		* @return
		*/
		virtual void setSkip(int skip) = 0;
		/**
		* 设置排序方法
		* @param key string 字段名
		* @return
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
		* @return void
		*/
		virtual void sum(string column) = 0;
		/**
		* 设置求平均值的字段
		* @param column 字段名
		* @return
		*/
		virtual void average(string column) = 0;
		/**
		* 设置要查询最大值的字段
		* @param cloumn 字段名
		* @return
		*/
		virtual void max(string column) = 0;
		/**
		* 设置要查询的最小值字段
		* @param column 字段名
		* @return
		*/
		virtual void min(string column) = 0;
		/**
		* 设置按某个字段进行分组查询
		* @param column 字段名
		* @return
		*/
		virtual void groupby(string column) = 0;
		/**
		* * @return
		*/
		virtual void having(bool isHaving = false) = 0;
		virtual void setHasGroupCount(bool groupCount) = 0;

		/**
		* 设置HTTP请求头部
		* @return
		*/
		virtual void setHeader(vector<string> v) {}
		/**
		* 返回HTTP请求头部
		* @return vector<string>
		*/
	    virtual vector<string> getHeader() {return m_header;}

	    /**
	    * @param value
			* @return
	    */
	    virtual void enJson(Json::Value* value) = 0;
			/**
	    * 将data数据转换城json数据存储到value中
	    * @param value Json::Value
	    * @param data map<string,CCObject*>
	    * @return
	    */
	    virtual void enJson(Json::Value* value,map<string,CCObject*> data) = 0;
	    /**
	    *
	    */
	    virtual void deJson(Json::Value* value) = 0;

		/**
		* 设置查询请求的类型
		* @param type BmobHttpUtil::QueryRequestType 查询的类型
		* @return
		*/
		inline void setQueryType(BmobHttpUtil::QueryRequestType type){
        	_queryType = type;
	    };

	   	/**
	   	* 得到查询请求的类型
			* @return BmobHttpUtil::QueryRequestType
	   	*/
	    inline BmobHttpUtil::QueryRequestType getQueryType(){
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
		virtual void query(string tag) = 0;

		virtual map<string,CCObject*> getSolidRequestData() = 0;

		BmobQueryInterafce(){}

	protected:
		CC_SYNTHESIZE(string,m_objectId,ObjectId);		//对象objectId //
		CC_SYNTHESIZE(string,m_tableName,TableName);	//对应的表名//

		/**
		* 统计查询回调接口
		*/
		CC_SYNTHESIZE(BmobStaticsDelegate*, m_pStaticsDelegate,StaticDelegate);
		/**
		* 数量查询的回调接口
		*/
		CC_SYNTHESIZE(BmobCountDelegate* ,m_pCountDelegate,CountDelegate);
		/**
		* 查询多条数据的回调接口
		*/
		CC_SYNTHESIZE(BmobFindDelegate*,m_pFindDelegate,FindDelegate);
		/**
		* 查询一个对象数据的回调接口
		*/
		CC_SYNTHESIZE(BmobGetDelegate* ,m_pGetDelegate,GetDelegate);
		/**
		* 执行bsql查询回调
		*/
		CC_SYNTHESIZE(BmobBQLDelegate*,m_pBQLDelegate,BQLDelegate);

		std::multimap<string, cocos2d::CCObject *> m_whereData; //请求的数据//
		BmobHttpUtil::QueryRequestType _queryType;			//查询请求的类型//
		std::vector<std::string> m_header;						//请求头部//
		map<string,CCObject*> m_mapData;
		string m_url;
	};

}

#endif
