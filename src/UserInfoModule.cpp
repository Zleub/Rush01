
#include <iostream>
#include "Monitor.hpp"
#include "UserInfoModule.hpp"
#include "UserInfoDisplay.hpp"

UserInfoModule::UserInfoModule(void) :
	AMonitorModule(new UserInfoDisplay)
{}

void	UserInfoModule::update(unsigned long time)
{
	(void) time;

	Monitor::log("Updating UserInfo");

	_data.hostname = "e1r12p3";
	_data.username = "amaurer";

	_display->draw(&_data);
}

void	UserInfoModule::reset(void)
{}