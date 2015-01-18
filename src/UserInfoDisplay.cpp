#include <sstream>
#include <iostream>
#include "Monitor.hpp"
#include "UserInfoDisplay.hpp"
#include "UserInfoModule.hpp"

void	UserInfoDisplay::drawMLX(void * d) const
{
	std::stringstream ss;
	if (_window == NULL)
		return ;

	UserInfoModule::data_t const *	data =
		static_cast<UserInfoModule::data_t const *>(d);

	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + 32 , 0xff0000, (char*)data->username.c_str() );
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + 44 , 0xff0000, (char*)data->hostname.c_str() );
}


void	UserInfoDisplay::draw(void * d) const
{
	if (_window == NULL)
		return ;

	UserInfoModule::data_t const *	data =
		static_cast<UserInfoModule::data_t const *>(d);

	mvwprintw(_window->window, 1, 13, "User");
	mvwprintw(_window->window, 2, 1, "----------------------------");

	mvwprintw(_window->window, 3, 2, "Username: %s", data->username.c_str());
	mvwprintw(_window->window, 4, 2, "Hostname: %s", data->hostname.c_str());

	box(_window->window, 0, 0);
	wrefresh(_window->window);
}

int        UserInfoDisplay::getWidth(void) const { return 30; }
int        UserInfoDisplay::getHeight(void) const { return 6; }
