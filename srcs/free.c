/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:41:58 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/09 15:39:42 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

void	ft_free_tab(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env[i]);
	free(env);
}

void	closepipes(t_mini *s)
{
	close(0);
	close(1);
	close(2);
	ft_free_env(s->env);
}

int		ft_del_tokens(t_cmdl *cmd, int ret)
{
	t_tok	*tmp;
	t_tok	*todel;

	todel = cmd->firsttoken;
	while (todel && todel->prev)
		todel = todel->prev;
	while (todel)
	{
		tmp = todel->next;
		if (todel->str)
			free(todel->str);
		free(todel);
		todel->str = NULL;
		todel->next = NULL;
		todel = tmp;
	}
	cmd->firsttoken = NULL;
	return (ret);
}

void	ft_closefd(t_mini *s)
{
	if (s->std.out > 1)
		dup2(0, 1);
	if (s->std.in > 0)
		close(s->std.in);
	if (s->std.out > 1 && s->std.out != s->std.in)
		close(s->std.out);
	s->std.in = 0;
	s->std.out = 1;
	dup2(1, 1);
	dup2(1, 0);
	dup2(s->std.sin, 0);
	dup2(s->std.sout, 1);
}

void	free_all(t_mini *s, char **args, char **env, char *path)
{
	(void)args;
	ft_free_tab(env);
	ft_free_env(s->env);
	ft_del_tokens(s->currentcmdl, 0);
	free(path);
}
