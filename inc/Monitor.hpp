
#ifndef MONITOR_HPP
# define MONITOR_HPP

# include <vector>
# include <string>
# include "AMonitorModule.hpp"

#include <ncurses.h>

struct Monitor {
protected:
	typedef std::vector<AMonitorModule*>::iterator	moduleIterator_t;

	static std::vector<AMonitorModule*>		_modules;
	static unsigned long					_updateInterval;
	static unsigned long					_lastUpdate;

	// GRAPHIC NASTY STUFF
	static std::string						_type;
	static void *							_mlx;
	static void *							_win;

public:
	static void								initNcurses(void);
	static void								initMLX(void);
	static void								registerModule(AMonitorModule *);
	static void								startMonitoring(void);
	static void								update(void);
	static void								updateMLX(void);
	static int								drawMLX(void);
	static void								start(void);
	static void								pause(void);
	static void								reset(void);
	static void								log(std::string, bool = true);
	static unsigned long					getTime(void);
	static void								createWindows(void);
	static void								createImages(void);

	static void								handleInput(void);

	static void								setUpdateInterval(double);
	static double							getUpdateInterval(void);
	static std::vector<AMonitorModule*> &	getModules(void);
	static void *							getMlx(void);
	static void *							getWin(void);
	static std::string						getType(void);
};

#endif
