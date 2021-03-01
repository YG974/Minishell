/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
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
** check if name variable contains only letters, numbers, underscores "_"
**and don't begin with numbers
*/

char	*ft_strjoin_free_s2(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*str;

	if (!(s2 && s1))
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	if (!(str = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[len1 + len2] = '\0';
	free((void *)s2);
	return (str);
}

char	*ft_strjoin_free_s1(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*str;

	if (!(s2 && s1))
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	if (!(str = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[len1 + len2] = '\0';
	free((void *)s1);
	return (str);
}

char	**put_env_in_tab(t_mini *s)
{
	t_env	*env;
	char	*env_str;
	char	**env_tab;

	env = s->env;
	env_str = strdup("");
	while (env)
	{
		if (env->value)
		{
			env_str = ft_strjoin_free_s1((env_str), (env->name));
			env_str = ft_strjoin_free_s1((env_str), ("="));
			env_str = ft_strjoin_free_s1((env_str), (env->value));
			env_str = ft_strjoin_free_s1((env_str), ("\n"));
		}
		env = env->next;
	}
	env_tab = ft_split(env_str, '\n');
	free(env_str);
	return (env_tab);
}

void	check_env_variable_name(t_mini *s)
{
	t_env	*env;
	int		i;

	env = s->env;
	while (env && env->next)
	{
		i = 0;
		while (env->name[i])
		{
			if (ft_isdigit(env->name[0]) == 1)
				error(s, ERR_INVALID_ENV_NAME);
			if (ft_isalnum(env->name[i]) == 0 && env->name[i] != '_')
				error(s, ERR_INVALID_ENV_NAME);
			i++;
		}
		env = env->next;
	}
}

/*
** split name and value into env->name and env->value, deleting the "=".
** if value is empty, replace by ""(empty string) and not NULL Char
*/

void	split_env_value(t_mini *s)
{
	t_env	*env;
	char	*tmp;
	int		pos;

	env = s->env;
	while (env)
	{
		tmp = ft_strdup(env->value);
		free(env->value);
		pos = ft_strchrgnl(tmp, '=');
		env->name = ft_strdup_size(tmp, pos, 0);
		env->value = ft_strdup_size(tmp, ft_strlen(tmp), pos + 1);
		if (env->value == NULL)
			env->value = ft_strdup("");
		free(tmp);
		env = env->next;
	}
}
