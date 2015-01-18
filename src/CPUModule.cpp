
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
{}

double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

double get_cpu_time(){
    return (double)clock() / CLOCKS_PER_SEC;
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

    while (top[--occ] != ' ');

    _data.threadCount = atoi(top.substr(occ, 5).c_str());
}

void    CPUModule::_setCPUUsage(std::string const & top)
{
    std::string     line = top.substr(top.find("CPU usage:"), 50);

    _data.userUsage = atof(line.substr(11, 5).c_str());
    _data.systemUsage = atof(line.substr(line.find("user") + 6, 5).c_str());
    _data.idle = atof(line.substr(line.find("sys") + 5, 5).c_str());
}

void	CPUModule::update(unsigned long time)
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

    std::string top = Util::execute("/usr/bin/top", args, 1024);

    _data.processCount = atoi(top.substr(11, 3).c_str());
    _setThreadCount(top);
    _setCPUUsage(top);

	_display->draw(&_data);

	static_cast<void>(time);
}

void	CPUModule::reset(void)
{}
