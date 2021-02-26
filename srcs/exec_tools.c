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

/*
** loop for executing each command line, and assigning exit status to '$?'
*/

void		exec_cmdlines(t_mini *s)
{
	t_cmdl	*cmd;

	cmd = s->firstcmdl;
	while (cmd && !s->error && cmd->token->flag != NEWLINE)
	{
		expand_dollars(s, cmd, 0, 0);
		handle_dollar_question_mark(s, cmd);
		if (!thereisapipe(cmd))
		{
			s->save_tok = cmd->firsttoken;
			ft_pipe(s, cmd);
			cmd->firsttoken = s->save_tok;
		}
		else if (!ft_redirection(s, cmd))
			ft_exe_cmd(s, cmd);
		ft_closefd(s);
		ft_del_tokens(cmd, 0);
		cmd = cmd->next;
	}
}

/*
** Split the input into seperated cmdlines, seperated by semicolons ';'
*/

int			split_cmdl(t_mini *s)
{
	t_cmdl	*cmd;

	s->parsed = -1;
	cmd = s->firstcmdl;
	cmd->token = cmd->firsttoken;
	while (cmd->token->flag != NEWLINE || !cmd->token)
	{
		if (cmd->token->flag <= REDIR_ARG)
			s->parsed = 1;
		if (cmd->token->flag == S_SEMICOLON && s->parsed == 1)
		{
			s->parsed = -1;
			cmd = new_cmd_line(cmd);
		}
		else if (cmd->token->flag == S_SEMICOLON && s->parsed == -1)
			return (syntax_error(s, ";", 3));
		else
			cmd->token = cmd->token->next;
		if (cmd->token->flag == NEWLINE)
			break ;
	}
	cmd->token = cmd->firsttoken;
	return (0);
}

/*
** malloc a new command line and link the token and cmdlines
*/

t_cmdl		*new_cmd_line(t_cmdl *cmd)
{
	t_cmdl	*new;
	t_tok	*tmp;

	tmp = cmd->token->next;
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		return (NULL);
	cmd->next = new;
	new->firsttoken = tmp;
	new->token = tmp;
	new->token->prev = NULL;
	cmd->token->next = NULL;
	return (new);
}

/*
**	check if the command line has only assignement : name=value ...
**	return 0 if there is a command in the line (a string without '=')
**	return 1 if there is only assignements in the command line
**	(only strings that contains '=')
*/

int			cmd_has_only_assignement(t_cmdl *cmd)
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

int			apply_assignement(t_mini *s, t_cmdl *cmd)
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
	if (args)
	{
		print_tab(args);
		cmd->ret = ft_export(s, args);
	}
	/*ft_free_tab(args);*/
	return (cmd->ret);
}
