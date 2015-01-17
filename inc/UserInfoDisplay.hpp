
#ifndef USER_INFO_DISPLAY_HPP
# define USER_INFO_DISPLAY_HPP

# include "AMonitorDisplay.hpp"

class UserInfoDisplay : public AMonitorDisplay
{
public:
	void		draw(void *) const;
};

#endif