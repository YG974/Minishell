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

t_tok	*link_token(t_mini *s, t_tok *tok, t_tok *new)
{
	if (tok)
	{
		tok->next = new;
		new->prev = tok;
		s->currentcmdl->token = tok->next;
	}
	else
		s->currentcmdl->firsttoken = new;
	return (new);
}

t_tok	*add_blank(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	j = s->i;
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '5')
		s->i++;
	new->str = ft_strdup(" ");
	new->flag = 5;
	new = link_token(s, tok, new);
	return (new);
}

t_tok	*add_simple_quote(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '1')
		s->i++;
	new->str = ft_strdup_size(s->p.str, s->i -1, j + 1);
	new->flag = 1;
	new = link_token(s, tok, new);
	return (new);
}

void	print_token(t_tok *tok)
{
	int i = 0;
	while (tok)
	{
		i++;
		ft_printf("%d-tok:%s\nflag:%d\nn----\n", i, tok->str,tok->flag);
		tok = tok->next;
	}
}

int		break_cmdline_into_token(t_mini *s)
{
	t_cmdl	*cmd;

	if (!(cmd = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	s->firstcmdl = cmd;
	s->currentcmdl = cmd;
	s->i = 0;
	while (s->p.buf[s->i])
	{
		if (s->p.flag[s->i] == '5')
			cmd->token = add_blank(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '1')
			cmd->token = add_simple_quote(s, s->i, cmd->token);
		/*else if (s->p.flag[s->i] == '2')*/
			/*cmd->token = add_double_quote(s, s->i, cmd->token);*/
		/*else if (s->p.flag[s->i] == '3')*/
			/*cmd->token = add_backslash(s, s->i, cmd->token);*/
		/*else if (s->p.flag[s->i] == '3')*/
			/*cmd->token = add_word(s, s->i, cmd->token);*/
		s->i++;
	}
	print_token(cmd->firsttoken);
	return (1);
}
