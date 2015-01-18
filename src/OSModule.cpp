
#include <ctime>
#include <sstream>
#include "Monitor.hpp"
#include "OSModule.hpp"
#include "OSDisplay.hpp"

OSModule::OSModule(void) :
	AMonitorModule(new OSDisplay)
{}

void	OSModule::update(unsigned long time)
{
	static_cast<void>(time);
}

void	OSModule::reset(void)
{}