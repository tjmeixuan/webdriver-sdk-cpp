// demo_cpp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include <string>
#include<iostream>
#include "webdriver_cpp.h"
#include "wdvalue.h"
#include "wdjson.h"

std::string APPID = "5b4564eaab00093b641e99b5";
std::string ACCESSKEY = "a59836a11b76dda496bac68c";
std::string SECRETKEY = "3dcc2142b326020d92b77b1c";
std::string PAGEID = "5b45b741aa4a3a3f5840d15b";
std::string PAGEID2 = "5bbc30e769516e40e8366d17";
std::string CIRCLE = "WDVZ6DE5OF";	// 页面1中的圆形组件，演示改变背景颜色
std::string BUTTON1 = "WDJTLFVEQQ";	// 页面1中的切换页面按钮
std::string BUTTON2 = "WDCIILJPWO";	// 页面1中的显示消息按钮
std::string BUTTON3 = "WDWLABJ5JW";	// 页面2中的切换页面按钮

void fNoticeCallback(const std::string& appid, const std::string& pageid, const std::string& wid, const std::string& name, const std::string& sid, const std::string& value, void* user)
{
	printf("rcv data wid = %s , name = %s, value = %s\r\n",  wid.c_str(), name.c_str(), value.c_str());

	if (pageid.compare(PAGEID) == 0)
	{
		if(wid.compare(BUTTON1) == 0)
		{
			// 第一页的按钮 id
			printf("收到 第一页 按钮的 点击事件, 准备跳转到第二页\n");

			// 跳转到第二页
			WEBDRIVER::CWebdriver::showPage(APPID, PAGEID, PAGEID2, "0");
		} 
		else if (wid.compare(BUTTON2) == 0)
		{
			// 显示消息
			const char* title = "hello";
			const char* message = "welcome to webdriver";

			WEBDRIVER::CWebdriver::sendMessage(APPID, PAGEID, "success", title, message, 3, sid);
		}
	}
	else if (pageid.compare(PAGEID2) == 0)
	{
		if (wid.compare(BUTTON3) == 0){
			// 第二页的按钮 id
			printf("收到 第二页 按钮的 点击事件, 准备跳转到第一页\n");
			// 跳转到第一页
			WEBDRIVER::CWebdriver::showPage(APPID, PAGEID2, PAGEID, sid);
		} 
	}
}

void fConnectStateCallback(const std::string& appid, bool state){
	printf("connect state, appid = %s , state = %d\r\n",  appid.c_str(), state);
}

int _tmain(int argc, _TCHAR* argv[])
{
	// _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );    //设置调试堆函数跟踪分配的方式 
    // _CrtSetBreakAlloc();     //这句话，在确实有内存泄露的情况下，给 内存分配编号

	std::string colors[]  = {"red", "blue", "yellow"};
	std::string serverip = "127.0.0.1";
	int index = 0;

	// 测试辅助函数
	std::cout<<"=== 测试辅助函数 ==="<<std::endl;
	std::string strvalue = "12.123456789";
	int a1;
	unsigned int a2;
	double a3;
	bool a4;
	std::string d1, d2, d3, d4;
	a1 = WEBDRIVER::WDValue::str_to_int(strvalue);
	a2 = WEBDRIVER::WDValue::str_to_uint(strvalue);
	a3 = WEBDRIVER::WDValue::str_to_double(strvalue);
	a4 = WEBDRIVER::WDValue::str_to_bool(strvalue);

	std::cout<<"a1="<<a1<<" a2="<<a2<<" a3="<<a3<<" a4="<<a4<<std::endl;

	d1 = WEBDRIVER::WDValue::int_to_str(a1);
	d2 = WEBDRIVER::WDValue::uint_to_str(a2);
	d3 = WEBDRIVER::WDValue::double_to_str(a3);
	d4 = WEBDRIVER::WDValue::bool_to_str(a4);

	std::cout<<"d1="<<d1<<" d2="<<d2<<" d3="<<d3<<" d4="<<d4<<std::endl;

	d3 = WEBDRIVER::WDValue::double_to_str(123456.123456);
	std::cout<<"double="<<123456.123456<<" str="<<d3<<std::endl;

	d3 = WEBDRIVER::WDValue::double_to_str(1.00000007);
	std::cout<<"double="<<1.00000007<<" str="<<d3<<std::endl;

	d3 = WEBDRIVER::WDValue::double_to_str(12345678.1);
	std::cout<<"double="<<12345678.1<<" str="<<d3<<std::endl;

	d3 = WEBDRIVER::WDValue::double_to_str(1.1234e-05);
	std::cout<<"double="<<1.1234e-05<<" str="<<d3<<std::endl;

	// 测试JSON对象和string 转换
	std::cout<<"=== 测试JSON ==="<<std::endl;
	// 解析json非格式化的字符串 到 JSON对象，读取JSON对象中的值
	std::string jsonstr = "{\"name\":\"webdriver\"}";
	Json::Value root;
	WEBDRIVER::ParseJsonValue(jsonstr, root);
	std::string name = root["name"].asString();
	std::cout<<"get name = "<<name<<std::endl;
	// 构建json对象，转字符串
	Json::Value root1;
	Json::Value childs;
	childs["name"] = "webdriver"; // 构成对象
	root1.append(childs);	// 构成数组
	std::string root1Str = WEBDRIVER::GetJsonStringWithNoStyled(root1);
	std::cout<<"get root1 = "<<root1Str<<std::endl;



	// 测试接口
	std::cout<<"=== 测试接口 ==="<<std::endl;
	WEBDRIVER::CWebdriver::config(serverip);
	WEBDRIVER::CWebdriver::connect(APPID, ACCESSKEY, SECRETKEY, fNoticeCallback, fConnectStateCallback);

	while(1){
		Sleep(1000);
		// 改变圆形的背景颜色
		WEBDRIVER::CWebdriver::write(APPID, PAGEID, CIRCLE, "bg", "0", colors[index]);
		index++;
		if(index >= 3) index = 0;
	}
	return 0;
}

