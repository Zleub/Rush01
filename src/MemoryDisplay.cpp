
#include <fstream>
#include <sstream>
#include "Monitor.hpp"
#include "MemoryDisplay.hpp"
#include "MemoryModule.hpp"

#define MEM_GRAPH_HEIGHT 8

void	MemoryDisplay::drawMLX(void * d) const
{
	std::stringstream ss;

	MemoryModule::data_t const *	data =
	static_cast<MemoryModule::data_t const *>(d);

	int i = 10;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + i , 0xff0000, (char*)"Memory" );
	i += 12;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + i , 0xff0000, (char*)"-------------------------------------------" );
	i += 24;
	ss.str("");
	ss.clear();
	ss << "MemoryTotal: " << static_cast<float>(data->total * 10);
	i += 12;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + i , 0xff0000, (char*)ss.str().c_str() );
	ss.str("");
	ss.clear();
	ss << "MemoryUsed: " << static_cast<float>(data->used * 10);
	i += 12;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + i , 0xff0000, (char*)ss.str().c_str() );
	ss.str("");
	ss.clear();
	ss << "MemoryFree: " << static_cast<float>(data->free * 10);
	i += 12;
	mlx_string_put (Monitor::getMlx(), Monitor::getWin(), _imageMLX->x, _imageMLX->y + i , 0xff0000, (char*)ss.str().c_str() );
}

void	MemoryDisplay::draw(void * d) const
{
	if (_window->window == NULL)
		return ;

	MemoryModule::data_t const *	data =
		static_cast<MemoryModule::data_t const *>(d);

	mvwprintw(_window->window, 1, 20, "Memory");
	mvwprintw(_window->window, 2, 1, "--------------------------------------------");

	mvwprintw(_window->window, 3, 2, "Total memory: %lu Mhz", data->total / 1000000);
	mvwprintw(_window->window, 4, 2, "Used memory: %lu Mhz", data->used / 1000000);
	mvwprintw(_window->window, 5, 2, "Free memory: %lu Mhz", data->free / 1000000);

	{
		unsigned int	value = 42 * data->used / data->total;

		for (unsigned int i = 0; i < 42; i++)
		{
			if (i < value)
				mvwprintw(_window->window, 7, 2 + i, "#");
			else
				mvwprintw(_window->window, 7, 2 + i, " ");
		}
	}

	mvwprintw(_window->window, 8, 2, "------------------------------------------");

	{
		unsigned int	width = static_cast<unsigned int>(getWidth()) - 4;

		for (unsigned int x = 0; x < width; x++)
		{
			if (x >= data->history.size())
				continue;

			unsigned int	value = MEM_GRAPH_HEIGHT * data->history[x] / data->total;

			for (unsigned int i = 0; i < MEM_GRAPH_HEIGHT; i++)
			{
				if (i < value)
					mvwprintw(_window->window, 9 + MEM_GRAPH_HEIGHT - i, 1 + width - x, "#");
				else
					mvwprintw(_window->window, 9 + MEM_GRAPH_HEIGHT - i, 1 + width - x, " ");
			}
		}
	}

	box(_window->window, 0, 0);
	wrefresh(_window->window);
}

int        MemoryDisplay::getWidth(void) const { return 46; }
int        MemoryDisplay::getHeight(void) const { return 18; }
