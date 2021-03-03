/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:15:47 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:15:54 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"
#include <string.h>

int		ft_export(t_mini *s, char **args)
{
	int		i;
	int		ret;

	i = 1;
	if ((ret = count_args(args)) == 1)
		return (print_sorted_env(s, 0, 0));
	ret = 0;
	while (args[i])
	{
		if ((is_valid_env_name(args[i])) == 0)
		{
			ret++;
			export_error(args[i]);
		}
		else
			export_assignement(s, args[i]);
		i++;
	}
	if (ret > 0)
		ret = 1;
	return (ret);
}

void	unset_value(t_mini *s, char *args)
{
	t_env	*env;
	t_env	*tmp;
	int		len;

	env = s->env;
	len = ft_strlen(args);
	while (env->next)
	{
		if (ft_strncmp(env->next->name, args, len) == 0)
		{
			tmp = env->next->next;
			free(env->next->name);
			free(env->next->value);
			free(env->next);
			env->next = tmp;
			return ;
		}
		env = env->next;
	}
}

int		ft_unset(t_mini *s, char **args)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	while (args[i])
	{
		if ((is_valid_env_name_unset(args[i])) == 0)
		{
			ret++;
			ft_putstr_fd(RED, STDERR);
			ft_putstr_fd("Minishell: unset: \"", STDERR);
			ft_putstr_fd(args[i], STDERR);
			ft_putstr_fd("\" not a valid identifier\n", STDERR);
			ft_putstr_fd(RESET, STDERR);
		}
		else
			unset_value(s, args[i]);
		i++;
	}
	if (ret > 0)
		ret = 1;
	return (ret);
}

int		ft_env(t_mini *s, char **args)
{
	int		i;
	t_env	*env;

	env = s->env;
	if ((i = count_args(args)) > 1)
	{
		ft_putstr_fd("Error: flag or argument forbidden with env command .\n",
				s->std.err);
		return (1);
	}
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->name, s->std.out);
			ft_putstr_fd("=", s->std.out);
			ft_putstr_fd(env->value, s->std.out);
			ft_putstr_fd("\n", s->std.out);
		}
		env = env->next;
	}
	return (0);
}

int		str_is_digit(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
