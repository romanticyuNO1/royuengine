#pragma once

#include <memory>

#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Royu
{
	class ROYUYU_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& get_core_logger()
		{
			return s_core_logger;
		}

		inline static std::shared_ptr<spdlog::logger>& get_client_logger()
		{
			return s_client_logger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_core_logger;
		static std::shared_ptr<spdlog::logger> s_client_logger;
	};
}

//core logger macros
#define RY_CORE_TRACE(...)	::Royu::Log::get_core_logger()->trace(__VA_ARGS__)
#define RY_CORE_INFO(...)	::Royu::Log::get_core_logger()->info(__VA_ARGS__)
#define RY_CORE_WARN(...)	::Royu::Log::get_core_logger()->warn(__VA_ARGS__)
#define RY_CORE_ERROR(...)	::Royu::Log::get_core_logger()->error(__VA_ARGS__)
#define RY_CORE_FATAL(...)	::Royu::Log::get_core_logger()->fatal(__VA_ARGS__)

//client logger macros
#define RY_TRACE(...)	::Royu::Log::get_client_logger()->trace(__VA_ARGS__)
#define RY_INFO(...)	::Royu::Log::get_client_logger()->info(__VA_ARGS__)
#define RY_WARN(...)	::Royu::Log::get_client_logger()->warn(__VA_ARGS__)
#define RY_ERROR(...)	::Royu::Log::get_client_logger()->error(__VA_ARGS__)
#define RY_FATAL(...)	::Royu::Log::get_client_logger()->fatal(__VA_ARGS__)


