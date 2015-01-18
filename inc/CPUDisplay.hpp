
#ifndef CPU_DISPLAY_HPP
# define CPU_DISPLAY_HPP

# include "AMonitorDisplay.hpp"

class CPUDisplay : public IMonitorDisplay, public AMonitorDisplay
{
public:
	void			draw(void *) const;
	void			drawMLX(void *) const;
	int				getWidth(void) const;
	int				getHeight(void) const;
};

#endif
