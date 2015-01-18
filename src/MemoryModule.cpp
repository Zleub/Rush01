
#include <ctime>
#include <sstream>
#include "Monitor.hpp"
#include "MemoryModule.hpp"
#include "MemoryDisplay.hpp"
#include <mach/mach_init.h>
#include <mach/vm_statistics.h>
#include <sys/sysctl.h>

MemoryModule::MemoryModule(void) :
	AMonitorModule(new MemoryDisplay)
{
	int		mib[2];
	size_t	len;
	int64_t	tmp;

	mib[0] = CTL_HW;
	mib[1] = HW_MEMSIZE;
	len = sizeof(int64_t);
	sysctl(mib, 2, &tmp, &len, NULL, 0);

	_data.total = tmp;
	_machPort = mach_host_self();
	_count = sizeof(_vmStats) / sizeof(natural_t);
}

void	MemoryModule::update(unsigned long time, std::string)
{
	if (KERN_SUCCESS == host_page_size(_machPort, &_pageSize) &&
		KERN_SUCCESS == host_statistics64(_machPort, HOST_VM_INFO,
			(host_info64_t)&_vmStats, &_count)
	)
	{
		_data.free = static_cast<int64_t>(_vmStats.free_count) * static_cast<int64_t>(_pageSize);
		_data.used = _data.total - _data.free;
	}

	static_cast<void>(time);
}

void	MemoryModule::reset(void)
{}
