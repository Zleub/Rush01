
#include <iostream>
#include <unistd.h>

#include "Monitor.hpp"

unsigned long	Monitor::_updateInterval = 1000000;
unsigned long	Monitor::_lastUpdate = Monitor::getTime();
std::vector<IMonitorModule*>	Monitor::_modules;

void *			Monitor::_mlx = NULL;

void			Monitor::initMLX(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
}

void			Monitor::registerModule(IMonitorModule * module)
{
	_modules.push_back(module);
}

void			Monitor::startMonitoring(void)
{
	_lastUpdate = getTime();
	update();
}

void			Monitor::update(void)
{
	moduleIterator_t	it;
	unsigned long 		time;

	while (true)
	{
		time = getTime();

		if (time - _lastUpdate > _updateInterval)
		{
			it = _modules.begin();
			_lastUpdate = getTime();
			log("Updating modules");

			for (; it != _modules.end(); it++)
				(*it)->update(_lastUpdate);
		}
	}
}

void			Monitor::reset(void)
{
	moduleIterator_t	it = _modules.begin();

	for (; it != _modules.end(); it++)
		(*it)->reset();
}

void			Monitor::start(void)
{
	moduleIterator_t	it = _modules.begin();

	for (; it != _modules.end(); it++)
		(*it)->start();
}

void			Monitor::pause(void)
{
	moduleIterator_t	it = _modules.begin();

	for (; it != _modules.end(); it++)
		(*it)->pause();
}

void			Monitor::log(std::string message, bool showTime)
{
	if (showTime)
	{
		unsigned long	time = getTime();

		std::cout
			<< "[" << (time / 1000000)
			<< "." << (time % 1000000)
			<< "] "
		;
	}

	std::cout
		<< message
		<< std::endl
	;
}

unsigned long	Monitor::getTime(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return time.tv_sec * 1000000 + time.tv_usec;
}

void		Monitor::setUpdateInterval(double interval)
{
	_updateInterval = interval;
}

double		Monitor::getUpdateInterval(void)
{
	return _updateInterval;
}

std::vector<IMonitorModule*> &	Monitor::getModules(void)
{
	return _modules;
}
