/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 21:26:56 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/20 13:31:40 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_initstructflags(t_ftprintf *mas)
{
	mas->l_align = 0;
	mas->star = 0;
	mas->star_activ = 0;
	mas->zero = 0;
	mas->zero_activ = 0;
	mas->dot = 0;
	mas->dot_activ = 0;
	mas->neg = 0;
	mas->len = 0;
}

void	ft_prints(t_ftprintf *mas)
{
	mas->strlenfinal = mas->strlenfinal + ft_putstr_p(mas->s, 1);
	free(mas->s);
	mas->s = NULL;
}

void	*ft_putstrins(int start, int end, const char *str, t_ftprintf *mas)
{
	int	i;

	i = 0;
	if (!(mas->s = malloc(sizeof(char) * (end - start))))
	{
		free(mas->str_final);
		return (NULL);
	}
	while (start != end)
	{
		mas->s[i] = str[start];
		i++;
		start++;
	}
	mas->s[i] = '\0';
	ft_prints(mas);
	return ("ok");
}

int		ft_putargins(va_list av, t_ftprintf *mas, const char *str)
{
	int n;

	n = 0;
	if ((n = ft_chkflgs(av, mas, str, n)) < 0)
		return (-1);
	if (str[n] == 'c')
	{
		if (!(ft_convc(av, mas)))
			return (-1);
		else
			return (n + 1);
	}
	else if (str[n] == '\0' || (str[n] != 's' && str[n] != 'p'
			&& str[n] != 'd' && str[n] != 'i' && str[n] != 'u' && str[n] != 'x'
			&& str[n] != 'X' && str[n] != '%'))
		return (-1);
	if (!(ft_cnvrt(av, mas, str, n)))
		return (-1);
	else if (str[n] != 'd' && str[n] != 'i')
		ft_prints(mas);
	n++;
	return (n);
}

void	*ft_getstr(const char *str, t_ftprintf *mas, va_list av)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (!(ft_putstrins(j, i, str, mas)))
				return (NULL);
			i++;
			if ((n = ft_putargins(av, mas, str + i)) < 0)
				return (NULL);
			ft_initstructflags(mas);
			i = i + n;
			j = i;
		}
		else
			i++;
	}
	if (!(ft_putstrins(j, i, str, mas)))
		return (NULL);
	return ("ok");
}
