#include "../libft/libft.h"
#include "../includes/minishell.h"

t_tok	*ft_next_sep(t_tok *tok)
{
	while (tok && tok->flag != FLAG_PIPE)
		tok = tok->next;
	if (tok && tok->next)
		return (tok->next);
	return (tok);
}

int		ft_pipe(t_mini *s, t_cmdl *cmd)
{
	t_tok	*next;
	int		fd[2];
	int		pid;

	next = ft_next_sep(cmd->firsttoken);
	if (pipe(fd) == -1)
		return (1);
	//RETOUR PIPE ERREUR
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		s->std.out = fd[1];
		dup2(fd[1], 1);
		ft_redirection(s, cmd);
		ft_exe_cmd(s, cmd);
		close(fd[1]);
		exit(s->status);
	} else // ls -l | grep 42 | grep 12
	{
		close(fd[1]);
		s->std.in = fd[0];
		dup2(fd[0], 0);
		cmd->firsttoken = next;
		waitpid(pid, NULL, 0);
		if (!thereisapipe(cmd))
			ft_pipe(s, cmd);
		else
		{
			ft_redirection(s, cmd);
			ft_exe_cmd(s, cmd);
		}
		close(fd[0]);
	}
	return (0);
}


int		thereisapipe(t_cmdl *cmd)
{
	t_tok	*tmp;

	tmp = cmd->firsttoken;
	while (tmp)
	{
		if (tmp->flag == FLAG_PIPE)
			return(0);
		tmp = tmp->next;
	}
	return (1);
}