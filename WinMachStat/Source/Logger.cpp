#include "Logger.h"

namespace WinMachStat {
	bool Logger::init = false;
	std::map<std::string, LoggerStream*> Logger::LoggerCache;

	void Logger::InitLogger(std::string config) {
		if (!init) {
			try {
				log4cpp::PropertyConfigurator::configure(config);
			}
			catch (log4cpp::ConfigureFailure &e) {
				std::cerr << "No log4cpp " << e.what() << std::endl;
				return;
			}
		}
		init = true;
	}

	LoggerStream& Logger::getLogger(std::string category, std::string config) {
		if (!init) {
			InitLogger(config);
		}
		auto it = LoggerCache.find(category);
		if (it == LoggerCache.end()) {
			LoggerStream &l = LoggerStream::getInstance(category);
			LoggerCache[category] = &l;
			return l;
		}
		else {
			LoggerStream &l = *(LoggerCache[category]);
			return l;
		}
	}
} /* namespace WinMachStat */