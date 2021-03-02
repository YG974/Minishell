/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_into_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:45:47 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:21:57 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

/*
** link the new token to the previous ones or to cmdline if it's the first
*/

t_tok	*link_token(t_mini *s, t_tok *tok, t_tok *new)
{
	if (tok != NULL)
	{
		tok->next = new;
		new->prev = tok;
		s->currentcmdl->token = tok->next;
	}
	else
		s->currentcmdl->firsttoken = new;
	return (new);
}

/*
** return a specific FLAG for each metacharacter
*/

int		flag_meta_token(char *str)
{
	if (str[0] == '>' && str[1] == '\0')
		return (S_GREATER);
	else if (str[0] == '>' && str[1] == '>')
		return (D_GREATER);
	else if (str[0] == '<' && str[1] == '\0')
		return (S_LESS);
	else if (str[0] == '|' && str[1] == '\0')
		return (S_PIPE);
	else if (str[0] == ';' && str[1] == '\0')
		return (S_SEMICOLON);
	else
		return (FORBIDEN_SEP);
	return (0);
}

t_cmdl	*init_cmdline(t_mini *s)
{
	t_cmdl	*cmd;

	if (!(cmd = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	s->firstcmdl = cmd;
	s->currentcmdl = cmd;
	s->i = 0;
	return (cmd);
}

/*
** malloc the new token from dollar word and flag it with T_DOLLAR
*/

t_tok	*add_dollar(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;

	if (!(new = ft_calloc(1, sizeof(t_tok))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '4')
	{
		s->i++;
		if (s->p.str[s->i] == '$' && s->p.str[s->i - 1] != '\\')
			break ;
	}
	new->flag = T_DOLLAR;
	new->str = ft_strdup_size(s->p.str, s->i, j);
	new = link_token(s, tok, new);
	return (new);
}

/*
** main tokenization function, call the differents token functions
*/

int		break_cmdline_into_token(t_mini *s)
{
	t_cmdl	*cmd;

	cmd = init_cmdline(s);
	while (s->p.str[s->i])
	{
		if (s->p.flag[s->i] == '5')
			cmd->token = add_blank(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '1')
			cmd->token = add_simple_quote(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '2')
			cmd->token = add_double_quote(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '3')
			cmd->token = add_backslash(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '6')
			cmd->token = add_meta(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '7')
			cmd->token = add_word(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '4')
			cmd->token = add_dollar(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '8')
			cmd->token = add_newline(s, s->i, cmd->token);
		else
			s->i++;
	}
	return (1);
}
