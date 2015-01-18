
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <sys/sysctl.h>
#include <sys/utsname.h>
#include "Monitor.hpp"
#include "CPUModule.hpp"
#include "CPUDisplay.hpp"
#include <sys/types.h>
#include <signal.h>

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

std::string executeTop(void)
{
    int     pipefd[2];
    int     pid;

    pipe(pipefd);
    pid = fork();

    if (pid == 0)
    {
        close(pipefd[0]);

        dup2(pipefd[1], 1);
        dup2(pipefd[1], 2);

        close(pipefd[1]);

        execl("/usr/bin/top", "top", "-c", "n", "-l", "0", NULL);
        exit(0);
    }
    else
    {
        char buffer[1024] = { 0 };

        close(pipefd[1]);

        while (read(pipefd[0], buffer, 1023) != 0)
        {
            kill(pid, SIGINT);

            return std::string(buffer);
        }
    }

    return std::string();
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

    std::string top = executeTop();

    _data.processCount = atoi(top.substr(11, 3).c_str());
    _setThreadCount(top);
    _setCPUUsage(top);
    // std::cout << top << std::endl;
    exit(0);
	// _display->draw(&_data);

	static_cast<void>(time);
}

void	CPUModule::reset(void)
{}