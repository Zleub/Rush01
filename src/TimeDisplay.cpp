
#include <iostream>
#include "Monitor.hpp"
#include "TimeDisplay.hpp"
#include "TimeModule.hpp"

void	TimeDisplay::draw(void * d) const
{
	TimeModule::data_t const *	data =
		static_cast<TimeModule::data_t const *>(d);
		
	mvwprintw(_window->window, 1, 5, "Time");
	mvwprintw(_window->window, 2, 1, "------------");

	mvwprintw(_window->window, 3, 2, "%s", data->date.c_str());
	mvwprintw(_window->window, 4, 2, " %s", data->time.c_str());
	
	box(_window->window, 0, 0);
	wrefresh(_window->window);
}

int        TimeDisplay::getWidth(void) const { return 14; }
int        TimeDisplay::getHeight(void) const { return 6; }
