
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

int        OSDisplay::getWidth(void) const { return 10; }
int        OSDisplay::getHeight(void) const { return 5; }