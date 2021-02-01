#include "../libft/libft.h"
#include "../includes/minishell.h"

void	handle_sigint(int signum)
{
	/*ft_printf("\npid %d\n", sig.pid);*/
	/*ft_printf("\nstatus %d\n", sig.status);*/
	/*ft_printf("\nsigint %d\n", sig.interrupt);*/
	/*ft_printf("\nsigquit %d\n", sig.quit);*/
	/*if (sig.pid == 0)*/
	/*{*/
		/*exit(128 + signum);*/
		/*ft_putstr_fd("\n", 1);*/
		/*sig.status = 1;*/
	/*}*/
	/*else*/
	/*{*/
		/*ft_putstr_fd("\b\b  \b\b", 1);*/
		/*ft_putstr_fd("\nMINISHELL DU TURFU ---> ", 1);*/
	/*ft_putstr_fd("\n", 1);*/
	/*}*/
	/*sig.status = 128 + signum;*/
	/*sig.interrupt = 1;*/
	/*exit (0);*/
	(void)signum;
	if (sig.pid == 0)
	{
		ft_putstr_fd("\b\b  ", STDERR);
		ft_putstr_fd("\nMINISHELL DU TURFU ---> ", 1);
		/*sig.status = 1;*/
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		sig.status = 130;
	}
	sig.interrupt = 1;
}

void	sigprompt(void)
{

	ft_putstr_fd("\nMINISHELL DU TURFU ---> ", 1);
	/*ft_putstr_fd("\n", 1);*/
}

void	handle_sigquit(int signum)
{
	(void)signum;
		char	*nbr;

	nbr = ft_itoa(signum);
	if (sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putendl_fd(nbr, STDERR);
		sig.status = 131;
		sig.quit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);


	/*ft_printf("\npid %d\n", sig.pid);*/
	/*ft_printf("\nstatus %d\n", sig.status);*/
	/*ft_printf("\nsigint %d\n", sig.interrupt);*/
	/*ft_printf("\nsigquit %d\n", sig.quit);*/
	/*if (sig.pid != 0)*/
	/*{*/
		/*ft_putstr_fd("Quit : ", 1);*/
		/*ft_putstr_fd("3\n", 1);*/
		/*sig.status = 128 + signum;*/
	/*}*/
	/*else*/
		/*ft_putstr_fd("\b\b  \b\b", 1);*/
	/*ft_putstr_fd("\b", 2);*/
	/*sig.quit = 1;*/
	/*sigprompt();*/
}

int     init_signal(t_mini *s)
{
    (void)s;
	sig.interrupt = 0;
	sig.quit = 0;
	sig.pid = 0;
	sig.status = 0;
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit);
	/*printf("On est rentré dans la fonction INIT SIGNAL\n");*/
    /*printf("%d\n", sig.interrupt);*/
    return(0);
}
