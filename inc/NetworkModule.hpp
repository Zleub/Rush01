
#ifndef NETWORK_MODULE_HPP
# define NETWORK_MODULE_HPP

# include <string>
# include "AMonitorModule.hpp"
# include "IMonitorDisplay.hpp"

class NetworkModule : public AMonitorModule 
{	
public:
	typedef struct {
		unsigned int	maxIn;
		unsigned int	maxOut;
		unsigned int	in;
		unsigned int	out;
	}					data_t;

	NetworkModule(void);

	void		update(unsigned long);
	void		reset(void);

protected:
	data_t		_data;
};

#endif