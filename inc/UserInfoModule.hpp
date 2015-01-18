
#ifndef USER_INFO_MODULE_HPP
# define USER_INFO_MODULE_HPP

# include <string>
# include "AMonitorModule.hpp"
# include "IMonitorDisplay.hpp"

class UserInfoModule : public AMonitorModule
{
public:
	typedef struct {
		std::string		hostname;
		std::string		username;
	}					data_t;

	UserInfoModule(void);

	void		update(unsigned long, std::string);
	void		reset(void);

protected:
	data_t		_data;
};

#endif
