
#include <iostream>
#include <unistd.h>
#include "Monitor.hpp"

unsigned long	Monitor::_updateInterval = 1000000;
unsigned long	Monitor::_lastUpdate = Monitor::getTime();
std::vector<IMonitorModule*>	Monitor::_modules;

SDL_Window *	Monitor::_window = NULL;
SDL_Surface *	Monitor::_screenSurface = NULL;

void			Monitor::initSDL(void)
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError();
	}
	else {
		_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 250, 250, SDL_WINDOW_SHOWN );
		if( _window == NULL ) {
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError();
		}
		else {
			_screenSurface = SDL_GetWindowSurface( _window );
			SDL_FillRect( _screenSurface, NULL, SDL_MapRGB( _screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			SDL_StartTextInput();
			// SDL_UpdateWindowSurface( _window );
			// SDL_Delay( 2000 );
		}
	}
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
	moduleIterator_t	it = _modules.begin();
	struct timeval		time;

	log("", false);
	log("Updating modules");

	for (; it != _modules.end(); it++)
		(*it)->update(_lastUpdate);

	gettimeofday(&time, NULL);

	usleep(_updateInterval - (getTime() - _lastUpdate));

	gettimeofday(&time, NULL);
	_lastUpdate = getTime();

	// if (SDL_PollEvent( &e ) != 0 )
		// SDL_UpdateWindowSurface( _window );
	update();
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
