#include "bmobstrutil.h"

namespace bmobutil{
		string BmobStrUtil::remove_tab_enter_space(string *str){
				if (str == NULL)
				{
					return "";
				}

				string::iterator it,temp;
				it = str->begin();
				temp = it;
				while(it != str->end()){
						temp = it;
						if (*it == '\n' || *it == '\0' || *it == '\r' || *it == '\t' \
								|| (*it == ' ' && *(it - 1) != '\"')){
								temp = it - 1;
								str->erase(it);
								it = temp;
						}

						it++;
				}

				return *str;
		}
}
