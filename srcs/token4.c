/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:21:15 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:21:17 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

void	check_lit_char(t_mini *s, t_cmdl *cmd)
{
	cmd->flag[s->i] = '3';
	s->i++;
	if (cmd->str[s->i])
		cmd->flag[s->i] = '3';
	s->i++;
}

void	check_quotes(t_mini *s, t_cmdl *cmd)
{
	int i;

	i = -1;
	cmd->flag = ft_strdup(cmd->str);
	while (cmd->flag && cmd->flag[++i])
		cmd->flag[i] = '0';
	s->i = 0;
	while (cmd->str[s->i])
	{
		if (cmd->str[s->i] == '\"')
			check_double_quotes(s, cmd);
		else if (cmd->str[s->i] == '\'')
			check_simple_quotes(s, cmd);
		else if (cmd->str[s->i] == '\\')
			check_lit_char(s, cmd);
		else
			s->i++;
	}
}

void	ft_closefd(t_mini *s)
{
	if (s->std.out > 1)
		dup2(0, 1);
	if (s->std.in > 0)
		close(s->std.in);
	if (s->std.out > 1)
		close(s->std.out);
	s->std.in = 0;
	s->std.out = 1;
	dup2(1, 1);
	dup2(1, 0);
}

void	free_cmd_str(t_cmdl *cmd)
{
	if (cmd->str)
		free(cmd->str);
	if (cmd->flag)
		free(cmd->flag);
}

void	break_cmdline_into_token(t_mini *s)
{
	t_cmdl	*cmd;

	cmd = s->firstcmdl;
	while (cmd && !s->error)
	{
		check_quotes(s, cmd);
		check_dollars(s, cmd);
		expand_dollars(s, cmd);
		free_cmd_str(cmd);
		cmd->str = cmd->buf;
		check_quotes(s, cmd);
		check_dollars(s, cmd);
		ft_get_tokens(s, cmd);
		handle_dollar_question_mark(s, cmd);
		if (thereisapipe(cmd))
		{
			if (!ft_redirection(s, cmd))
				ft_exe_cmd(s, cmd);
		}
		else
			ft_firstpipe(s, cmd);
		ft_closefd(s);
		ft_del_tokens(cmd, 0);
		cmd = cmd->next;
	}
}
