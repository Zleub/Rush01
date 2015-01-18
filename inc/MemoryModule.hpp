
#ifndef MEMORY_MODULE_HPP
# define MEMORY_MODULE_HPP

# include <string>
# include <mach/mach_host.h>
# include "AMonitorModule.hpp"

class MemoryModule : public AMonitorModule
{
public:
	typedef struct {
		int64_t			total;
		int64_t			used;
		int64_t			free;
	}					data_t;

	MemoryModule(void);

	void		update(unsigned long, std::string);
	void		reset(void);

protected:
	data_t					_data;
	int64_t					_maxMemory;
    vm_size_t				_pageSize;
    mach_port_t				_machPort;
    mach_msg_type_number_t	_count;
    vm_statistics64_data_t	_vmStats;
};

#endif
