#include <iostream>
#include "Monitor.hpp"
#include "UserInfoModule.hpp"

int		main(void)
{
	Monitor::registerModule(new UserInfoModule());

	Monitor::startMonitoring();

	return 0;
}
