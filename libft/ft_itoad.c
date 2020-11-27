/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:43:23 by pcoureau          #+#    #+#             */
/*   Updated: 2019/12/05 17:43:24 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

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

char				*ft_itoad(int n)
{
	unsigned char	*str;
	unsigned int	nb;
	unsigned int	size;

	nb = ft_abs(n);
	size = ft_size(nb) + 1;
	if (!(str = ft_calloc(sizeof(char), size)))
		return (0);
	str[size - 1] = '\0';
	if (n == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[size - 2] = nb % 10 + '0';
		nb /= 10;
		size--;
	}
	return ((char *)str);
}
