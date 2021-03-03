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

void		flag_redir_arg(t_mini *s, t_tok *tok)
{
	tok->flag = REDIR_ARG;
	s->parsed = 0;
	return ;
}

/*
** check if a redirection argument is an empty string -> ambigous redirect
*/

int			check_ambigous_redir(t_mini *s, t_cmdl *cmd, t_tok *tok)
{
	s->parsed = 0;
	while (tok && tok->next && is_control_op(tok->flag) == -1)
	{
		while (tok && (is_redir(tok->flag) != 1))
			tok = tok->next;
		if (tok && is_redir(tok->flag) == 1)
			s->parsed = 1;
		if (tok && tok->next)
			tok = tok->next;
		if (tok && tok->next && tok->flag == BLANK)
			tok = tok->next;
		if (tok && s->parsed == 1 && (tok->flag == T_DOLLAR || tok->flag == 1))
		{
			if (tok && tok->str[0] == '\0')
				return (-1);
			flag_redir_arg(s, tok);
		}
		else if (tok && tok->flag <= REDIR_ARG && s->parsed == 1)
			flag_redir_arg(s, tok);
	}
	if (s->parsed != 0)
		return (-1);
	tok = cmd->firsttoken;
	return (0);
}

/*
** loop for executing each command line, and assigning exit status to '$?'
*/

void		exec_cmdlines(t_mini *s)
{
	t_cmdl	*cmd;

	cmd = s->firstcmdl;
	while (cmd && !s->error && cmd->token->flag != NEWLINE)
	{
		handle_dollar_question_mark(s, cmd);
		expand_dollars(s, cmd);
		cmd = join_tokens(cmd);
		if (check_ambigous_redir(s, cmd, cmd->token) == -1)
			error_ambigous(s, cmd);
		else if (!thereisapipe(cmd))
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
