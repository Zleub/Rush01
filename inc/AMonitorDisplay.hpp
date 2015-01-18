
#ifndef AMONITOR_DISPLAY_HPP
# define AMONITOR_DISPLAY_HPP

# include "IMonitorDisplay.hpp"
# include "IMonitormodule.hpp"

extern "C" {
	#include <mlx.h>
}
# include <ncurses.h>

typedef struct {
	WINDOW *		window;
	int	x;
	int	y;
}					window_t;

typedef struct {
	void *			image;
	int	x;
	int	y;
}					image_t;

class IMonitorModule;

class AMonitorDisplay
{
protected:
	IMonitorModule *	_module;
	static int			_nbrDisplay;
	window_t *			_window;
	image_t *			_imageMLX;

public:
	AMonitorDisplay(IMonitorModule * = NULL);
	AMonitorDisplay(AMonitorDisplay const &);
	virtual ~AMonitorDisplay(void);

	AMonitorDisplay &		operator=(AMonitorDisplay const &);

	virtual void			draw(void *) const;
	virtual void			drawMLX(void *) const;
	void					setWindow(window_t *);
	void					setImage(image_t *);
	window_t *				getWindow(void) const;
	image_t *				getImage(void) const;
	virtual int				getWidth(void) const;
	virtual int				getHeight(void) const;
	void					drawRectangle(int, int, int, int) const ;
};

#endif
