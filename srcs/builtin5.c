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
