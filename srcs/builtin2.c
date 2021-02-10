/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:15:26 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:15:32 by pcoureau         ###   ########.fr       */
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

int		print_sorted_env(t_mini *s)
{
	t_env	*env;

	env = s->env;
	ft_printf("sorted env\n");
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
