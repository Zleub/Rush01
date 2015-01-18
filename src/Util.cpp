
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include "Util.hpp"

std::string		Util::execute(char const * path, char ** const args, unsigned int bufferSize)
{
	int     pipefd[2];
    int     pid;

    pipe(pipefd);
    pid = fork();

    if (pid == 0)
    {
        close(pipefd[0]);

        dup2(pipefd[1], 1);
        dup2(pipefd[1], 2);

        close(pipefd[1]);

        execv(path, args);
        exit(0);
    }
    else
    {
        char	buffer[bufferSize + 1] = { 0 };

        close(pipefd[1]);

        read(pipefd[0], buffer, bufferSize);
		kill(pid, SIGINT);

        return std::string(buffer);
    }

    return std::string();
}