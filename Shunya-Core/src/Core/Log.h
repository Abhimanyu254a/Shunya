#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include <memory>

namespace Shunya
{
	class SHUNYA_API Log
	{
	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}


// Core log macros

#define SHUNYA_CORE_ERROR(...)   :: Shunya::Log::GetCoreLogger()-> error(__VA_ARGS__)
#define SHUNYA_CORE_WARNING(...) :: Shunya::Log::GetCoreLogger()-> warn(__VA_ARGS__)
#define SHUNYA_CORE_INFO(...)	 :: Shunya::Log::GetCoreLogger()-> info(__VA_ARGS__)
#define SHUNYA_CORE_FATAL(...)   :: Shunya::Log::GetCoreLogger()-> fatal(__VA_ARGS__)
#define SHUNYA_CORE_TRACE(...)   :: Shunya::Log::GetCoreLogger()-> trace(__VA_ARGS__)

// Client Log Macros

#define SHUNYA_ERROR(...)   :: Shunya::Log::GetClientLogger()-> error(__VA_ARGS__)
#define SHUNYA_WARNING(...) :: Shunya::Log::GetClientLogger()-> warn(__VA_ARGS__)
#define SHUNYA_INFO(...)	 :: Shunya::Log::GetClientLogger()-> info(__VA_ARGS__)
#define SHUNYA_FATAL(...)   :: Shunya::Log::GetClientLogger()-> fatal(__VA_ARGS__)
#define SHUNYA_TRACE(...)   :: Shunya::Log::GetClientLogger()-> trace(__VA_ARGS__)
