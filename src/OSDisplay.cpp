
#include <iostream>
#include "Monitor.hpp"
#include "OSDisplay.hpp"
#include "OSModule.hpp"

void	OSDisplay::draw(void * d) const
{
	if (_window == NULL)
		return ;

	OSModule::data_t const *	data =
		static_cast<OSModule::data_t const *>(d);

	mvwprintw(_window->window, 1, 1, "%s", data->os.c_str());

	(void) data;
}
