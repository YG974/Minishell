/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:06:22 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/20 13:33:48 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	*ft_initializestruct(t_ftprintf *mas)
{
	if (!(mas->str_final = malloc(sizeof(char) * 1)))
		return (NULL);
	mas->str_final[0] = '\0';
	mas->l_align = 0;
	mas->star = 0;
	mas->star_activ = 0;
	mas->zero = 0;
	mas->zero_activ = 0;
	mas->dot = 0;
	mas->dot_activ = 0;
	mas->neg = 0;
	mas->strlenfinal = 0;
	return ("ok");
}

int		ft_printf(const char *str, ...)
{
	va_list		av;
	t_ftprintf	mas;

	va_start(av, str);
	if (!str || !(ft_initializestruct(&mas)))
		return (-1);
	if (!(ft_getstr(str, &mas, av)))
	{
		if (mas.str_final)
			free(mas.str_final);
		return (-1);
	}
	free(mas.str_final);
	va_end(av);
	return (mas.strlenfinal);
}
