/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:38:34 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/20 15:54:14 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_printsc(t_ftprintf *mas)
{
	mas->strlenfinal = mas->strlenfinal + ft_putstr_p(mas->s, 1);
	free(mas->s);
}

void	*ft_convc_ii(va_list av, t_ftprintf *mas)
{
	if (mas->star < 0)
	{
		mas->star = mas->star * -1;
		mas->l_align = 1;
	}
	if (!(mas->s = malloc(sizeof(char) * (mas->star + 1))))
		return (NULL);
	ft_memset(mas->s, ' ', mas->star);
	mas->s[mas->star - 1] = '\0';
	if (mas->l_align || mas->star == 0)
	{
		ft_putchar_fd(va_arg(av, int), 1);
		ft_printsc(mas);
	}
	else
	{
		ft_printsc(mas);
		ft_putchar_fd(va_arg(av, int), 1);
	}
	return ("ok");
}

void	*ft_convc(va_list av, t_ftprintf *mas)
{
	if (mas->star_activ && mas->star != 0)
	{
		if (!(ft_convc_ii(av, mas)))
			return (NULL);
	}
	else
	{
		if (!(mas->s = malloc(sizeof(char) * 2)))
			return (NULL);
		mas->s[0] = va_arg(av, int);
		mas->s[1] = '\0';
		ft_putchar_fd(mas->s[0], 1);
		free(mas->s);
	}
	mas->strlenfinal++;
	return ("ok");
}
