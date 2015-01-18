
#ifndef CPU_DISPLAY_HPP
# define CPU_DISPLAY_HPP

# include "AMonitorDisplay.hpp"

class CPUDisplay : public IMonitorDisplay, public AMonitorDisplay
{
public:
	void		draw(void *) const;
};

#endif
