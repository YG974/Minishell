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

	i = count_args(args);
	if (i == 1)
		return (go_to_home_path(s));
	else
		return (go_to_path(s, args[1]));
}

int		ft_pwd(t_mini *s, char **args)
{
	char *cwd;

	(void)s;
	(void)args;
	if (!(cwd = ft_calloc(PATH_MAX, sizeof(char))))
		return (1);
	cwd = getcwd(cwd, PATH_MAX);
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
	if (str[i] == '=' || str[i] == '\0')
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

int		print_sorted_env(t_mini *s, int i, int j)
{
	char	**s_env;

	s_env = put_sorted_env_in_tab(s);
	s_env = sort_tab_env(s_env);
	while (s_env[i])
	{
		ft_putstr_fd("declare -x ", s->std.out);
		while (s_env[i][j - 1] != '=' && s_env[i][j])
			write(s->std.out, &s_env[i][j++], 1);
		if (s_env[i][j - 1] == '=')
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
	ft_free_tab(s_env);
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
