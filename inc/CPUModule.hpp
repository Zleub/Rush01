
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
		std::string			name;
		unsigned int		coreCount;
		double				frequency;
		unsigned int		processCount;
		unsigned int		threadCount;
		double				userUsage;
		double				systemUsage;
		double				idle;
	}						data_t;

	CPUModule(void);

	void					update(unsigned long);
	void					reset(void);

protected:
	data_t					_data;

	double					_getCPUFrequency(void);
	void					_setThreadCount(std::string const &);
	void					_setCPUUsage(std::string const &);
};

#endif
