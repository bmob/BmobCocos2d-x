/*
 * bmobbase64.h
 *
 *  Created on: 14/03/2011
 *      Author: zhou
 *
 * 实现数据base64编码
 */

#ifndef BASE64_H_
#define BASE64_H_
#include <string>

namespace bmobbase64
{

	class encode_t
	{
	public:
			encode_t(std::string::size_type size);
			void operator() (std::string::value_type c);
			std::string str();

	private:
			enum
			{
				zero = 0,
				two,
				four
			} state;

			unsigned int remainder;
			std::string encoded;
	};

	class decode_t
	{
	public:
			decode_t(std::string::size_type size);
			void operator() (std::string::value_type c);
			std::string str() const;

	private:
			enum
			{
				zero = 0,
				six,
				four,
				two
			} state;
			unsigned int remainder;
			std::string decoded;
	};

	/*
	 * 对数据进行base64编码
	 * @param str 要编码的数据
	 * @return string 	返回编码后的数据
	 */
	std::string encode(const std::string& str);

	/*
	 * 对数据进行base64解码
	 * @param str 要解码的数据
	 * @return 返回解码后的数据
	 */
	std::string decode(const std::string& str);

}

#endif /* BASE64_H_ */
