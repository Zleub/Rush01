
#ifndef USER_INFO_DISPLAY_HPP
# define USER_INFO_DISPLAY_HPP

# include "AMonitorDisplay.hpp"

class UserInfoDisplay : public IMonitorDisplay, public AMonitorDisplay
{
public:
	void			draw(void *) const;
	int	getWidth(void) const;
	int	getHeight(void) const;
};

#endif
