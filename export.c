/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:38:47 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/09 14:41:04 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

int		is_valid_env_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[0]) == 1)
			return (0);
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char **put_sorted_env_in_tab(t_mini *s)
{
	t_env	*env;
	char	*env_str;
	char	**env_tab;

	env = s->env;
	env_str = strdup("");
	while (env)
	{
		env_str = ft_strjoin_free_s1(env_str, env->name);
		if (env->value)
		{
			env_str = ft_strjoin_free_s1(env_str, "=");
			env_str = ft_strjoin_free_s1(env_str, env->value);
		}
		env_str = ft_strjoin_free_s1(env_str, "\n");
		env = env->next;
	}
	env_tab = ft_split(env_str, '\n');
	free(env_str);
	return (env_tab);
}

char **sort_tab_env(char **s_env)
{
	char	*tmp;
	int		i;
	int		min;
	int		d;

	i = 1;
	min = 0;
	while (s_env[min])
	{
		while (s_env[i])
		{
			if ((d = ft_strncmp(s_env[min], s_env[i], SIZE_T_MAX)) < 0)
				i++;
			else
			{
				tmp = s_env[i];
				s_env[i] = s_env[min];
				s_env[min]= tmp;
			}
		}
		min++;
		i = min + 1;
	}
	return (s_env);
}

int		print_sorted_env(t_mini *s)
{
	char	**s_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s_env = put_sorted_env_in_tab(s);
	s_env = sort_tab_env(s_env);
	while (s_env[i])
	{
		ft_putstr_fd("declare -x ", s->std.out);
		while (s_env[i][j - 1] != '=' && s_env[i][j])
			write(s->std.out, &s_env[i][j++], 1);
		if (s_env[i][j])
		{
			write(s->std.out, "\"", 1);
			while (s_env[i][j])
				write(s->std.out, &s_env[i][j++], 1);
			write(s->std.out, "\"", 1);
		}
		write(s->std.out, "\n", 1);
		j = 0;
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

/*secure the return for the name of the env var without = */
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

	/*print_tab(s_env);*/
void	create_export_value(t_mini *s, char *name, char *str, int pos)
{
	t_env	*env;
	t_env	*tmp;
	int		len;

	env = s->env;
	len = ft_strlen(str);
	while (env->next)
		env = env->next;
	if (!(tmp = ft_calloc(1, sizeof(t_env))))
		return error(s, ERR_CALLOC);
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
