// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 WEBDRIVER_CPP_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// WEBDRIVER_CPP_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifndef _WEBDRIVER_CPP_H_
#define _WEBDRIVER_CPP_H_

#include <string>
#include <functional>

#ifdef WEBDRIVER_CPP_EXPORTS
#define WEBDRIVER_CPP_API __declspec(dllexport)
#else
#define WEBDRIVER_CPP_API __declspec(dllimport)
#endif

namespace WEBDRIVER
{

	// 此类是从 webdriver_cpp.dll 导出的
	class WEBDRIVER_CPP_API CWebdriver
	{
	public: 
		typedef std::function<void(const std::string& appid, const std::string& pageid, const std::string& wid, const std::string& name, const std::string& sid, const std::string& value, void* user)> NOTICE_CALLBACK;
		typedef std::function<void(const std::string& appid, bool state)> CONNECTSTATE_CALLBACK;
	public:
		CWebdriver(void);
		// TODO: 在此添加您的方法。

	public:
		static int config(const std::string& serverip);

		static int connect(const std::string& appid, const std::string& accesskey, const std::string& secretkey, NOTICE_CALLBACK noticeCallback, CONNECTSTATE_CALLBACK connectStateCallback);
		static int disconnect(const std::string& appid);

		static int write(const std::string& appid, const std::string& pageid, const std::string& wid, const std::string& name, const std::string& sid, const std::string& value);
		static int read(const std::string& appid, const std::string& pageid, const std::string& wid, const std::string& name, void* value);

		static int showPage(const std::string& appid, const std::string& pageid, const std::string& targetpageid, const std::string& sid);
		static int sendMessage(const std::string& appid, const std::string& pageid, const std::string& type, const std::string& title, const std::string& message, int duration, const std::string& sid);
	};

}

#endif //!_WEBDRIVER_CPP_H_