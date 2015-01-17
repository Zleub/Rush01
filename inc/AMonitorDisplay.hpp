
#ifndef AMONITOR_DISPLAY_HPP
# define AMONITOR_DISPLAY_HPP

# include "IMonitorDisplay.hpp"
# include "IMonitormodule.hpp"

class AMonitorDisplay : public IMonitorDisplay
{
protected:
	IMonitorModule *	_module;

public:
	AMonitorDisplay(IMonitorModule * = NULL);
	AMonitorDisplay(AMonitorDisplay const &);
	virtual ~AMonitorDisplay(void);

	AMonitorDisplay &	operator=(AMonitorDisplay const &);
};

#endif