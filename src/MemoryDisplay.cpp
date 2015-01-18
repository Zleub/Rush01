
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

int        MemoryDisplay::getWidth(void) const { return 10; }
int        MemoryDisplay::getHeight(void) const { return 5; }