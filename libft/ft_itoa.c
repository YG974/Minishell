/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:44:48 by ygeslin           #+#    #+#             */
/*   Updated: 2019/10/16 16:27:06 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_abs(int n)
{
	return ((unsigned int)(n < 0 ? -n : n));
}

static unsigned int	ft_size(unsigned int n)
{
	unsigned int size;

	size = 0;
	n = ft_abs(n);
	while (n / 10 > 0)
	{
		n /= 10;
		size++;
	}
	return (size + 1);
}

char				*ft_itoa(int n)
{
	unsigned char	*str;
	unsigned int	nb;
	unsigned int	size;

	nb = ft_abs(n);
	size = ft_size(nb) + 1 + (n < 0 ? 1 : 0);
	if (!(str = ft_calloc(sizeof(char), size)))
		return (0);
	str[size - 1] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
	}
	while (nb > 0)
	{
		str[size - 2] = nb % 10 + '0';
		nb /= 10;
		size--;
	}
	return ((char *)str);
}
