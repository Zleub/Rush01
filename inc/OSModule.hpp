
#ifndef OS_MODULE_HPP
# define OS_MODULE_HPP

# include <string>
# include "AMonitorModule.hpp"
# include "IMonitorDisplay.hpp"

class OSModule : public AMonitorModule 
{	
public:
	typedef struct {
		std::string		date;
		std::string		time;
	}					data_t;

	OSModule(void);

	void		update(unsigned long);
	void		reset(void);

protected:
	data_t		_data;
};

#endif