
#include <ctime>
#include <sstream>
#include "Monitor.hpp"
#include "TimeModule.hpp"
#include "TimeDisplay.hpp"

TimeModule::TimeModule(void) :
	AMonitorModule(new TimeDisplay)
{}

void	TimeModule::update(unsigned long time, std::string drawtype)
{
	time_t		now = std::time(0);
    struct tm	tstruct;
    char		buf[80];

    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    _data.date  = buf;

    strftime(buf, sizeof(buf), "%X", &tstruct);
    _data.time  = buf;

    if (drawtype == "console")
        _display->draw(&_data);
    else if (drawtype == "graphic")
        _display->drawMLX(&_data);

	static_cast<void>(time);
}

void	TimeModule::reset(void)
{}
