
#include <iostream>
#include "Monitor.hpp"
#include "MemoryDisplay.hpp"
#include "MemoryModule.hpp"

void	MemoryDisplay::draw(void * d) const
{
	MemoryModule::data_t const *	data =
		static_cast<MemoryModule::data_t const *>(d);

	(void) data;
}