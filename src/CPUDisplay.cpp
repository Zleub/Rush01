#include <iostream>
#include <string>
#include <sstream>

#include "Monitor.hpp"
#include "CPUDisplay.hpp"
#include "CPUModule.hpp"

void	CPUDisplay::draw(void * d) const
{
	CPUModule::data_t const *	data =
	static_cast<CPUModule::data_t const *>(d);

	std::string Result;

	std::ostringstream convert;
	convert << data->coreCount;
}
