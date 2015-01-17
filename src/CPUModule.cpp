
#include <unistd.h>
#include <iostream>
#include <cmath>
#include "Monitor.hpp"
#include "CPUModule.hpp"
#include "CPUDisplay.hpp"

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

void	CPUModule::update(unsigned long time)
{
    _data.coreCount = sysconf(_SC_NPROCESSORS_ONLN);

	_display->draw(&_data);

	static_cast<void>(time);
}

void	CPUModule::reset(void)
{}