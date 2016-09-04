#pragma once


namespace noob
{
	enum class log_importance : uint8_t
	{
		CRITICAL = 0, ERROR = 1, WARNING = 2, INFO = 4, END_USER = 5
	};

	static std::string to_string(noob::log_importance arg) noexcept(true)
	{
		switch(arg)
		{
			case(noob::log_importance::CRITICAL):
			{
				return "critical";
			}
			case(noob::log_importance::ERROR):
			{
				return "error";
			}
			case(noob::log_importance::WARNING):
			{
				return "warning";
			}
			case(noob::log_importance::INFO):
			{
				return "info";
			}
			case(noob::log_importance::END_USER):
			{
				return "end user";
			}
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

			static void log(noob::log_importance imp, const std::string& msg) noexcept(true)
			{
				f.log(imp, msg);
			}

		protected:
			 static LogFunctor f;	
	};
}
