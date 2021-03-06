
#include <unistd.h>
#include <cmath>
#include <sys/sysctl.h>
#include <cstdlib>
#include "Monitor.hpp"
#include "CPUModule.hpp"
#include "CPUDisplay.hpp"
#include "Util.hpp"

CPUModule::CPUModule(void) :
	AMonitorModule(new CPUDisplay)
{
    char *  args[4] = {
        (char *) "sysctl",
        (char *) "-n",
        (char *) "machdep.cpu.brand_string",
        NULL
    };

    _data.name = std::string(Util::execute("/usr/sbin/sysctl", args, 100));
}

double     CPUModule::_getCPUFrequency(void)
{
    int     freq;
    size_t  size = sizeof(freq);
    int     mib[2] = { CTL_HW, HW_CPU_FREQ };

    sysctl(mib, 2, &freq, &size, NULL, 0);

    return roundf(static_cast<float>(freq) / 10000000) / 100;
}

void    CPUModule::_setThreadCount(std::string const & top)
{
    size_t  occ = top.find(" threads");

    if (occ == std::string::npos)
        return ;

    while (top[--occ] != ' ');

    _data.threadCount = atoi(top.substr(occ, 5).c_str());
}

void    CPUModule::_setCPUUsage(std::string const & top)
{
    size_t      occ;
    std::string line;

    occ = top.find("CPU usage:");

    if (top.size() > occ)
        line = top.substr(occ, 50);
    else
        return ;

    if (line.size() > 11)
        _data.userUsage = atof(line.substr(11, 5).c_str());
    else
        _data.userUsage = 0;


    occ = line.find("user") + 6;

    if (line.size() > occ)
        _data.systemUsage = atof(line.substr(occ, 5).c_str());
    else
        _data.systemUsage = 0;


    occ = line.find("sys") + 5;

    if (line.size() > occ)
        _data.idle = atof(line.substr(occ, 5).c_str());
    else
        _data.idle = 0;
}

void	CPUModule::update(unsigned long time, std::string drawtype)
{
    _data.coreCount = sysconf(_SC_NPROCESSORS_ONLN);
    _data.frequency = _getCPUFrequency();

    char *  args[6] = {
        (char *) "top",
        (char *) "-c",
        (char *) "n",
        (char *) "-l",
        (char *) "0",
        NULL
    };

    std::string top = Util::execute("/usr/bin/top", args, 500);

    if (top.size() > 11)
        _data.processCount = atoi(top.substr(11, 3).c_str());
    else
        _data.processCount = 0;
    
    _setThreadCount(top);
    _setCPUUsage(top);

    if (drawtype == "console")
    	_display->draw(&_data);
    else if (drawtype == "graphic")
        _display->drawMLX(&_data);

	static_cast<void>(time);
}

void	CPUModule::reset(void)
{}
