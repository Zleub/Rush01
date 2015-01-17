
#include <iostream>
#include "Monitor.hpp"
#include "TimeDisplay.hpp"
#include "TimeModule.hpp"

void	TimeDisplay::draw(void * d) const
{
	TimeModule::data_t const *	data =
		static_cast<TimeModule::data_t const *>(d);

	std::cout << data->date << std::endl;
	std::cout << data->time << std::endl;
}