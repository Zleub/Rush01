#include "AMonitorDisplay.hpp"

int		AMonitorDisplay::_nbrDisplay = 0;

AMonitorDisplay::AMonitorDisplay(IMonitorModule * module) :
	_module(module),
	_window(NULL)
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

void				AMonitorDisplay::setWindow(window_t * window)
{
	_window = window;
}

window_t *			AMonitorDisplay::getWindow(void)
{
	return _window;
}

void		AMonitorDisplay::draw(void *) const
{}
