#include "../libft/libft.h"
#include "../includes/minishell.h"

void	sigprompt(void)
{
	ft_putstr_fd(CYAN, STDOUT);
	ft_putstr_fd("\nMINISHELL DU TURFU -> ", STDOUT);
	ft_putstr_fd(RESET, STDOUT);
}

void	handle_sigint(int signum)
{
	(void)signum;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\b\b  ", STDERR);
		sigprompt();
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		/*g_sig.status = 130;*/
	}
	g_sig.interrupt = 1;
}

void	handle_sigquit(int signum)
{
	(void)signum;

	if (g_sig.pid != 0)
	{
		ft_putstr_fd(RED, STDERR);
		ft_putstr_fd("Quit: 3\n", STDERR);
		ft_putstr_fd(RESET, STDERR);
		/*g_sig.status = 131;*/
		g_sig.quit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);

}

int     init_signal(t_mini *s)
{
    (void)s;
	g_sig.interrupt = 0;
	g_sig.quit = 0;
	g_sig.pid = -1;
	g_sig.status = 0;
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit);
    /*printf("%d\n", g_sig.interrupt);*/
    return(0);
}
