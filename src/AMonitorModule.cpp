
#include "AMonitorModule.hpp"
#include <iostream>

AMonitorModule::AMonitorModule(IMonitorDisplay * display) :
	_paused(false),
	_display(display)
{}

AMonitorModule::AMonitorModule(AMonitorModule const & src) :
	_paused(src._paused),
	_display(src._display)
{}

AMonitorModule::~AMonitorModule(void)
{}

AMonitorModule &	AMonitorModule::operator=(AMonitorModule const & rhs)
{
	if (this == &rhs)
		return *this;

	_paused = rhs._paused;
	_display = rhs._display;

	return *this;
}

void				AMonitorModule::start(void)
{
	_paused = false;
}

void				AMonitorModule::pause(void)
{
	_paused = true;
}