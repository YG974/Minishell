/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
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

int		ft_cd(t_mini *s, char **args)
{
	int		i;

	(void)s;
	i = count_args(args);
	if (i == 1)
		return (go_to_home_path(s));
	else
		return (go_to_path(s, args));
}

int		ft_pwd(t_mini *s, char **args)
{
	char *cwd;

	(void)s;
	cwd = ft_calloc(PATH_MAX, sizeof(char));
	if (!cwd)
	{
		error(s, ERR_CALLOC);
		return (1);
	}
	cwd = getcwd(args[1], PATH_MAX);
	if (!cwd)
	{
		ft_putstr_fd(RED, STDERR);
		ft_putstr_fd(strerror(errno), STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd(RESET, STDERR);
		return (1);
	}
	ft_putstr_fd(cwd, s->std.out);
	ft_putstr_fd("\n", s->std.out);
	free(cwd);
	return (0);
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
		if ((is_valid_env_name(args[i])) == 1)
		{
			ret++;
			ft_putstr_fd(RED, STDERR);
			ft_putstr_fd("Minishell: unset: ", STDERR);
			ft_putstr_fd(args[i], STDERR);
			ft_putstr_fd(" not a valid identifier\n", STDERR);
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
