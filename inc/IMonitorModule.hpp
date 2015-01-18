
#ifndef IMONITOR_MODULE_HPP
# define IMONITOR_MODULE_HPP

# include <string>
# include <sys/time.h>
# include "IMonitorDisplay.hpp"

class IMonitorModule
{
public:
    virtual void		update(unsigned long, std::string) = 0;
    virtual void		reset(void) = 0;
    virtual void		start(void) = 0;
    virtual void		pause(void) = 0;
};

#endif
