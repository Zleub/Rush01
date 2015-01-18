#include <iostream>
#include <string>
#include <sstream>

#include "Monitor.hpp"
#include "CPUDisplay.hpp"
#include "CPUModule.hpp"

#include <ncurses.h>

void	CPUDisplay::draw(void * d) const
{
	if (_window == NULL)
		return ;
	wclear(_window->window);
	CPUModule::data_t const *	data =
	static_cast<CPUModule::data_t const *>(d);

	mvwprintw(_window->window, 1, 1, "%s", data->name.c_str());
	mvwprintw(_window->window, 2, 1, "coreCount: %d", data->coreCount);
	mvwprintw(_window->window, 3, 1, "frequency: %f", data->frequency);
	mvwprintw(_window->window, 4, 1, "processCount: %lu", data->processCount);
	mvwprintw(_window->window, 5, 1, "threadCount: %lu", data->threadCount);
	mvwprintw(_window->window, 6, 1, "userUsage: %.2f", data->userUsage);
	mvwprintw(_window->window, 7, 1, "systemUsage: %.2f", data->systemUsage);
	mvwprintw(_window->window, 8, 1, "idle: %.2f", data->idle);


	int i = 1;
	int userpercent = _window->width * data->userUsage / 100;
	init_pair(1, COLOR_RED, COLOR_BLACK);
	wattrset(_window->window, COLOR_PAIR(1));
	for(int j = 0; j < userpercent; j++) {
		mvwprintw(_window->window, 9, i + j, "#");
	}
	wattroff(_window->window, COLOR_PAIR(1));

	i += userpercent;

	int systempercent = _window->width * data->systemUsage / 100;
	init_pair(2, 202, COLOR_BLACK);
	wattrset(_window->window, COLOR_PAIR(2));
	for(int j = 0; j < systempercent; j++) {
		mvwprintw(_window->window, 9, i + j, "#");
	}
	wattroff(_window->window, COLOR_PAIR(2));

	mvwprintw(_window->window, 14, 1, "%d", userpercent);
	mvwprintw(_window->window, 15, 1, "%f", _window->width * data->userUsage / 100);
	mvwprintw(_window->window, 16, 1, "%f", _window->width * data->idle / 100);
	box(_window->window, 0, 0);
	wrefresh(_window->window);

	(void) data;
}
