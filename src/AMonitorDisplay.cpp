
#include "AMonitorDisplay.hpp"

AMonitorDisplay::AMonitorDisplay(IMonitorModule * module) :
	_module(module)
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