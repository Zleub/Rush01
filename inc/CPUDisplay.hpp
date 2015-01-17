
#ifndef CPU_DISPLAY_HPP
# define CPU_DISPLAY_HPP

# include "AMonitorDisplay.hpp"

class CPUDisplay : public AMonitorDisplay
{
public:
	void		draw(void *) const;
};

#endif