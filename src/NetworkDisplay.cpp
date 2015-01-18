#include <sstream>
#include <iostream>
#include "Monitor.hpp"
#include "NetworkDisplay.hpp"
#include "NetworkModule.hpp"

void	NetworkDisplay::drawMLX(void * d) const
{
	std::stringstream ss;
	NetworkModule::data_t const *	data =
		static_cast<NetworkModule::data_t const *>(d);

	int i = 10;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + i , 0xff0000, (char*)"Network" );
	i += 12;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + i , 0xff0000, (char*)"-------------------------------------------" );
	i += 24;
	ss.str("");
	ss.clear();
	ss << "Network In: " << static_cast<float>(data->in);
	i += 12;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + i , 0xff0000, (char*)ss.str().c_str() );
	ss.str("");
	ss.clear();
	ss << "Network Out: " << static_cast<float>(data->out) ;
	i += 12;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + i , 0xff0000, (char*)ss.str().c_str() );
}


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
