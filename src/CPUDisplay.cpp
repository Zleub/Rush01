
#include <iostream>
#include "Monitor.hpp"
#include "CPUDisplay.hpp"
#include "CPUModule.hpp"

void	CPUDisplay::draw(void * d) const
{
	CPUModule::data_t const *	data =
		static_cast<CPUModule::data_t const *>(d);

	std::cout << data->coreCount << std::endl;
}