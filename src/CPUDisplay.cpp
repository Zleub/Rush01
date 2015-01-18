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

	CPUModule::data_t const *	data =
	static_cast<CPUModule::data_t const *>(d);

	box(_window->window, 0, 0);
	wrefresh(_window->window);

	(void) data;
}

int        CPUDisplay::getWidth(void) const { return 10; }
int        CPUDisplay::getHeight(void) const { return 5; }