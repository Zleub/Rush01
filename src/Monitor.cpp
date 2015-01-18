
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <fstream>

#include "Monitor.hpp"
#include "AMonitorDisplay.hpp"

#include "CPUModule.hpp"
#include "MemoryModule.hpp"
#include "OSModule.hpp"
#include "TimeModule.hpp"
#include "UserInfoModule.hpp"
#include "NetworkModule.hpp"

unsigned long	Monitor::_updateInterval = 500000;
unsigned long	Monitor::_lastUpdate = Monitor::getTime();
std::vector<AMonitorModule*>	Monitor::_modules;

static module_e	getModuleType(AMonitorModule * module)
{
	AMonitorModule *	ptr;

	if ((ptr = dynamic_cast<CPUModule *>(module)) != NULL)
		return CPU;
	else if ((ptr = dynamic_cast<MemoryModule *>(module)) != NULL)
		return Memory;
	else if ((ptr = dynamic_cast<OSModule *>(module)) != NULL)
		return OS;
	else if ((ptr = dynamic_cast<TimeModule *>(module)) != NULL)
		return Time;
	else if ((ptr = dynamic_cast<UserInfoModule *>(module)) != NULL)
		return UserInfo;
	else if ((ptr = dynamic_cast<NetworkModule *>(module)) != NULL)
		return Network;

	return Unknown;
}

static void		handleInputNcurses(void)
{
	char		ch;

	nodelay(stdscr, TRUE);
	ch = getch();

	switch (ch) {
		case 27: // Escape
			endwin();
			exit(0);

		case 'q':
			Monitor::registerModule(new CPUModule);
			break ;
		case 'a':
			Monitor::unregisterModule(CPU);
			break ;

		case 'w':
			Monitor::registerModule(new MemoryModule);
			break ;
		case 's':
			Monitor::unregisterModule(Memory);
			break ;

		case 'e':
			Monitor::registerModule(new OSModule);
			break ;
		case 'd':
			Monitor::unregisterModule(OS);
			break ;

		case 'r':
			Monitor::registerModule(new TimeModule);
			break ;
		case 'f':
			Monitor::unregisterModule(Time);
			break ;

		case 't':
			Monitor::registerModule(new UserInfoModule);
			break ;
		case 'g':
			Monitor::unregisterModule(UserInfo);
			break ;

		case 'y':
			Monitor::registerModule(new NetworkModule);
			break ;
		case 'h':
			Monitor::unregisterModule(Network);
			break ;
	}
	
	flushinp();
}

void			Monitor::initNcurses(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
	curs_set(0);
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

void			Monitor::unregisterModule(module_e module)
{
	moduleIterator_t	it = _modules.begin();

	for (; it < _modules.end(); it++)
	{
		if (getModuleType(*it) == module)
		{
			_modules.erase(it);
			createWindows();

			return ;
		}
	}
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

	clear();

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
			mvwin(window->window, window->y, window->x);

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

		handleInputNcurses();

		if (time - _lastUpdate > _updateInterval)
		{
			it = _modules.begin();
			_lastUpdate = getTime();

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
