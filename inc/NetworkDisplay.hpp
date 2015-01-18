
#ifndef NETWORK_DISPLAY_HPP
# define NETWORK_DISPLAY_HPP

# include "AMonitorDisplay.hpp"

class NetworkDisplay : public IMonitorDisplay, public AMonitorDisplay
{
public:
	void			draw(void *) const;
	void			drawMLX(void *) const;
	int				getWidth(void) const;
	int				getHeight(void) const;
};

#endif
