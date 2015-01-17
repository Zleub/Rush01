
#ifndef AMONITOR_MODULE_HPP
# define AMONITOR_MODULE_HPP

# include "IMonitorModule.hpp"
# include "IMonitorDisplay.hpp"

class AMonitorModule : public IMonitorModule
{
protected:
	bool				_paused;
	IMonitorDisplay *	_display;

public:
	AMonitorModule(IMonitorDisplay * = NULL);
	AMonitorModule(AMonitorModule const &);
	virtual ~AMonitorModule(void);

	AMonitorModule &	operator=(AMonitorModule const &);

	void				start(void);
	void				pause(void);
};

#endif