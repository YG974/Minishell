/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convd_ii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 19:38:27 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/26 19:38:55 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_printd_m(t_ftprintf *mas)
{
	ft_putchar_fd('-', 1);
	mas->strlenfinal++;
}

void	ft_printd_dot(int i, t_ftprintf *mas)
{
	int j;

	j = 0;
	while (j < i)
	{
		ft_putchar_fd('0', 1);
		j++;
	}
	mas->strlenfinal = mas->strlenfinal + i;
	mas->len = mas->len + i;
}

void	ft_printd_tmps(char *tampostr, t_ftprintf *mas)
{
	ft_putstr_fd(tampostr, 1);
	mas->strlenfinal = mas->strlenfinal + ft_strlen(tampostr);
}

void	ft_printd_star(int i, t_ftprintf *mas)
{
	int j;

	j = 0;
	while (j < i)
	{
		if (mas->zero_activ)
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd(' ', 1);
		j++;
	}
	mas->strlenfinal = mas->strlenfinal + i;
	mas->len = mas->len + i;
}
