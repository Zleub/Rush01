
#include <sys/utsname.h>
#include "Monitor.hpp"
#include "OSModule.hpp"
#include "OSDisplay.hpp"
#include <iostream>

OSModule::OSModule(void) :
	AMonitorModule(new OSDisplay)
{}

void	OSModule::update(unsigned long time, std::string drawtype)
{
    struct utsname  d;

    uname(&d);

    _data.os = std::string(d.sysname);
    _data.release = std::string(d.release);
    _data.version = std::string(d.version);
    _data.machine = std::string(d.machine);

    if (drawtype == "console")
    	_display->draw(&_data);
    else if (drawtype == "graphic")
        _display->drawMLX(&_data);

	static_cast<void>(time);
}

void	OSModule::reset(void)
{}
