
#ifndef CPU_MODULE_HPP
# define CPU_MODULE_HPP

# include <string>
# include <vector>
# include "AMonitorModule.hpp"
# include "IMonitorDisplay.hpp"

class CPUModule : public AMonitorModule 
{	
public:
	typedef struct {
		unsigned int		coreCount;
		std::vector<float>	coreActivity;
		std::vector<float>	coreSpeed;
		unsigned int		processCount;
		unsigned int		threadCount;
	}						data_t;

	CPUModule(void);

	void		update(unsigned long);
	void		reset(void);

protected:
	data_t		_data;
};

#endif