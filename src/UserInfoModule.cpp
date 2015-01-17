
#include <unistd.h>
#include "Monitor.hpp"
#include "UserInfoModule.hpp"
#include "UserInfoDisplay.hpp"

UserInfoModule::UserInfoModule(void) :
	AMonitorModule(new UserInfoDisplay)
{}

void	UserInfoModule::update(unsigned long time)
{
	char	buf[50];

	gethostname(buf, 50);
	_data.hostname = std::string(buf);

	getlogin_r(buf, 50);
	_data.username = std::string(buf);

	_display->draw(&_data);

	static_cast<void>(time);
}

void	UserInfoModule::reset(void)
{}