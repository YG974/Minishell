/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:21:06 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:21:08 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

int		is_char_set(int c, const char *char_set)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(char_set);
	while (i < len)
	{
		if (c == char_set[i])
			return (1);
		i++;
	}
	return (0);
}

int		ft_get_tokens(t_mini *s, t_cmdl *cmd)
{
	int		i;

	i = 0;
	(void)s;
	while (cmd->str[i] == ' ')
		i++;
	while (cmd->str[i])
	{
		if (cmd->str[i] == '\\')
		{
			if (ft_lit_char(cmd, i))
				return (ft_del_tokens(cmd, 1));
			i += 2;
		}
		else
		{
			if (ft_add_token(cmd, i))
				return (ft_del_tokens(cmd, 1));
			i = ft_inc_i(cmd->str, cmd->flag, i, cmd->flag[i]);
		}
	}
	return (0);
}

int		ft_ismeta(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int		ft_lit_char(t_cmdl *cmd, int i)
{
	t_tok	*tmp;
	t_tok	*current;

	if (!(tmp = ft_calloc(1, sizeof(t_tok))))
		return (1);
	tmp->flag = FLAG_LIT_CHAR;
	tmp->next = NULL;
	if (!cmd->firsttoken)
		cmd->firsttoken = tmp;
	else
	{
		current = cmd->firsttoken;
		while (current->next)
			current = current->next;
		current->next = tmp;
		tmp->prev = current;
	}
	if (!(tmp->str = ft_calloc(3, sizeof(char))))
		return (1);
	tmp->str[0] = '\\';
	tmp->str[1] = cmd->str[i + 1];
	tmp->str[3] = '\0';
	return (0);
}
