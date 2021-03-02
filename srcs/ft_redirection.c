/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:18:16 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/09 16:19:18 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

int		ft_change_fd2(t_mini *s, t_tok *tok, t_tok *tmp)
{
	if (s->std.out > 2)
		close(s->std.out);
	if (tok->flag == D_GREATER)
		s->std.out = open(tmp->str, O_WRONLY | O_CREAT | O_APPEND, 420);
	else
		s->std.out = open(tmp->str, O_WRONLY | O_CREAT | O_TRUNC, 420);
	if (s->std.out < 0)
	{
		s->std.out = 0;
		return (1);
	}
	else
	{
		dup2(s->std.out, 1);
	}
	return (0);
}

int		ft_change_fd(t_mini *s, t_tok *tok)
{
	t_tok	*tmp;

	tmp = tok->next;
	while (tmp && tmp->flag != REDIR_ARG)
		tmp = tmp->next;
	if (!tmp)
		return (1);
	if (tok->flag == S_GREATER || tok->flag == D_GREATER)
		return (ft_change_fd2(s, tok, tmp));
	if (tok->flag == S_LESS)
	{
		if (s->std.in > 2)
			close(s->std.in);
		s->std.in = open(tmp->str, O_RDONLY);
		if (s->std.in < 0)
		{
			s->std.in = 0;
			return (1);
		}
		else
		{
			dup2(s->std.in, 0);
		}
	}
	return (0);
}

int		ft_redirection(t_mini *s, t_cmdl *cmd)
{
	t_tok	*tmp;

	tmp = cmd->firsttoken;
	while (tmp && tmp->flag != S_PIPE)
	{
		if (tmp->flag >= 11 && tmp->flag <= 13)
			if (ft_change_fd(s, tmp))
			{
				while (tmp && tmp->flag != REDIR_ARG)
					tmp = tmp->next;
				dup2(s->std.sin, 0);
				dup2(s->std.sout, 1);
				return (ft_redir_error(tmp->str));
			}
		tmp = tmp->next;
	}
	return (0);
}
