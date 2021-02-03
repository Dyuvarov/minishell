
#include <executor.h>

void	input_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
       	write(1, "Quit: 3\n", 8);
	}
}

void signal_handler(int sig)
{
	if (sig == SIGINT) {
		write(1, "\n", 1);
		show_promt();
	}
}