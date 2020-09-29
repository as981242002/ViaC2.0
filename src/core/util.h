#pragma once

#include<string>
#include<cstdio>
#include<iostream>
#include<mutex>
#include<thread>

namespace T
{

using File_t = FILE*;

constexpr int nil = -1;

namespace Util
{
	enum class TextColor
	{
		Black = 0,
		Green,
		Red,
		Yellow,
		Blue,
		Purple,
		Cyan,
		White
	};
	
	enum class LogLevel
	{
		Waring = 0,
		Info,
		Error,
	};
	
	//cross platform
	void clearString(std::string& str);
	
	std::string getLogFileName(const std::string& basename);

	std::string getNowTime();

	//only linux
	std::string getColorText(const std::string& str, TextColor color, int32_t extraInfo = nil);


	class Thread
	{
	public:
		template<class Func, typename ... Args>
		Thread(const std::string& name,Func&& f, Args&& ... args);
		
		template<class Func, typename ... Args>
		Thread(const char* name, Func&& f, Args&& ... args);

		~Thread();

		const std::string& geThreadName() const { return name_; };
	private:
		void func();
	private:
		std::thread worker_;
		std::string name_;
	};
}

namespace FileUtil
{
	class File
	{
	public:
		explicit File(const std::string& path, int32_t flushInterval,  int32_t checkEveryN = 1024);

		explicit File(const char* path, int32_t flushInterval, int32_t checkEveryN = 1024);

		~File();
		
		File& operator=(const File&) = delete;
		
		File(const File&) = delete;
		
		void write(const std::string& str);
		
		void write(const char* str, uint32_t size);
		
		void flush();
	private:
		void init();
		
		void windUp();
	private:
		std::string path_;
		int32_t flushInterval_;
		int32_t checkEveryN_;
		File_t file_;
		uint64_t writeSize_;
		uint32_t writeCount_;
	};

}
};