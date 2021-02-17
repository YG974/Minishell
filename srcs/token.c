/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:45:47 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:21:57 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

void	add_blank(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '5')
		s->i++;
	new->str = ft_strdup(" ");
	new->flag = 5;
	if (tok)
	{
		tok->next = new;
		new->prev = tok;
	}
	
}
int		break_cmdline_into_token(t_mini *s)
{
	t_cmdl	*cmd;

	cmd = init
	if (!(cmd = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	cmd->firsttoken = tok;
	s->firstcmdl = cmd;
	s->i = 0;
	while (s->p.buf[s->i])
	{
		if (s->p.flag[s->i] == '5')
			add_blank(s, s->i, tok);
		else if (s->p.flag[s->i] == '1')
			add_simple_quote(s, s->i, tok);
		else if (s->p.flag[s->i] == '2')
			add_double_quote(s, s->i, tok);
		else if (s->p.flag[s->i] == '3')
			add_backslash(s, s->i, tok);
		else if (s->p.flag[s->i] == '3')
			add_word(s, s->i, &tok);
		s->i++;
	}
	return (1);
}
