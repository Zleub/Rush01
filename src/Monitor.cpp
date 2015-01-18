
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

void *		Monitor::_mlx = NULL;
void *		Monitor::_win = NULL;
std::string	Monitor::_type;
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
	_type = "console";
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
	curs_set(0);
}

void			Monitor::initMLX(void) {
	_type = "graphic";
	_mlx = mlx_init();
	_win = mlx_new_window(_mlx, 1280, 800, (char*)"ft_gkrellm");
}

void			Monitor::registerModule(AMonitorModule * module)
{
	if (module == NULL)
		return ;

	window_t *	window = new window_t;
	window->window = NULL;

	image_t *	imageMLX = new image_t;
	imageMLX->image = NULL;

	_modules.push_back(module);
	module->getDisplay()->setWindow(window);
	module->getDisplay()->setImage(imageMLX);

	if (_type == "console")
		createWindows();
	else if (_type == "graphic")
		createImages();
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
	if (_type == "console")
		update();
	else if (_type == "graphic")
		updateMLX();
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

void			Monitor::createImages(void)
{
	moduleIterator_t	it = _modules.begin();
	AMonitorDisplay *	display;
	image_t *			image;
	int					x = 0;
	int					y = 0;
	int					maxY = 0;

	for (; it < _modules.end(); it++)
	{
		display = (*it)->getDisplay();

		if (static_cast<int>(x + display->getWidth() * 10) > 640)
		{
			x = 0;
			y += maxY;
			maxY = 0;
		}

		image = display->getImage();
		image->x = x;
		image->y = y;
		maxY = std::max(maxY, display->getHeight() * 12);

		if (image->image == NULL)
		{
			image->image = mlx_new_image(_mlx, display->getWidth() * 10, display->getHeight() * 12);

		}
		else
		{
			// mvwin(image->image, image->x, image->y);
			;
		}

		x += display->getWidth() * 10;
	}
}

int				Monitor::drawMLX(void) {
	moduleIterator_t	it;
	unsigned long 		time;

	time = getTime();

	if (time - _lastUpdate > _updateInterval)
	{
		it = _modules.begin();
		_lastUpdate = getTime();
		// log("Updating modules");

		mlx_clear_window (_mlx, _win);
		for (; it != _modules.end(); it++)
			(*it)->update(_lastUpdate, "graphic");
	}
	return 0;
}

static int		handleInputMLX(int keycode, void*)
{
	switch (keycode) {
		case 65307: // Escape
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

	return 0;
}

void			Monitor::updateMLX(void) {
	mlx_loop_hook(_mlx, drawMLX, NULL);
	mlx_expose_hook (_win, drawMLX, NULL);
	mlx_key_hook (_win, handleInputMLX, NULL);
	mlx_loop(_mlx);
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
				(*it)->update(_lastUpdate, "console");
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

void *		Monitor::getMlx(void) {
	return _mlx;
}
void *		Monitor::getWin(void) {
	return _win;
}

std::string		Monitor::getType(void) {
	return _type;
}
