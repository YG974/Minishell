/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:16:03 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:33:18 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"
#include <string.h>

int		is_in_env(t_mini *s, char *str)
{
	t_env	*env;
	int		len;

	env = s->env;
	len = ft_strlen(str);
	while (env)
	{
		if (ft_strncmp(env->name, str, len) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

/*
**	secure the return for the name of the env var without =
*/

char	*get_name(char *str)
{
	int		pos;
	char	*tmp;

	pos = ft_strchr_int(str, '=');
	if (pos < 0)
		tmp = ft_strdup(str);
	else
		tmp = ft_strdup_size(str, pos, 0);
	return (tmp);
}

void	ct_export_value(t_mini *s, char *name, char *str, int pos)
{
	t_env	*env;
	t_env	*tmp;
	int		len;

	env = s->env;
	len = ft_strlen(str);
	while (env->next)
		env = env->next;
	if (!(tmp = ft_calloc(1, sizeof(t_env))))
		return (error(s, ERR_CALLOC));
	tmp->name = name;
	if (pos < 0)
		tmp->value = NULL;
	else
	{
		if (pos == ft_strlen(str))
			tmp->value = ft_strdup("");
		else
			tmp->value = ft_strdup_size(str, len, pos + 1);
	}
	env->next = tmp;
	tmp->next = NULL;
	return ;
}

void	md_export_value(t_mini *s, char *name, char *str, int pos)
{
	t_env	*env;
	int		len;

	env = s->env;
	len = ft_strlen(str);
	while (env)
	{
		if (ft_strncmp(env->name, name, len) == 0)
		{
			if (pos < 0)
				return ;
			else
			{
				if (env->value)
					free(env->value);
				if (pos == ft_strlen(str))
					env->value = ft_strdup("");
				else
					env->value = ft_strdup_size(str, len, pos + 1);
			}
		}
		env = env->next;
	}
	free(name);
}

void	export_assignement(t_mini *s, char *str)
{
	char	*tmp;
	int		pos;

	pos = ft_strchr_int(str, '=');
	tmp = get_name(str);
	if (is_in_env(s, tmp) == 0)
		ct_export_value(s, tmp, str, pos);
	else
	{
		if (pos < 0)
			return ;
		else if (pos == ft_strlen(str))
			md_export_value(s, tmp, str, pos);
		else
			md_export_value(s, tmp, str, pos);
	}
}
