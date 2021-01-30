#include "../libft/libft.h"
#include "../includes/minishell.h"

void	handle_sigint(int signum)
{
	(void)signum;
	ft_putstr_fd("\b\b \b\b \b\b", 1);
	ft_putstr_fd("\nMINISHELL DU TURFU ---> ", 1);
	sig.interrupt = 1;
	/*exit (0);*/
}

void	sigprompt(void)
{

	ft_putstr_fd("\nMINISHELL DU TURFU ---> ", 1);
	/*ft_putstr_fd("\n", 1);*/
}

void	handle_sigquit(int signum)
{
	(void)signum;
	ft_putstr_fd("\b\b  \b\b", STDERR);
	/*ft_putstr_fd("\b", 2);*/
	sig.quit = 1;
	/*sigprompt();*/


}

int     init_signal(t_mini *s)
{
    (void)s;
	sig.interrupt = 0;
	sig.quit = 0;
	sig.status = 0;
	/*signal(SIGINT, handle_sigint);*/
	/*signal(SIGQUIT, handle_sigquit);*/
	printf("On est rentré dans la fonction INIT SIGNAL\n");
    /*printf("%d\n", sig.interrupt);*/
    return(0);
}
