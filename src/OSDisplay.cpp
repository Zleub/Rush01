
#include <iostream>
#include "Monitor.hpp"
#include "OSDisplay.hpp"
#include "OSModule.hpp"

void	OSDisplay::draw(void * d) const
{
	OSModule::data_t const *	data =
		static_cast<OSModule::data_t const *>(d);

		(void) data;
}