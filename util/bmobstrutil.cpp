#include "bmobstrutil.h"

string BmobStrUtil::remove_tab_enter_space(string *str){
	if (str == NULL)
	{
		/* code */
		return "";
	}
	string::iterator it,temp;
	it = str->begin();
	temp = it;
	while(it != str->end()){
		temp = it;
		if (*it == '\n' || *it == '\0' || *it == ' ')
		{
			/* code */
			temp = it - 1;
			str->erase(it);
			it = temp;
		}
		it++;
	}

	return *str;
}