
#ifndef IMONITOR_DISPLAY_HPP
# define IMONITOR_DISPLAY_HPP

class IMonitorDisplay {
public:
    virtual void		draw(void *) const = 0;
};

#endif