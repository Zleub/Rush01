
#include <sys/utsname.h>
#include "Monitor.hpp"
#include "OSModule.hpp"
#include "OSDisplay.hpp"
#include <iostream>

OSModule::OSModule(void) :
	AMonitorModule(new OSDisplay)
{}

void	OSModule::update(unsigned long time)
{
    struct utsname  d;

    uname(&d);

    _data.os = std::string(d.sysname);
    _data.release = std::string(d.release);
    _data.version = std::string(d.version);
    _data.machine = std::string(d.machine);

    _display->draw(&_data);

	static_cast<void>(time);
}

void	OSModule::reset(void)
{}