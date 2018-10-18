/** @file wdjson.cpp
  * @brief JSON¸¨Öú·½·¨
  * @copyright (c) 2018, MeiXuan All rights reserved
  * @author MeiXuan01
  * @date 2018/10/10
  */

#include "stdafx.h"
#include "wdjson.h"

namespace WEBDRIVER
{

bool StrListToJsonString(const std::list<std::string>& list, std::string& out)
{
	Json::Value json_ids;
	for (auto it = list.begin(); it != list.end(); it++)
	{
		json_ids.append(*it);
	}
	out = GetJsonStringWithNoStyled(json_ids);
	return true;
}

bool JsonStrArrayToList(const Json::Value& array_str, std::list<std::string>& out)
{
	if (array_str.isArray())
	{
		int size = array_str.size();
		for (int index = 0; index < size; index++)
		{
			out.push_back(array_str[index].asString());
		}
		return true;
	}
	return false;
}

bool JsonArrayStringToList(const std::string& array_str, std::list<std::string>& out)
{
	Json::Value value;
	if (ParseJsonValue(array_str, value) && value.isArray())
	{
		return JsonStrArrayToList(value, out);
	}
	return false;
}

bool ParseJsonValue(const std::string &content, Json::Value &values)
{
	Json::Reader reader;
	if (reader.parse(content, values))
	{
		return true;
	}
	return false;
}

std::string GetJsonStringWithNoStyled(const Json::Value& values)
{
	Json::FastWriter fw;
	return fw.write(values);
}

Json::Value GetJsonValueFromJsonString(const std::string& json_string)
{
	Json::Value value;
	Json::Reader reader;
	if (!reader.parse(json_string, value) /*|| !value.isArray()*/)
		assert(0);

	return value;
}
}