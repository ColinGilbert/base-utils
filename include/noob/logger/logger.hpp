#pragma once
#include <string>

namespace noob
{
	enum class importance : uint8_t
	{
		CRITICAL = 0, ERROR = 1, WARNING = 2, INFO = 4
	};

	static std::string to_string(noob::importance arg) noexcept(true)
	{
		switch(arg)
		{
			case(noob::importance::CRITICAL):
			{
				return "critical";
			}
			case(noob::importance::ERROR):
			{
				return "error";
			}
			case(noob::importance::WARNING):
			{
				return "warning";
			}
			case(noob::importance::INFO):
			{
				return "info";
			}
			//case(noob::importance::END_USER):
			//{
				return "end user";
			// }
			default:
			{
				return "INVALID";
			}
		}
	}

	template<typename LogFunctor> class logger_impl
	{
		public:
			//logger_impl(LogFunctor arg) noexcept(true) : f(arg) {}

			static void log(noob::importance imp, const std::string& msg) noexcept(true)
			{
				f.log(imp, msg);
			}

		protected:
			 static LogFunctor f;	
	};
}
