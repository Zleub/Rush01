
#include <cstdlib>
#include "Monitor.hpp"
#include "NetworkModule.hpp"
#include "NetworkDisplay.hpp"
#include "Util.hpp"

NetworkModule::NetworkModule(void) :
	AMonitorModule(new NetworkDisplay)
{}

void	NetworkModule::update(unsigned long time)
{
    size_t  occ;

    _data.in = 0;
    _data.maxIn = 0;
    _data.out = 0;
    _data.maxOut = 0;

	char *  args[6] = {
        (char *) "top",
        (char *) "-c",
        (char *) "n",
        (char *) "-l",
        (char *) "0",
        NULL
    };

    try
    {

        std::string top = Util::execute("/usr/bin/top", args, 500);

        occ = top.find("packets:");

        if (occ != std::string::npos && top.size() > occ + 9)
        {
            std::string line = top.substr(occ + 9);

            _data.in = atoi(line.c_str());

            occ = line.find("/");

            if (occ != std::string::npos)
            {
                _data.maxIn = atoi(line.c_str());

                occ = line.find("in, ");

                if (occ != std::string::npos && line.size() > occ + 4)
                {
                    line = line.substr(occ + 4);

                    _data.out = atoi(line.c_str());

                    occ = line.find("/");

                    if (occ != std::string::npos)
                        _data.maxOut = atoi(line.c_str());
                }
            }
        }
    }
    catch (std::exception)
    {}

	_display->draw(&_data);

	static_cast<void>(time);
}

void	NetworkModule::reset(void)
{}