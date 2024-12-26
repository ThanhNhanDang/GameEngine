#include "Logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/common.h>	

namespace VIEngine {
	Shared<spdlog::logger> Logger::sCoreLogger = nullptr;
	Shared<spdlog::logger> Logger::sClientLogger = nullptr;

	void Logger::Init() {

		// EX: [22:40:00] [VIEngine::Application::Init:11] [VIEngine] [thread 1000] Logger works  
		spdlog::set_pattern("%^[%H:%M:%S] [%!:%#] [%n] [thread %t] %v%$");

		sCoreLogger = spdlog::stdout_color_mt("VIEngine");
		sCoreLogger->set_level(spdlog::level::trace);

		sClientLogger = spdlog::stdout_color_mt("Client");
		sClientLogger->set_level(spdlog::level::trace);
	}
}
