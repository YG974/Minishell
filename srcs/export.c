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

void	export_assignement(t_mini *s, char *str)
{
	char	*tmp;
	int		pos;

	pos = ft_strchr_int(str, '=');
	tmp = get_name(str);
	if (is_in_env(s, tmp) == 0)
	{
		if (pos < 0)
			return ;
		else if (pos == ft_strlen(str))
			create_export_value(s, tmp, str, pos);
		else
			create_export_value(s, tmp, str, pos);
	}
	else
	{
		if (pos < 0)
			return ;
		else if (pos == ft_strlen(str))
			modify_export_value(s, tmp, str, pos);
		else
			modify_export_value(s, tmp, str, pos);
	}
}

