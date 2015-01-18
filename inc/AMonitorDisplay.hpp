
#ifndef AMONITOR_DISPLAY_HPP
# define AMONITOR_DISPLAY_HPP

# include "IMonitorDisplay.hpp"
# include "IMonitormodule.hpp"

# include <ncurses.h>

class AMonitorDisplay
{
protected:
	IMonitorModule *	_module;

	static int			_nbrDisplay;
	WINDOW *			_win;
public:
	AMonitorDisplay(IMonitorModule * = NULL);
	AMonitorDisplay(AMonitorDisplay const &);
	virtual ~AMonitorDisplay(void);

	AMonitorDisplay &	operator=(AMonitorDisplay const &);
};

#endif
