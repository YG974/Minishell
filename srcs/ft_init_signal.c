#include "../libft/libft.h"
#include "../includes/minishell.h"

void	handle_sigint(int signum)
{
	(void)signum;
	ft_putstr_fd("\b\b ", 2);
	ft_putstr_fd("\n", 2);
	sig.interrupt = 1;
	/*exit (0);*/
}

void	handle_sigquit(int signum)
{
	(void)signum;
		/*ft_putstr_fd("\b\b  \b\b", STDERR);*/
	ft_putstr_fd("\b", 2);
	sig.quit = 1;


}

int     init_signal(t_mini *s)
{
    (void)s;
	sig.interrupt = 0;
	sig.quit = 0;
	sig.status = 0;
    printf("On est rentré dans la fonction INIT SIGNAL\n");
    /*printf("%d\n", sig.interrupt);*/
    return(0);
}
