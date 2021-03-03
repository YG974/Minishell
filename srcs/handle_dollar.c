/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:53:01 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 10:53:03 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

char	*replace_tab_by_space(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
	return (str);
}

t_tok	*new_dollar_tok(t_mini *s, char *str, int flag)
{
	t_tok	*new;

	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	new->str = ft_strdup(str);
	if (flag == 0)
		new->flag = T_WORD;
	if (flag != 0)
		new->flag = BLANK;
	return (new);
}

t_tok	*split_dollar_token(t_mini *s, char *str, t_tok *prev, t_tok *next)
{
	char	**tab;
	int		i;
	t_tok	*new;
	t_tok	*tmp;

	new = NULL;
	i = 0;
	str = replace_tab_by_space(str);
	tab = ft_split(str, ' ');
	free(str);
	new = new_dollar_tok(s, tab[i], 0);
	link_token(s, prev, new);
	i++;
	while (tab[i])
	{
		tmp = new_dollar_tok(s, " ", 1);
		link_token(s, new, tmp);
		new = new_dollar_tok(s, tab[i], 0);
		link_token(s, tmp, new);
		i++;
	}
	ft_free_tab(tab);
	new->next = next;
	return (new);
}

/*
**	replace the env names ($NAME) in the input by their values in cmd->buf
*/

void	expand_dollars(t_mini *s, t_cmdl *cmd)
{
	char	*tmp;

	cmd->token = cmd->firsttoken;
	while (cmd->token)
	{
		if (cmd->token->flag == T_DOLLAR)
		{
			tmp = ft_strdup_size(cmd->token->str,
					ft_strlen(cmd->token->str), 1);
			tmp = get_env_value(s, tmp);
			free(cmd->token->str);
			if (ft_strchr_int(tmp, ' ') == -1)
				cmd->token->str = tmp;
			else
			{
				free(cmd->token);
				cmd->token = split_dollar_token(s, tmp,
					cmd->token->prev, cmd->token->next);
			}
			cmd->token->flag = T_WORD;
		}
		cmd->token = cmd->token->next;
	}
	cmd->token = cmd->firsttoken;
}

/*
** itinerate the string and put the flag 4 on var names followings '$' char
** FLAG = 4 --> not escaped VARIABLE NAME
*/

void	check_dollars(t_mini *s, t_parse *p)
{
	s->i = 0;
	while (p->str[s->i])
	{
		if (p->str[s->i] == '$' && p->flag[s->i] != '1'
				&& p->str[s->i - 1] != '\\')
		{
			p->flag[s->i++] = '4';
			if (p->str[s->i] == '?')
			{
				p->flag[s->i++] = '4';
				break ;
			}
			while (p->str[s->i]
					&& (ft_isalnum(p->str[s->i]) || p->str[s->i] == '_'))
				p->flag[s->i++] = '4';
		}
		else
			s->i++;
	}
}
