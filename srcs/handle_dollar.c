/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:53:01 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 10:53:03 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

/*
**	cmd->str = command line;
**	cmd->flag = flags or comments;
**	cmd->str[i] = char i of the line;
**	cmd->flag[i] = flags or comments on char i;
**	flags :
**	1 : inside simpled quotes
**	2 : inside double quotes
**	3 : escaped by backslash
**	4 : dollar expansion
**
**	look for name variable in env
**	if variable name is found, return its value
**	if name is not found, return empty string ""
*/

char	*get_env_value(t_mini *s, char *name)
{
	char	*value;
	t_env	*env;
	int		i;

	value = NULL;
	env = s->env;
	i = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(env->name, name, i) == 0 && i == ft_strlen(env->name))
			value = ft_strdup(env->value);
		env = env->next;
	}
	if (value == NULL)
		value = ft_strdup("");
	free(name);
	return (value);
}

/*
**	replace the env names ($NAME) in the input by their values in cmd->buf
*/

void	expand_dollars(t_mini *s, t_parse *p, int i, int j)
{
	char	*tmp;

	p->buf = ft_strdup("");
	while (p->str[i])
	{
		i = i + j;
		j = 0;
		if (p->flag[i] == '4')
		{
			while (p->flag[i + j] == '4' && p->str[i + j])
				j++;
			tmp = ft_strdup_size(p->str, i + j, i);
			tmp = get_env_value(s, tmp);
			p->buf = ft_strjoin_free_s1_s2(p->buf, tmp);
		}
		else
		{
			while (p->flag[i + j] != '4' && p->str[i + j])
				j++;
			tmp = ft_strdup_size(p->str, i + j - 1, i);
			p->buf = ft_strjoin_free_s1_s2(p->buf, tmp);
		}
	}
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
			s->i++;
			while (p->str[s->i]
					&& (ft_isalnum(p->str[s->i]) || p->str[s->i] == '_'))
				p->flag[s->i++] = '4';
		}
		else
			s->i++;
	}
}
