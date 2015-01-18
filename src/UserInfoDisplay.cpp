
#include <iostream>
#include "Monitor.hpp"
#include "UserInfoDisplay.hpp"
#include "UserInfoModule.hpp"

void	UserInfoDisplay::draw(void * d) const
{
	UserInfoModule::data_t const *	data =
		static_cast<UserInfoModule::data_t const *>(d);

	std::cout << data->hostname << std::endl;
	std::cout << data->username << std::endl;
}

int        UserInfoDisplay::getWidth(void) const { return 10; }
int        UserInfoDisplay::getHeight(void) const { return 5; }