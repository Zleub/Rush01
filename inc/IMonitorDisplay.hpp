
#ifndef IMONITOR_DISPLAY_HPP
# define IMONITOR_DISPLAY_HPP

# include "AMonitorDisplay.hpp"

class IMonitorDisplay {
public:
    virtual void		draw(void *) const = 0;
};

#endif
