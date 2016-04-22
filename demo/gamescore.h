#ifndef GAMESCORE_H_
#define GAMESCORE_H_

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "../bmobsdk.h"

using namespace std;
using namespace bmobsdk;
USING_NS_CC_EXT;
USING_NS_CC;

class GameScore:public BmobObject{
public:
	GameScore(string tableName);
	virtual ~GameScore();

private:
	CC_SYNTHESIZE(std::string,m_name,Name);
	CC_SYNTHESIZE(int,m_score,Score);
	CC_SYNTHESIZE(string,m_info,Info);
};

#endif
