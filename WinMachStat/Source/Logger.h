#pragma once

#include "log4cpp/config-win32.h"
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/NDC.hh"
#include "log4cpp/PropertyConfigurator.hh"

#include <string>
#include <memory>

#define CODE_LOCATION " " __FILE__ ":"

#define LOG_EMERG(__logstream)   __logstream << log4cpp::Priority::EMERG  << CODE_LOCATION << __LINE__ << " (" << __FUNCTION__ << ") " 
#define LOG_ALERT(__logstream)   __logstream << log4cpp::Priority::ALERT  << CODE_LOCATION << __LINE__ << " (" << __FUNCTION__ << ") " 
#define LOG_CRIT(__logstream) 	 __logstream << log4cpp::Priority::CRIT   << CODE_LOCATION << __LINE__ << " (" << __FUNCTION__ << ") " 
#define LOG_ERROR(__logstream)   __logstream << log4cpp::Priority::ERROR  << CODE_LOCATION << __LINE__ << " (" << __FUNCTION__ << ") " 
#define LOG_WARN(__logstream)    __logstream << log4cpp::Priority::WARN   << CODE_LOCATION << __LINE__ << " (" << __FUNCTION__ << ") " 
#define LOG_NOTICE(__logstream)  __logstream << log4cpp::Priority::NOTICE << CODE_LOCATION << __LINE__ << " (" << __FUNCTION__ << ") " 
#define LOG_INFO(__logstream)    __logstream << log4cpp::Priority::INFO   << CODE_LOCATION << __LINE__ << " (" << __FUNCTION__ << ") " 
#define LOG_DEBUG(__logstream)   __logstream << log4cpp::Priority::DEBUG  << CODE_LOCATION << __LINE__ << " (" << __FUNCTION__ << ") " 

typedef log4cpp::Category LoggerStream;

#ifndef LOG4CPPCONFIG
#define LOG4CPPCONFIG "./log4cpp.properties"
#endif


namespace WinMachStat {
	class Logger {
		Logger();
		~Logger();
		static bool init;
		static std::map<std::string, LoggerStream*> LoggerCache;
	public:
		static void InitLogger(std::string config);
		static LoggerStream& getLogger(std::string category, std::string config = "");
	};
}