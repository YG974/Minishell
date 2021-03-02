/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_token.c                                      :+:      :+:    :+:   */
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
** malloc the new token from metacharacter word and flag it with meta flag
*/

t_tok	*add_meta(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;

	if (!(new = ft_calloc(1, sizeof(t_tok))))
		error(s, ERR_CALLOC);
	if (s->p.str[s->i] == '>' && s->p.str[s->i + 1] == '|')
		s->i++;
	else if (s->p.str[s->i] == s->p.str[s->i + 1])
		s->i++;
	s->i++;
	new->str = ft_strdup_size(s->p.str, s->i, j);
	new->flag = flag_meta_token(new->str);
	new = link_token(s, tok, new);
	return (new);
}

/*
** malloc the new token from regular word and flag it with T_WORD
*/

t_tok	*add_word(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;

	if (!(new = ft_calloc(1, sizeof(t_tok))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '7')
		s->i++;
	new->flag = T_WORD;
	new->str = ft_strdup_size(s->p.str, s->i, j);
	new = link_token(s, tok, new);
	return (new);
}

/*
** malloc the new token from '\n' and flag it with NEWLINE
*/

t_tok	*add_newline(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;

	(void)j;
	if (!(new = ft_calloc(1, sizeof(t_tok))))
		error(s, ERR_CALLOC);
	new->str = ft_strdup("newline");
	new->flag = NEWLINE;
	new = link_token(s, tok, new);
	s->i++;
	return (new);
}

/*
** malloc the new token from space or tqb and flag it with BLANK
*/

t_tok	*add_blank(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;

	(void)j;
	if (!(new = ft_calloc(1, sizeof(t_tok))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '5')
		s->i++;
	new->str = ft_strdup(" ");
	new->flag = BLANK;
	new = link_token(s, tok, new);
	return (new);
}

/*
** shift all the string by one to the left in order to erase '\' preceding
** escaped character
*/

char	*shift_str_left(char *str, int i)
{
	while (str[i])
	{
		str[i - 1] = str[i];
		i++;
	}
	str[i - 1] = '\0';
	return (str);
}
