#include "AMonitorDisplay.hpp"
#include "Monitor.hpp"
#include <iostream>

int		AMonitorDisplay::_nbrDisplay = 0;

AMonitorDisplay::AMonitorDisplay(IMonitorModule * module) :
_module(module),
_window(NULL),
_imageMLX(NULL)
{}

AMonitorDisplay::AMonitorDisplay(AMonitorDisplay const & src)
{
	static_cast<void>(src);
}

AMonitorDisplay::~AMonitorDisplay(void)
{}

AMonitorDisplay &	AMonitorDisplay::operator=(AMonitorDisplay const & rhs)
{
	static_cast<void>(rhs);

	return *this;
}

void				AMonitorDisplay::setImage(image_t * window)
{
	_imageMLX = window;
}

void				AMonitorDisplay::setWindow(window_t * window)
{
	_window = window;
}

window_t *			AMonitorDisplay::getWindow(void) const
{
	return _window;
}

image_t *			AMonitorDisplay::getImage(void) const
{
	return _imageMLX;
}

void		AMonitorDisplay::draw(void *) const
{}

void		AMonitorDisplay::drawMLX(void *) const
{}

void		AMonitorDisplay::drawRectangle(int off_x, int off_y, int width, int height) const
{
	int x = off_x;
	int y = off_y;

	while (y <= off_y + height)
	{
		x = off_x;
		while(x <= off_x + width)
		{
			mlx_pixel_put(Monitor::getMlx(), Monitor::getWin(), x, y, 0x00ff00);
			x++;
		}
		y++;
	}
}

int        AMonitorDisplay::getWidth(void) const { return 10; }
int        AMonitorDisplay::getHeight(void) const { return 5; }
