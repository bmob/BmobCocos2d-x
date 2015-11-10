/**
* create by zh_u 2015-10-25
* 查询数据对象类
*/

#ifndef BMOBSDK_BMOBQUERY_H_
#define BMOBSDK_BMOBQUERY_H_

#include <iostream>
#include "cocos2d.h"
#include "bmobqueryinterface.h"
#include "bmobSDKinit.h"


using namespace std;
USING_NS_CC;

class BmobQuery:public BmobQueryInterafce{
public:

	BmobQuery(string tableName);

	virtual ~BmobQuery();

	virtual void findObjects(BmobFindDelegate* delegate);
	virtual void findObjects(string tableName,BmobFindDelegate* delegate);
	virtual void getObject(string objectId,BmobGetDelegate* delegate);
	virtual void count(BmobCountDelegate* delegate,bool sign = false) ;
	virtual void findStatistics(BmobStaticsDelegate* delegate);

	virtual void addWhereEqualTo(string seg,CCObject *object);
	virtual void addWhereNotEqualTo(string seg,CCObject *object);
	virtual void addWhereGreatorThan(string seg,CCObject* object) ;
	virtual void addWhereLessThan(string seg,CCObject* object) ;
	virtual void addWhereLessThanOrEqualTo(string seg,CCObject* object);
	virtual void addWhereGreaterThan(string seg,CCObject* object);
	virtual void addWhereGreaterThanOrEqualTo(string seg,CCObject* object) ;
	virtual void addWhereContainedIn(string seg,CCObject* array) ;
	virtual void addWhereNotContainedIn(string seg,CCObject* array) ;
	virtual void addWhereContainsAll(string seg,CCArray* array) ;
	virtual void addWhereExists(string column);
	virtual void addWhereDoesNotExists(string column);

	virtual void addWhereMatches() ;
	virtual void addWhereContains() ;
	virtual void whereStartsWith() ;
	virtual void whereEndsWith() ;

	

	virtual void setLimit(int limit);
	virtual void setSkip(int skip);
	virtual void order(string key);

	
	virtual void setCachePolicy() ;

	virtual bool hasCachedResult() ;
	virtual void clearCachedResult() ;
	virtual void clearAllCachedResults() ;

	virtual void addQueryKeys(string column) ;
	

	virtual void sum(string column) ;
	virtual void average(string column) ;
	virtual void max(string column) ;
	virtual void min(string column) ;
	virtual void groupby(string column);
	virtual void having(bool isHaving = false) ;
	virtual void setHasGroupCount(bool groupCount) ;

	virtual void setHeader(vector<string> v);
	virtual vector<string> getHeader();

	virtual void enJson(Json::Value* value);
	virtual void deJson(Json::Value* value);

protected:
	virtual void onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data) ;
	virtual void query() ;

private:
	/**
	* 获取查询的URL
	*/
	inline string getBaseUrl(){
		if (strcmp(m_tableName.c_str(),BmobSDKInit::USER_TABLE.c_str()) == 0)
	    {
	        /* code */
	        return BmobSDKInit::USER_URL;
	    }else{
	        return BmobSDKInit::URL + this->m_tableName;
	    }
	}

	/**
	* 获取对应查询数量的请求格式
	*/
	inline string getLimit(){
		if (m_limit == 0)
		{
			/* code */
			return "";
		}
		stringstream ss;
	    ss<<m_limit;
	    string  s=ss.str();
	    s = "limit=" + s + "&";

	    m_limit = 0;

	    return s;
	}

	/**
	* 获取查询页的请求格式
	*/
	inline string getSkip(){
		if (m_skip == 0)
		{
			/* code */
			return "";
		}
		stringstream ss;
	    ss<<m_skip;
	    string  s=ss.str();
	    s = "skip=" + s + "&";

	    m_skip = 0;

	    return s;
	}

	/**
	* 获取排序的请求格式
	*/
	inline string getOrder(){
		if (m_order.empty())
		{
			/* code */
			return "";
		}

		string ord = "order=" + m_order + "&";

		m_order.clear();

		return ord;
	}

	/**
	* 获取返回字段的请求格式
	*/
	inline string getQueryKey(){
		if (m_queryKey.empty())
		{
			/* code */
			return "";
		}

		string key = "key=" + m_queryKey + "&";
		m_queryKey.clear();

		return key;
	}

	/**
	* 获取数量查询的请求格式
	*/
	inline string getSum(){
		if (m_sum.empty())
		{
			/* code */
			return "";
		}

		string sum = "sum=" + m_sum +"&";
		m_sum.clear();

		return sum;
	}

	/**
	* 获取分组查询的请求格式
	*/
	inline string getGroup(){
		if (m_group.empty())
		{
			/* code */
			return "";
		}

		string group = "groupby=" + m_group + "&";
		m_group.clear();

		return group;
	}

	/**
	* 获取分组数量的请求格式
	*/
	inline string getGroupCount(){
		if (!m_groupCount)
		{
			/* code */
			return "";
		}

		string count = "groupcount=true&";

		m_groupCount = false;

		return count;
	}

	/**
	* 获取查询字段最小值的请求格式
	*/
	inline string getMin(){
		if (m_min.empty())
		{
			/* code */
			return "";
		}

		string mi = "min=" + m_min + "&";
		m_min.clear();

		return mi;
	}

	/**
	* 获取查询最大值的请求格式
	*/
	inline string getMax(){
		if (m_max.empty())
		{
			/* code */
			return "";
		}

		string ma = "max=" + m_max + "&";
		m_max.clear();

		return ma;
	}

	/**
	* 获取查询平均值的请求格式
	*/
	inline string getAverage(){
		if (m_average.empty())
		{
			/* code */
			return "";
		}

		string averag = "average=" + m_average + "&";
		m_average.clear();

		return averag;
	}
};

#endif