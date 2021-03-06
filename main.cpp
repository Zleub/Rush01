#include <iostream>
#include "Monitor.hpp"
#include "CPUModule.hpp"
#include "TimeModule.hpp"
#include "UserInfoModule.hpp"
#include "OSModule.hpp"
#include "NetworkModule.hpp"
#include "MemoryModule.hpp"

int		main(int argc, char ** argv)
{
	if (argc != 2) {
		std::cout << "Plz, don't mess around: ./ft_gkrellm [graphic|console]" << std::endl;
		return (-1);
	}

	if (std::string(argv[1]) == "graphic")
		Monitor::initMLX();
	else if (std::string(argv[1]) == "console")
		Monitor::initNcurses();
	else {
		std::cout << "Plz, don't mess around: ./ft_gkrellm [graphic|console]" << std::endl;
		return (-1);
	}

	Monitor::registerModule(new UserInfoModule());
	Monitor::registerModule(new CPUModule());
	Monitor::registerModule(new OSModule());
	Monitor::registerModule(new MemoryModule());
	Monitor::registerModule(new UserInfoModule());
	Monitor::registerModule(new TimeModule());
	Monitor::registerModule(new NetworkModule());

	Monitor::startMonitoring();

	return 0;
}
