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

int		echo_flag_on(char *str)
{
	int i;

	i = 2;
	if (str[0] != '-')
		return (0);
	if (str[1] != 'n')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int		count_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int		ft_echo(t_mini *s, char **args)
{
	int		n_flag;
	int		i;
	int		nb;

	n_flag = 0;
	i = 1;
	if ((nb = count_args(args)) > 1)
	{
		while (args[i] && echo_flag_on(args[i]))
		{
			n_flag = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], s->std.out);
			i++;
			if (args[i])
				ft_putstr_fd(" ", s->std.out);
		}
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", s->std.out);
	return (0);
}

int		go_to_path(t_mini *s, char *args)
{
	int		i;

	(void)s;
	i = chdir(args);
	if (i != 0)
	{
		ft_putstr_fd(RED, STDERR);
		ft_putstr_fd("Minishell: cd: ", STDERR);
		ft_putstr_fd(args, STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(strerror(errno), STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd(RESET, STDERR);
	}
	if (i < 0)
		i = -i;
	return (i);
}

int		go_to_home_path(t_mini *s)
{
	char	*path;
	char	*buf;
	int		i;

	path = NULL;
	buf = NULL;
	buf = ft_strdup("HOME");
	path = get_env_value(s, buf);
	if ((i = ft_strlen(path)) == 0)
	{
		cd_str_error(path, 1);
		return (1);
	}
	i = chdir(path);
	if (i != 0)
		cd_str_error(path, 2);
	if (path)
		free(path);
	return (-i);
}
