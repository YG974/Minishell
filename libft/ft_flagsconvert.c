/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagsconvert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:38:34 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/20 13:56:43 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_flagalign(t_ftprintf *mas, const char *str, int n)
{
	mas->l_align = 1;
	while (str[n] == '-')
		n++;
	return (n);
}

int	ft_flagzero(t_ftprintf *mas, const char *str, int n)
{
	mas->zero_activ = 1;
	while (str[n] == '0')
		n++;
	return (n);
}

int	ft_flagwn(t_ftprintf *mas, const char *str, int n)
{
	if (mas->star_activ == 1)
		return (-1);
	mas->star_activ = 1;
	mas->star = ft_atoi(str + n);
	while (ft_isdigit(str[n]))
		n++;
	return (n);
}

int	ft_flagws(va_list av, t_ftprintf *mas, const char *str, int n)
{
	if (mas->star_activ == 1)
		return (-1);
	mas->star_activ = 1;
	mas->star = va_arg(av, int);
	while (str[n] == '*')
		n++;
	return (n);
}

int	ft_flagdot(va_list av, t_ftprintf *mas, const char *str, int n)
{
	if (mas->dot_activ == 1)
		return (-1);
	mas->dot_activ = 1;
	while (str[n] == '.')
		n++;
	if (str[n] == '*')
	{
		mas->dot = va_arg(av, int);
		n++;
	}
	else if (str[n] >= '0' && str[n] <= '9')
	{
		mas->dot = ft_atoi(str + n);
		while (ft_isdigit(str[n]))
			n++;
	}
	return (n);
}
