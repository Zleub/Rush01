
#include <iostream>
#include "Monitor.hpp"
#include "TimeDisplay.hpp"
#include "TimeModule.hpp"

void	TimeDisplay::draw(void * d) const
{
	TimeModule::data_t const *	data =
		static_cast<TimeModule::data_t const *>(d);
		
	box(_window->window, 0, 0);
	wrefresh(_window->window);

	(void) data;
}

int        TimeDisplay::getWidth(void) const { return 10; }
int        TimeDisplay::getHeight(void) const { return 5; }