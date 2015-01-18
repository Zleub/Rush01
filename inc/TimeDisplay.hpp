
#ifndef TIME_DISPLAY_HPP
# define TIME_DISPLAY_HPP

# include "AMonitorDisplay.hpp"

class TimeDisplay : public IMonitorDisplay, public AMonitorDisplay
{
public:
	void			draw(void *) const;
	int				getWidth(void) const;
	int				getHeight(void) const;
};

#endif
