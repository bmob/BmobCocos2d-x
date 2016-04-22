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

namespace bmobsdk{
	class BmobQuery:public BmobQueryInterafce{
	public:

		BmobQuery(string tableName);

		virtual ~BmobQuery();

		virtual void findObjects(BmobFindDelegate* delegate) override final;
		virtual void findObjects(string tableName,BmobFindDelegate* delegate) override final;
		virtual void getObject(string objectId,BmobGetDelegate* delegate) override final;
		virtual void count(BmobCountDelegate* delegate,bool sign = false) override final;
		virtual void findStatistics(BmobStaticsDelegate* delegate) override final;
		virtual void BSQLFindObjects(string bql,CCObject* values,BmobBQLDelegate* delegate) override final;

		virtual void addWhereEqualTo(string seg,CCObject *object) override final;
		virtual void addWhereNotEqualTo(string seg,CCObject *object) override final;
		virtual void addWhereGreatorThan(string seg,CCObject* object) override final;
		virtual void addWhereLessThan(string seg,CCObject* object) override final;
		virtual void addWhereLessThanOrEqualTo(string seg,CCObject* object) override final;
		virtual void addWhereGreaterThan(string seg,CCObject* object) override final;
		virtual void addWhereGreaterThanOrEqualTo(string seg,CCObject* object) override final;
		virtual void addWhereContainedIn(string seg,CCObject* array) override final;
		virtual void addWhereNotContainedIn(string seg,CCObject* array) override final;
		virtual void addWhereContainsAll(string seg,CCArray* array) override final;
		virtual void addWhereExists(string column)override final;
		virtual void addWhereDoesNotExists(string column)override final;

		virtual void addWhereMatches() override final;
		virtual void addWhereContains() override final;
		virtual void whereStartsWith() override final;
		virtual void whereEndsWith() override final;



		virtual void setLimit(int limit) override final;
		virtual void setSkip(int skip) override final;
		virtual void order(string key) override final;


		virtual void setCachePolicy()  override final;

		virtual bool hasCachedResult()  override final;
		virtual void clearCachedResult()  override final;
		virtual void clearAllCachedResults()  override final;

		virtual void addQueryKeys(string column)  override final;


		virtual void sum(string column)  override final;
		virtual void average(string column)  override final;
		virtual void max(string column)  override final;
		virtual void min(string column)  override final;
		virtual void groupby(string column) override final;
		virtual void having(bool isHaving = false)  override final;
		virtual void setHasGroupCount(bool groupCount)  override final;

		virtual void setHeader(vector<string> v)  override final;
		virtual vector<string> getHeader()  override final;

		virtual void enJson(Json::Value* value)  override final;
		virtual void enJson(Json::Value* value,map<string,CCObject*> data) override final;
		virtual void deJson(Json::Value* value) override final;

	protected:
		virtual void onHttpRequestCompleted(cocos2d::CCNode *pSender,void *data)  override final;
		virtual map<string,CCObject*> getSolidRequestData() override final;
		virtual void query(string tag)  override final;

	private:
	};
}

#endif
