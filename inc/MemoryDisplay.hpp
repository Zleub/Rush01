
#ifndef MEMORY_DISPLAY_HPP
# define MEMORY_DISPLAY_HPP

# include "AMonitorDisplay.hpp"

class MemoryDisplay : public IMonitorDisplay, public AMonitorDisplay
{
public:
	void		draw(void *) const;
};

#endif
