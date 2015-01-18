
#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include "Monitor.hpp"
#include "AMonitorDisplay.hpp"

unsigned long	Monitor::_updateInterval = 1000000;
unsigned long	Monitor::_lastUpdate = Monitor::getTime();
std::vector<AMonitorModule*>	Monitor::_modules;

void			Monitor::initNcurses(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
}


void			Monitor::registerModule(AMonitorModule * module)
{
	if (module == NULL)
		return ;

	window_t *	window = new window_t;

	window->window = NULL;
	_modules.push_back(module);

	module->getDisplay()->setWindow(window);

	createWindows();
}

void			Monitor::startMonitoring(void)
{
	_lastUpdate = getTime();
	update();
}

void			Monitor::createWindows(void)
{
	moduleIterator_t	it = _modules.begin();
	AMonitorDisplay *	display;
	window_t *			window;
	int					x = 0;
	int					y = 0;
	int					maxY = 0;

	std::cout << "--------\n" << std::endl;

	for (; it < _modules.end(); it++)
	{
		display = (*it)->getDisplay();

		if (static_cast<int>(x + display->getWidth()) > COLS)
		{
			x = 0;
			y += maxY;
			maxY = 0;
		}
		
		window = display->getWindow();
		window->x = x;
		window->y = y;
		maxY = std::max(maxY, display->getHeight());

		if (window->window == NULL)
		{
			window->window = newwin(
				display->getHeight(),
				display->getWidth(),
				window->y,
				window->x
			);
		}
		else
		{
			mvwin(window->window, window->x, window->y);
		}

		x += display->getWidth();
	}
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
			// log("Updating modules");

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

std::vector<AMonitorModule*> &	Monitor::getModules(void)
{
	return _modules;
}
