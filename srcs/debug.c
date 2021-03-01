/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:38:47 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/09 14:41:04 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

/*
** DEBUG FUNCTION : print the input and the flags for the parsing.
*/

void	print_str(t_mini *s)
{
	ft_putstr_fd("str:", 1);
	ft_putstr_fd(s->p.str, 1);
	ft_putstr_fd("\nflg:", 1);
	ft_putstr_fd(s->p.flag, 1);
	ft_putstr_fd("\nbuf:", 1);
	ft_putstr_fd(s->p.buf, 1);
	ft_putstr_fd("\n--------\n", 1);
}

/*
** DEBUG FUNCTION : print all the tokens and flags
*/

void	print_token(t_mini *s)
{
	t_tok	*tok;
	t_cmdl	*cmd;
	int		i;
	int		j;

	cmd = s->firstcmdl;
	tok = cmd->firsttoken;
	i = 0;
	j = 0;
	while (cmd && tok && tok->next && tok->flag != NEWLINE)
	{
		j++;
		ft_printf("%dcmd_line----------\n", j);
		while (tok && tok->next && tok->flag != NEWLINE)
		{
			i++;
			ft_printf("%d-tok:%s|\n flag:%d|\n----\n", i, tok->str, tok->flag);
			if (tok->next)
				tok = tok->next;
		}
		if (!cmd->next)
			break ;
		cmd = cmd->next;
		tok = cmd->firsttoken;
	}
}
