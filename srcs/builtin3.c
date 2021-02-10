/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                          :+:      :+:    :+:  */
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

int		ft_export(t_mini *s, char **args)
{
	int		i;
	int		ret;

	i = 1;
	if ((ret = count_args(args)) == 1)
		return (print_sorted_env(s));
	while (args[i])
	{
		if (!(ret = is_valid_env_name(args[i])))
			error(s, ERR_INVALID_ENV_NAME);
		else
			export_assignement(s, args[i]);
		i++;
	}
	return (ret);
}

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
