/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_token2.c                                     :+:      :+:    :+:   */
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
** malloc the new token from escaped char and flag it with T_WORD
*/

t_tok	*add_backslash(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;

	if (!(new = ft_calloc(1, sizeof(t_tok))))
		error(s, ERR_CALLOC);
	s->i++;
	new->str = ft_strdup_size(s->p.str, s->i, j);
	new->flag = T_WORD;
	new = link_token(s, tok, new);
	return (new);
}

/*
** malloc the new token from double quoted input and flag it with T_WORD
*/

t_tok	*add_double_quote(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;

	if (!(new = ft_calloc(1, sizeof(t_tok))))
		error(s, ERR_CALLOC);
	if (s->p.str[s->i] == '\"')
		j++;
	while (s->p.flag[s->i] == '2')
	{
		s->i++;
		if (s->p.str[s->i] == '"' && s->p.str[s->i - 1] != '\\')
			break ;
	}
	if (s->p.str[s->i] == '\"')
	{
		s->i++;
		new->str = ft_strdup_size(s->p.str, s->i - 1, j);
	}
	else
		new->str = ft_strdup_size(s->p.str, s->i, j);
	new->str = delete_backslash(new->str);
	new->flag = T_WORD;
	new = link_token(s, tok, new);
	return (new);
}

/*
** malloc the new token from single quoted input and flag it with T_WORD
*/

t_tok	*add_simple_quote(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;

	if (!(new = ft_calloc(1, sizeof(t_tok))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '1')
		s->i++;
	new->str = ft_strdup_size(s->p.str, s->i - 1, j + 1);
	new->flag = T_WORD;
	new = link_token(s, tok, new);
	return (new);
}

/*
** join token which are not seperated by BLANK
** for example the string \o\k'bo'"goss" will return the 3 followings token
** token 1 : o	|token 2 : k	| token 3 : bo	| token 4: goss
** we have to join them to create a single token like in bash
*/

t_cmdl	*join_tokens(t_cmdl *cmd)
{
	t_tok	*tmp;
	t_tok	*tok;

	tok = cmd->firsttoken;
	while (tok && tok->next)
	{
		while (tok->next && (tok->flag == 1 || tok->flag == 4) &&
					(tok->next->flag == 1 || tok->next->flag == 4))
		{
			tmp = tok->next;
			tok->next = tmp->next;
			tok->str = ft_strjoin_free_s1(tok->str, tmp->str);
			free(tmp->str);
			free(tmp);
		}
		tok = tok->next;
	}
	return (cmd);
}

/*
** malloc the new token and flag it with T_WORD, for TOKEN WORD
*/

char	*delete_backslash(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i - 1] == '\\' && str[i - 1])
			str = shift_str_left(str, i);
		else if (str[i] == '"' && str[i - 1] == '\\' && str[i - 1])
			str = shift_str_left(str, i);
		else if (str[i] == '\\' && str[i - 1] == '\\' && str[i - 1])
			str = shift_str_left(str, i);
		i++;
	}
	return (str);
}
