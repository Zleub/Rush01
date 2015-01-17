
#include "Monitor.hpp"
#include "UserInfoDisplay.hpp"
#include "UserInfoModule.hpp"
#include <iostream>
void	UserInfoDisplay::draw(void * d) const
{
	UserInfoModule::data_t const *	data =
		static_cast<UserInfoModule::data_t const *>(d);

	std::cout << data->hostname << std::endl;
}