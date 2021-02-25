/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:03:47 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/09 16:17:59 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"


/*
int		ft_firstpipe(t_mini *s, t_cmdl *cmd)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		close(fd[0]);
		s->firstfd = fd[1];
		close(fd[1]);
		ft_pipe(s, cmd);
	}
	else
	{
		close(fd[1]);
		waitpid(g_sig.pid, &g_sig.ret, 0);
		g_sig.ret = WEXITSTATUS(g_sig.ret);
		close(fd[0]);
	}
	close(fd[1]);
	return (0);
}

void	ft_pipe2(t_mini *s, t_cmdl *cmd, int fd, t_tok *next)
{
	s->std.in = fd;
	dup2(fd, 0);
	cmd->firsttoken = next;
	waitpid(g_sig.pid, &g_sig.ret, 0);
	if (!thereisapipe(cmd))
	{
		close(fd);
		ft_pipe(s, cmd);
	}
	else
	{
		ft_redirection(s, cmd);
		ft_exe_cmd(s, cmd);
		close(fd);
		close(0);
		close(1);
		close(2);
		ft_free_env(s->env);
		exit(g_sig.ret);
	}
	close(fd);
}

int		ft_pipe(t_mini *s, t_cmdl *cmd)
{
	t_tok	*next;
	int		fd[2];

	next = ft_next_sep(cmd->firsttoken);
	if (pipe(fd) == -1)
		return (1);
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		close(fd[0]);
		s->std.out = fd[1];
		dup2(fd[1], 1);
		if (!ft_redirection(s, cmd))
			ft_exe_cmd(s, cmd);
		close(fd[1]);
		closepipes(s);
		exit(g_sig.ret);
	}
	else
	{
		close(fd[1]);
		ft_pipe2(s, cmd, fd[0], next);
	}
	return (0);
}

int		ft_pipepar(t_mini *s, t_cmdl *cmd)
{
	t_tok	*next;
	int		fd[2];

	next = ft_next_sep(cmd->firsttoken);
	if (pipe(fd) == -1)
		return (1);
	g_sig.pid = fork();
	if (g_sig.pid != 0)
	{
		close(fd[0]);
		s->std.out = fd[1];
		dup2(fd[1], 1);
		if (!ft_redirection(s, cmd))
			ft_exe_cmd(s, cmd);
		close(fd[1]);
		closepipes(s);
		waitpid(g_sig.pid, &g_sig.ret, 0);
		exit(g_sig.ret);
	}
	else
	{
		close(fd[1]);
		ft_pipe2(s, cmd, fd[0], next);
	}
	return (0);
}



int		ft_pipe(t_mini *s, t_cmdl *cmd)
{
	t_tok	*next = NULL;
	pid_t	*pidlist;
	int fd[2];
	int j = 0;
	int i = 0;
	int save;

	next = cmd->firsttoken;
	while (next)
	{
		if (next->flag == S_PIPE)
			j++;
		next = next->next;
	}
	if (!(pidlist = ft_calloc(sizeof(pid_t), j)))
	{
		error(s, ERR_CALLOC);
		return (1);
	}
	next = ft_next_sep(cmd->firsttoken);
	while (cmd->firsttoken)
	{
		pipe(fd);
		pidlist[i] = fork();
		if (pidlist[i] == 0)
		{
			close(fd[0]);
			if (next)
				dup2(fd[1], 1);
			else
				g_sig.has_pipe = 0;
			if (!ft_redirection(s, cmd))
				ft_exe_cmd(s, cmd);
			close(fd[1]);
			closepipes(s);
			free(pidlist);
			exit(g_sig.ret);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			i++;
			cmd->firsttoken = next;
			next = ft_next_sep(cmd->firsttoken);
			close(fd[0]);
		}
	}
	waitpid(pidlist[--i], &g_sig.ret, 0);
	g_sig.ret = WEXITSTATUS(g_sig.ret);
	while (--i >= 0)
		waitpid(pidlist[i], &j, 0);
	free(pidlist);
	//exit(g_sig.ret);
	return (0);
}
*/

t_tok	*ft_pipe3(t_mini *s, t_tok *next, t_cmdl *cmd)
{
	close(s->fd[1]);
	dup2(s->fd[0], 0);
	cmd->firsttoken = next;
	next = ft_next_sep(cmd->firsttoken);
	s->y++;
	close(s->fd[0]);
	return (next);
}

void	ft_pipe2(t_tok *next, t_mini *s, t_cmdl *cmd, pid_t *pl)
{
	close(s->fd[0]);
	if (next)
		dup2(s->fd[1], 1);
	else
		g_sig.has_pipe = 0;
	if (!ft_redirection(s, cmd))
		ft_exe_cmd(s, cmd);
	close(s->fd[1]);
	closepipes(s);
	free(pl);
	exit(g_sig.ret);
}

int		ft_pipe(t_mini *s, t_cmdl *cmd)
{
	t_tok	*next;
	pid_t	*pidlist;

	s->y = ft_count_pipe(cmd->firsttoken);
	next = ft_next_sep(cmd->firsttoken);
	if (!(pidlist = ft_calloc(sizeof(pid_t), s->y)))
	{
		error(s, ERR_CALLOC);
		return (1);
	}
	s->y = 0;
	while (cmd->firsttoken)
	{
		pipe(s->fd);
		pidlist[s->y] = fork();
		if (pidlist[s->y] == 0)
			ft_pipe2(next, s, cmd, pidlist);
		else
			next = ft_pipe3(s, next, cmd);
	}
	waitpid(pidlist[--s->y], &g_sig.ret, 0);
	g_sig.ret = WEXITSTATUS(g_sig.ret);
	while (--s->y >= 0)
		waitpid(pidlist[--s->y], &s->save, 0);
	free(pidlist);
	return (0);
}