
#ifndef OS_DISPLAY_HPP
# define OS_DISPLAY_HPP

# include "AMonitorDisplay.hpp"

class OSDisplay : public IMonitorDisplay, public AMonitorDisplay
{
public:
	void		draw(void *) const;
};

#endif
