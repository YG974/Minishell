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
	if (sig.pid == 0)
	{
		ft_putstr_fd("\b\b  ", STDERR);
		sigprompt();
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		/*sig.status = 130;*/
	}
	sig.interrupt = 1;
}

void	handle_sigquit(int signum)
{
	(void)signum;

	if (sig.pid != 0)
	{
		ft_putstr_fd(RED, STDERR);
		ft_putstr_fd("Quit: 3\n", STDERR);
		ft_putstr_fd(RESET, STDERR);
		/*sig.status = 131;*/
		sig.quit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);

}

int     init_signal(t_mini *s)
{
    (void)s;
	sig.interrupt = 0;
	sig.quit = 0;
	sig.pid = -1;
	sig.status = 0;
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit);
    /*printf("%d\n", sig.interrupt);*/
    return(0);
}
