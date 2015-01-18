#include <iostream>
#include "Monitor.hpp"
#include "OSModule.hpp"
#include <IOKit/IOKitLib.h>

int		main(void)
{
	Monitor::registerModule(new OSModule());

	Monitor::initNcurses();
	Monitor::startMonitoring();

	return 0;
}
