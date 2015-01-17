#include <iostream>
#include <Monitor.hpp>
#include "TimeModule.hpp"

int		main(void)
{
	Monitor::registerModule(new TimeModule());

	Monitor::startMonitoring();

	return 0;
}
