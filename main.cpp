#include <iostream>
#include "Monitor.hpp"
#include "CPUModule.hpp"
#include "UserInfoModule.hpp"

int		main(void)
{
	Monitor::initNcurses();

	Monitor::registerModule(new CPUModule());
	// Monitor::registerModule(new UserInfoModule());
	Monitor::startMonitoring();

	return 0;
}
