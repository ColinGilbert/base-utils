#include <noob/graph/graph.hpp>
#include <noob/logger/logger.hpp>

#include <noob/strings/strings.hpp>

#include <cassert>
#include <iostream>
// #include <sstream>
namespace noob
{
	struct log_funct
	{
		static void log(noob::log_importance imp, const std::string& s)
		{
			std::cout << noob::concat(noob::to_string(imp), ": ", s, "\n");
		}
	};

	typedef logger_impl<log_funct> logger;
}

int main()
{
	noob::logger::log(noob::log_importance::INFO, noob::concat("Testing logger! ", noob::to_string(0.9998)));
	// noob::graph g;


	return 0;
}
