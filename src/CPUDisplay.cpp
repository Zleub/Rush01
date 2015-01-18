#include <iostream>
#include <string>
#include <sstream>

#include "Monitor.hpp"
#include "CPUDisplay.hpp"
#include "CPUModule.hpp"

#include <ncurses.h>

#define CPU_BAR_WIDTH 27

void	CPUDisplay::draw(void * d) const
{
	if (_window == NULL)
		return ;
	wclear(_window->window);
	CPUModule::data_t const *	data =
	static_cast<CPUModule::data_t const *>(d);

	mvwprintw(_window->window, 1, 21, "CPU");
	mvwprintw(_window->window, 2, 1, "-------------------------------------------");

	mvwprintw(_window->window, 4, 2, "%s", data->name.c_str());
	mvwprintw(_window->window, 6, 2, "Number of cores: %d", data->coreCount);
	mvwprintw(_window->window, 8, 2, "CPU frequency: %.2f GHz", data->frequency);
	mvwprintw(_window->window, 7, 2, "Number of processes: %lu", data->processCount);
	mvwprintw(_window->window, 9, 2, "Number of threads: %lu", data->threadCount);

	{
		mvwprintw(_window->window, 11, 2, "User");
		mvwprintw(_window->window, 11, 37, "%5.2f%%", data->userUsage);

		unsigned int	value = CPU_BAR_WIDTH * data->userUsage / 100;

		for (unsigned int i = 0; i < value; i++)
			mvwprintw(_window->window, 11, 9 + i, "|");
	}

	{
		mvwprintw(_window->window, 12, 2, "System");
		mvwprintw(_window->window, 12, 37, "%5.2f%%", data->systemUsage);

		unsigned int	value = CPU_BAR_WIDTH * data->systemUsage / 100;

		for (unsigned int i = 0; i < value; i++)
			mvwprintw(_window->window, 12, 9 + i, "|");
	}

	{
		mvwprintw(_window->window, 13, 2, "Idle");
		mvwprintw(_window->window, 13, 37, "%5.2f%%", data->idle);

		unsigned int	value = CPU_BAR_WIDTH * data->idle / 100;

		for (unsigned int i = 0; i < value; i++)
			mvwprintw(_window->window, 13, 9 + i, "|");
	}

	box(_window->window, 0, 0);
	wrefresh(_window->window);

	(void) data;
}

int        CPUDisplay::getWidth(void) const { return 45; }
int        CPUDisplay::getHeight(void) const { return 15; }
