
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Shunya
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("Shunya");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);

	}



}

// Core log macros

#define Shunya_Core_Error(...)   :: Shunya::Log::GetCoreLogger()-> error(__VA_ARGS__)
#define Shunya_Core_Warning(...) :: Shunya::Log::GetCoreLogger()-> warn(__VA_ARGS__)
#define Shunya_Core_Info(...)	 :: Shunya::Log::GetCoreLogger()-> info(__VA_ARGS__)
#define Shunya_Core_Fatal(...)   :: Shunya::Log::GetCoreLogger()-> fatal(__VA_ARGS__)
#define Shunya_Core_Trace(...)   :: Shunya::Log::GetCoreLogger()-> trace(__VA_ARGS__)

// Client Log Macros

#define Shunya_Error(...)   :: Shunya::Log::GetClientLogger()-> error(__VA_ARGS__)
#define Shunya_Warning(...) :: Shunya::Log::GetClientLogger()-> warn(__VA_ARGS__)
#define Shunya_Info(...)	 :: Shunya::Log::GetClientLogger()-> info(__VA_ARGS__)
#define Shunya_Fatal(...)   :: Shunya::Log::GetClientLogger()-> fatal(__VA_ARGS__)
#define Shunya_Trace(...)   :: Shunya::Log::GetClientLogger()-> trace(__VA_ARGS__)