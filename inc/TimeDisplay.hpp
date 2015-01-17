
#ifndef TIME_DISPLAY_HPP
# define TIME_DISPLAY_HPP

# include "AMonitorDisplay.hpp"

class TimeDisplay : public AMonitorDisplay
{
public:
	void		draw(void *) const;
};

#endif