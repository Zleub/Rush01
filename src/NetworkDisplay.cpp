
#include <iostream>
#include "Monitor.hpp"
#include "NetworkDisplay.hpp"
#include "NetworkModule.hpp"

void	NetworkDisplay::draw(void * d) const
{
	NetworkModule::data_t const *	data =
		static_cast<NetworkModule::data_t const *>(d);
		
	mvwprintw(_window->window, 1, 7, "Network");
	mvwprintw(_window->window, 2, 1, "-------------------");

	mvwprintw(_window->window, 3, 2, "In: %lu o/s", data->in);
	mvwprintw(_window->window, 4, 2, "Out: %lu o/s", data->out);
	
	box(_window->window, 0, 0);
	wrefresh(_window->window);
}

int        NetworkDisplay::getWidth(void) const { return 21; }
int        NetworkDisplay::getHeight(void) const { return 6; }
