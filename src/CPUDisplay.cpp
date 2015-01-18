#include <iostream>
#include <string>
#include <sstream>

#include "Monitor.hpp"
#include "CPUDisplay.hpp"
#include "CPUModule.hpp"

#include <ncurses.h>

void	CPUDisplay::drawMLX(void * d) const {
	std::stringstream ss;

	CPUModule::data_t const *	data =
	static_cast<CPUModule::data_t const *>(d);

	(void)data;

	// drawRectangle(_imageMLX->x, _imageMLX->y, 50, 50);

	// mlx_put_image_to_window(Monitor::getMlx(), Monitor::getWin(), _imageMLX->image, _imageMLX->x, _imageMLX->y);
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + 10 , 0xff0000, (char*)data->name.c_str() );
	ss.str("");
	ss.clear();
	ss << data->coreCount;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + 32 , 0xff0000, (char*)ss.str().c_str() );
	ss.str("");
	ss.clear();
	ss << data->frequency;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + 44 , 0xff0000, (char*)ss.str().c_str() );
	ss.str("");
	ss.clear();
	ss << data->processCount;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + 56 , 0xff0000, (char*)ss.str().c_str() );
	ss.str("");
	ss.clear();
	ss << data->threadCount;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + 68 , 0xff0000, (char*)ss.str().c_str() );
	ss.str("");
	ss.clear();
	ss << data->userUsage;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + 80 , 0xff0000, (char*)ss.str().c_str() );
	ss.str("");
	ss.clear();
	ss << data->systemUsage;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + 92 , 0xff0000, (char*)ss.str().c_str() );
	ss.str("");
	ss.clear();
	ss << data->idle;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + 104 , 0xff0000, (char*)ss.str().c_str() );
	ss.str("");
}

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
	int userpercent = getWidth() * data->userUsage / 100;
	init_pair(1, COLOR_RED, COLOR_BLACK);
	wattrset(_window->window, COLOR_PAIR(1));
	for(int j = 0; j < userpercent; j++) {
		mvwprintw(_window->window, getHeight() - 2, i + j, "|");
	}
	wattroff(_window->window, COLOR_PAIR(1));

	i += userpercent;

	int systempercent = getWidth() * data->systemUsage / 100;
	init_pair(2, 202, COLOR_BLACK);
	wattrset(_window->window, COLOR_PAIR(2));
	for(int j = 0; j < systempercent; j++) {
		mvwprintw(_window->window, getHeight() - 2, i + j, "|");
	}
	wattroff(_window->window, COLOR_PAIR(2));

	i += systempercent;

	int idlepercent = getWidth() * data->idle / 100;
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	wattrset(_window->window, COLOR_PAIR(3));
	for(int j = 0; j < idlepercent; j++) {
		mvwprintw(_window->window, getHeight() - 2, i + j, "|");
	}
	wattroff(_window->window, COLOR_PAIR(3));


	box(_window->window, 0, 0);
	wrefresh(_window->window);

	(void) data;
}

int        CPUDisplay::getWidth(void) const { return 20; }
int        CPUDisplay::getHeight(void) const { return 15; }
