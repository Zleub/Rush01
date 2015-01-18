#include <iostream>
#include "Monitor.hpp"
#include "CPUModule.hpp"
#include "TimeModule.hpp"
#include "UserInfoModule.hpp"

int		main(int argc, char ** argv)
{
	if (argc != 2) {
		std::cout << "Plz, not mess around: ./ft_gkrellm [graphic|console]" << std::endl;
		return (-1);
	}

	if (std::string(argv[1]) == "graphic")
		Monitor::initMLX();
	else if (std::string(argv[1]) == "console")
		Monitor::initNcurses();
	else {
		std::cout << "Plz, not mess around: ./ft_gkrellm [graphic|console]" << std::endl;
		return (-1);
	}

	Monitor::registerModule(new CPUModule());
	Monitor::registerModule(new CPUModule());
	Monitor::registerModule(new TimeModule());
	Monitor::registerModule(new CPUModule());
	Monitor::registerModule(new UserInfoModule());
	Monitor::startMonitoring();

	return 0;
}
