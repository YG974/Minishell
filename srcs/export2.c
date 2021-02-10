/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:23:26 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/09 14:38:42 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"
#include <string.h>

int		is_valid_env_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[0]) == 1)
			return (1);
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int		ft_strchr_int(const char *s, int c)
{
	int i;

	i = 0;
	c = (char)c;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}

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

void	modify_export_value(t_mini *s, char *name, char *str, int pos)
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
}

