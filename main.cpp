#include <iostream>
#include "Monitor.hpp"
#include "CPUModule.hpp"

int		main(void)
{
	Monitor::registerModule(new CPUModule());

	Monitor::initNcurses();
	Monitor::startMonitoring();

	return 0;
}
