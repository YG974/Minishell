/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:53:01 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 10:53:03 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

/*
** set exit_status to 2, and print syntax error string to STD ERROR
*/

int		syntax_error(t_mini *s, char *str, int err)
{
	s->error = 3;
	(void)s;
	g_sig.ret = 2;
	ft_putstr_fd(RED, STDERR);
	if (err == 1)
		ft_putstr_fd("Minishell: syntax error : single quotes opened.\n",
				STDERR);
	else if (err == 2)
		ft_putstr_fd("Minishell: syntax error : double quotes opened.\n",
				STDERR);
	else
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token: \"",
				STDERR);
		ft_putstr_fd(str, STDERR);
		ft_putstr_fd("\"\n", STDERR);
	}
	ft_putstr_fd(RESET, STDERR);
	return (-1);
}

/*
** look for pipe syntax error :
** a pipe need at least one WORD token before AND after
** command [ | command2 ... ]
** return -1 if syntax error
** return 1 if NO syntax error
*/

int		is_control_op(int flag)
{
	if (flag == S_SEMICOLON || flag == NEWLINE || flag == S_PIPE)
		return (1);
	else
		return (-1);
}

int		pipe_syntax_error(t_mini *s, t_tok *tok)
{
	int		i;
	t_tok	*tmp;

	(void)s;
	i = 0;
	tmp = tok;
	while (tmp && tmp->prev && i == 0 && (is_control_op(tmp->prev->flag)) == -1)
	{
		tmp = tmp->prev;
		if (tmp->flag == T_WORD || (tmp->flag >= 11 && tmp->flag <= 13))
			i++;
	}
	tmp = tok;
	while (tmp && tmp->next && i == 1 && (is_control_op(tmp->next->flag)) == -1)
	{
		tmp = tmp->next;
		if (tmp->flag == T_WORD || (tmp->flag >= 11 && tmp->flag <= 13))
			i++;
	}
	if (i == 2 && (g_sig.has_pipe = 1))
		return (1);
	s->currentcmdl->token = tok;
	return (-1);
}

/*
** set exit_status to 2, and print syntax error string to STD ERROR
*/

int		syntax_sep_error(t_mini *s, t_tok *tok, int err)
{
	s->error = 3;
	(void)s;
	g_sig.ret = 2;
	ft_putstr_fd(RED, STDERR);
	if (err == 1)
		ft_putstr_fd("Minishell: syntax error near unexpected token: \"",
				STDERR);
	else if (err == 2)
		ft_putstr_fd("Minishell: syntax error token not supported: \"",
				STDERR);
	if (tok->str)
		ft_putstr_fd(tok->str, STDERR);
	ft_putstr_fd("\"\n", STDERR);
	ft_del_tokens(s->currentcmdl, 0);
	return (-1);
}

/*
** call the differents syntax checking functions for the diffecrents operators
** return 1 if NO syntax error
** return -1 and call functions that print error string if syntax error.
*/

int		check_sep_syntax(t_mini *s)
{
	t_tok	*tok;

	(void)s;
	tok = s->firstcmdl->firsttoken;
	if (tok->flag == S_SEMICOLON)
		return (syntax_sep_error(s, tok, 1));
	while (tok && tok->flag != NEWLINE)
	{
		if (tok->flag == FORBIDEN_SEP)
			return (syntax_sep_error(s, s->currentcmdl->token, 2));
		else if ((is_redir(tok->flag) == 1) && ((find_redir_arg(s, tok)) == -1))
			return (syntax_sep_error(s, s->currentcmdl->token, 1));
		else if (tok->flag == S_PIPE && (pipe_syntax_error(s, tok)) == -1)
			return (syntax_sep_error(s, s->currentcmdl->token, 1));
		tok = tok->next;
	}
	return (1);
}
