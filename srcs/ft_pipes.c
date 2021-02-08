#include "../libft/libft.h"
#include "../includes/minishell.h"

t_tok	*ft_prev_sep(t_tok *tok)
{
	while (tok && tok->flag != FLAG_PIPE)
		tok = tok->prev;
	return (tok);
}

t_tok	*ft_next_sep(t_tok *tok)
{
	while (tok && tok->flag != FLAG_PIPE)
		tok = tok->next;
	if (tok && tok->next)
		return (tok->next);
	return (tok);
}

int		ft_create_pipe(t_mini *s)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		s->pipe.in = pipefd[0];
		s->pid = -1;
		return (2);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		s->pipe.out = pipefd[1];
		s->pid = pid;
		return (1);
	}
}


/*
int		minipipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		mini->pipin = pipefd[0];
		mini->pid = -1;
		mini->parent = 0;
		mini->no_exec = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		mini->pipout = pipefd[1];
		mini->pid = pid;
		mini->last = 0;
		return (1);
	}
}
void	redir_and_exec(t_mini *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	pipe = 0;
	if (is_type(prev, TRUNC))
		redir(mini, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(mini, token, APPEND);
	else if (is_type(prev, INPUT))
		input(mini, token);
	else if (is_type(prev, PIPE))
		pipe = minipipe(mini);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_and_exec(mini, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
		&& pipe != 1 && mini->no_exec == 0)
		exec_cmd(mini, token);
}

*/

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
		exit(0);
	} else
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