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

/*
**	check if the command line has only assignement : name=value ...
**	return 0 if there is a command in the line (a string without '=')
**	return 1 if there is only assignements in the command line
**	(only strings that contains '=')
*/

int		cmd_has_only_assignement(t_cmdl *cmd)
{
	cmd->token = cmd->firsttoken;
	if (cmd->token == NULL)
		return (0);
	while (cmd->token)
	{
		if (!(ft_strchr(cmd->token->str, '=')) && cmd->token->flag != 2)
			return (0);
		cmd->token = cmd->token->next;
	}
	cmd->token = cmd->firsttoken;
	return (1);
}

int		apply_assignement(t_mini *s, t_cmdl *cmd)
{
	char **args;

	(void)s;
	cmd->buf = ft_strjoin_free_s1(cmd->buf, "\n");
	cmd->token = cmd->firsttoken;
	while (cmd->token)
	{
		if (ft_strchr(cmd->token->str, '='))
		{
			cmd->buf = ft_strjoin_free_s1(cmd->buf, cmd->token->str);
			cmd->buf = ft_strjoin_free_s1(cmd->buf, "\n");
		}
		cmd->token = cmd->token->next;
	}
	args = ft_split(cmd->buf, '\n');
	if (cmd->buf)
		free(cmd->buf);
	cmd->ret = ft_export(s, args);
	ft_free_tab(args);
	return (cmd->ret);
}
