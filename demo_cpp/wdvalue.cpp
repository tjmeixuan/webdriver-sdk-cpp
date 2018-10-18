/** @file wdvalue.cpp
  * @brief 值和字符串互转辅助方法
  * @copyright (c) 2018, MeiXuan All rights reserved
  * @author MeiXuan01
  * @date 2018/10/10
  */
#include "stdafx.h"
#include "wdvalue.h"
#include <sstream>

namespace WEBDRIVER
{
WDValue::WDValue() 
{
}
int WDValue::str_to_int(std::string& value)
{
	int int_temp;
	std::stringstream stream(value);  
    stream>>int_temp;
	return int_temp;
}
unsigned int WDValue::str_to_uint(std::string& value)
{
	unsigned int int_temp;
	std::stringstream stream(value);  
    stream>>int_temp;
	return int_temp;
}
double WDValue::str_to_double(std::string& value)
{
	std::istringstream iss(value);
	double num;
	iss >> num;
	return num;
}
bool WDValue::str_to_bool(std::string& value)
{
	if(value.empty() || value.compare("0") == 0 || value.compare("false") == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

std::string WDValue::int_to_str(int value)
{
	std::string string_temp;
	std::stringstream stream;  
	stream<<value;
	string_temp=stream.str();   //此处也可以用 stream>>string_temp 
	return string_temp;
}
std::string WDValue::uint_to_str(unsigned int value)
{
	std::string string_temp;
	std::stringstream stream;  
	stream<<value;
	string_temp=stream.str();   //此处也可以用 stream>>string_temp 
	return string_temp;
}
std::string WDValue::double_to_str(long double value, int decplaces)
{
	char DECIMAL_POINT='.'; // 欧洲用法为','
	std::ostringstream out;
	int prec = std::numeric_limits<long double>::digits10; // 18
	out.precision(prec);//覆盖默认精度
	out<<value;
	std::string str= out.str(); //从流中取出字符串
	size_t n=str.find(DECIMAL_POINT);
 
	if ((n!=std::string::npos)&& (str.size()> n+decplaces)) //有小数点吗？ //后面至少还有decplaces位吗？
	{
		str[n+decplaces]='\0';//覆盖第一个多余的数
	}
	str.swap(std::string(str.c_str()));//删除nul之后的多余字符
	return str;
}
std::string WDValue::bool_to_str(bool value)
{
	std::string string_temp;
	string_temp = value?"1":"0";
	return string_temp;
}	
}

