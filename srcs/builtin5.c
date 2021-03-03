/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:12:40 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:14:01 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"
#include <string.h>

/*
**	si on veut peaufiner, bien checker a verifier si un seul argument, et que
**	cest un nombre, dans ce cas, return ce nombre, sinon renvoyer de dernier
**	retour cmd->ret
**	Dans le sujet c'est ecrit, sans option, mais pas sans argument.
*/

int		ft_exit(t_mini *s, char **args)
{
	int		i;

	(void)s;
	i = count_args(args);
	if (i == 1)
		return (0);
	if (i > 2)
	{
		ft_putstr_fd(RED, STDERR);
		ft_putstr_fd(args[0], STDERR);
		ft_putstr_fd(": too many arguments\n", STDERR);
		ft_putstr_fd(RESET, STDERR);
		return (1);
	}
	if (i == 2 && !(i = str_is_digit(args[1])))
	{
		ft_putstr_fd(RED, STDERR);
		ft_putstr_fd(args[0], STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR);
		ft_putstr_fd(RESET, STDERR);
		return (1);
	}
	return (2);
}

char	**put_sorted_env_in_tab(t_mini *s)
{
	t_env	*env;
	char	*env_str;
	char	**env_tab;

	env = s->env;
	env_str = strdup("");
	while (env)
	{
		env_str = ft_strjoin_free_s1_s2(env_str, ft_strdup(env->name));
		if (env->value)
		{
			env_str = ft_strjoin_free_s1(env_str, "=");
			env_str = ft_strjoin_free_s1_s2(env_str, ft_strdup(env->value));
		}
		env_str = ft_strjoin_free_s1(env_str, "\n");
		env = env->next;
	}
	env_tab = ft_split(env_str, '\n');
	free(env_str);
	return (env_tab);
}

char	**sort_tab_env(char **s_env)
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
				s_env[min] = tmp;
			}
		}
		min++;
		i = min + 1;
	}
	return (s_env);
}

void	cd_str_error(char *s1, int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd(RED, STDERR);
		ft_putstr_fd("Minishell: cd: ", STDERR);
		ft_putstr_fd("HOME not set\n", 2);
		ft_putstr_fd(RESET, STDERR);
	}
	if (flag == 2)
	{
		ft_putstr_fd(RED, STDERR);
		ft_putstr_fd("Minishell: cd: ", STDERR);
		ft_putstr_fd(strerror(errno), STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd(RESET, STDERR);
	}
	free(s1);
}

int		is_valid_env_name_unset(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '=' || str[i] == '\0')
		return (0);
	if (ft_strchr_int(str, '=') != -1)
		return (0);
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
