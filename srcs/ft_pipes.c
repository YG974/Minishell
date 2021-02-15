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

t_tok	*ft_next_sep(t_tok *tok)
{
	while (tok && tok->flag != FLAG_PIPE)
		tok = tok->next;
	if (tok && tok->next)
		return (tok->next);
	return (tok);
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
		close(4);
		s->firstfd = 0;
		close(0);
		close(1);
		close(2);
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
		close(0);
		close(1);
		close(2);
		exit(g_sig.ret);
	}
	else
	{
		close(fd[1]);
		ft_pipe2(s, cmd, fd[0], next);
	}
	return (0);
}

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

int		thereisapipe(t_cmdl *cmd)
{
	t_tok	*tmp;

	tmp = cmd->firsttoken;
	while (tmp)
	{
		if (tmp->flag == FLAG_PIPE)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
