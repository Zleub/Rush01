
#ifndef OS_MODULE_HPP
# define OS_MODULE_HPP

# include <string>
# include "AMonitorModule.hpp"
# include "IMonitorDisplay.hpp"

class OSModule : public AMonitorModule 
{	
public:
	typedef struct {
		std::string		os;
		std::string		release;
		std::string		version;
		std::string		machine;
	}					data_t;

	OSModule(void);

	void		update(unsigned long);
	void		reset(void);

protected:
	data_t		_data;
};

#endif