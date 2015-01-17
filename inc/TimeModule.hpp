
#ifndef TIME_MODULE_HPP
# define TIME_MODULE_HPP

# include <string>
# include "AMonitorModule.hpp"
# include "IMonitorDisplay.hpp"

class TimeModule : public AMonitorModule 
{	
public:
	typedef struct {
		std::string		date;
		std::string		time;
	}					data_t;

	TimeModule(void);

	void		update(unsigned long);
	void		reset(void);

protected:
	data_t		_data;
};

#endif