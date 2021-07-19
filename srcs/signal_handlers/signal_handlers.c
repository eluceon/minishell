#include "signal_handlers.h"

void	handle_sigint(int signum)
{
	(void)signum;
	g_sigint = 1;
	write(1, "\n", 1);
	print_promt();
}

void	handle_sigquit(int signum)
{
	(void)signum;
}

void	set_signal_handlers(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}
