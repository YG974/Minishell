/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkflags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:38:34 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/20 16:08:37 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_chkflgs_ii(t_ftprintf *mas, const char *str, int n)
{
	if (str[n] == '-')
		n = ft_flagalign(mas, str, n);
	else if (str[n] == '0')
		n = ft_flagzero(mas, str, n);
	return (n);
}

int	ft_chkflgs(va_list av, t_ftprintf *mas, const char *str, int n)
{
	while (1)
	{
		if (str[n] == '-' || str[n] == '0')
			n = ft_chkflgs_ii(mas, str, n);
		else
			break ;
	}
	while (1)
	{
		if (str[n] >= '1' && str[n] <= '9')
			n = ft_flagwn(mas, str, n);
		if (str[n] == '*')
			n = ft_flagws(av, mas, str, n);
		else
			break ;
	}
	while (1)
	{
		if (str[n] == '.')
			n = ft_flagdot(av, mas, str, n);
		else
			break ;
	}
	return (n);
}
