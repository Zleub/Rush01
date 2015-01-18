
#ifndef AMONITOR_DISPLAY_HPP
# define AMONITOR_DISPLAY_HPP

# include "IMonitorDisplay.hpp"
# include "IMonitormodule.hpp"

# include <ncurses.h>

typedef struct {
	WINDOW *		window;
	int	x;
	int	y;
}					window_t;

class IMonitorModule;

class AMonitorDisplay
{
protected:
	IMonitorModule *	_module;
	static int			_nbrDisplay;
	window_t *			_window;

public:
	AMonitorDisplay(IMonitorModule * = NULL);
	AMonitorDisplay(AMonitorDisplay const &);
	virtual ~AMonitorDisplay(void);

	AMonitorDisplay &		operator=(AMonitorDisplay const &);

	virtual void			draw(void *) const;
	void					setWindow(window_t *);
	window_t *				getWindow(void) const;
	virtual int				getWidth(void) const;
	virtual int				getHeight(void) const;
};

#endif
