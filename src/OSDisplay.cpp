
#include <iostream>
#include "Monitor.hpp"
#include "OSDisplay.hpp"
#include "OSModule.hpp"

void	OSDisplay::draw(void * d) const
{
	if (_window == NULL)
		return ;

	OSModule::data_t const *	data =
		static_cast<OSModule::data_t const *>(d);

	mvwprintw(_window->window, 1, 15, "Operating System");
	mvwprintw(_window->window, 2, 1, "--------------------------------------------");

	mvwprintw(_window->window, 3, 2, "Name: %s", data->os.c_str());
	mvwprintw(_window->window, 4, 2, "Release: %s", data->release.c_str());
	mvwprintw(_window->window, 5, 2, "Version: %s", data->version.substr(0, getWidth() - 13).c_str());
	mvwprintw(_window->window, 6, 2, "Machine: %s", data->machine.c_str());

	box(_window->window, 0, 0);
	wrefresh(_window->window);
}

int        OSDisplay::getWidth(void) const { return 46; }
int        OSDisplay::getHeight(void) const { return 8; }
