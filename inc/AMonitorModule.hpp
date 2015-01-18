
#ifndef AMONITOR_MODULE_HPP
# define AMONITOR_MODULE_HPP

# include "IMonitorModule.hpp"
# include "IMonitorDisplay.hpp"

class AMonitorModule : public IMonitorModule
{
protected:
	bool				_paused;
	AMonitorDisplay *	_display;

public:
	AMonitorModule(AMonitorDisplay * = NULL);
	AMonitorModule(AMonitorModule const &);
	virtual ~AMonitorModule(void);

	AMonitorModule &	operator=(AMonitorModule const &);

	void				start(void);
	void				pause(void);
	AMonitorDisplay *	getDisplay(void) const;
};

#endif