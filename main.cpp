#include <iostream>
#include "Monitor.hpp"
#include "CPUModule.hpp"
#include "TimeModule.hpp"
#include "UserInfoModule.hpp"
#include "OSModule.hpp"
#include "MemoryModule.hpp"

int		main(void)
{
	Monitor::initNcurses();

	Monitor::registerModule(new CPUModule());
	Monitor::registerModule(new OSModule());
	Monitor::registerModule(new MemoryModule());
	Monitor::registerModule(new UserInfoModule());
	Monitor::registerModule(new TimeModule());

	Monitor::startMonitoring();

	return 0;
}
