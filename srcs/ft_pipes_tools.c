/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:03:47 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/09 16:17:59 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

int		thereisapipe(t_cmdl *cmd)
{
	t_tok	*tmp;

	tmp = cmd->firsttoken;
	while (tmp)
	{
		if (tmp->flag == S_PIPE)
		{
			g_sig.in_func = 1;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int		ft_count_pipe(t_tok *tok)
{
	int		i;
	t_tok	*tmp;

	i = 0;
	tmp = tok;
	while (tmp)
	{
		if (tmp->flag == S_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_tok	*ft_next_sep(t_tok *tok)
{
	while (tok && tok->flag != S_PIPE)
		tok = tok->next;
	if (tok && tok->next)
		return (tok->next);
	return (tok);
}

int		pipe_error(t_mini *s)
{
	error(s, ERR_CALLOC);
	return (1);
}
