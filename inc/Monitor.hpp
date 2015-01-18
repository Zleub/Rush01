
#ifndef MONITOR_HPP
# define MONITOR_HPP

# include <vector>
# include <string>
# include "AMonitorModule.hpp"

#include <ncurses.h>

struct Monitor {
protected:
	typedef std::vector<IMonitorModule*>::iterator	moduleIterator_t;

	static std::vector<IMonitorModule*>		_modules;
	static unsigned long					_updateInterval;
	static unsigned long					_lastUpdate;

public:
	static void								initNcurses(void);
	static void								registerModule(AMonitorModule *);
	static void								startMonitoring(void);
	static void								update(void);
	static void								start(void);
	static void								pause(void);
	static void								reset(void);
	static void								log(std::string, bool = true);
	static unsigned long					getTime(void);

	static void								handleInput(void);

	static void								setUpdateInterval(double);
	static double							getUpdateInterval(void);
	static std::vector<IMonitorModule*> &	getModules(void);
};

#endif
