/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoax.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:43:23 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/20 13:47:40 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static unsigned int	ft_size(unsigned int n)
{
	unsigned int	size;

	size = 0;
	while (n / 16 > 0)
	{
		n /= 16;
		size++;
	}
	return (size + 1);
}

char				*ft_itoax(unsigned int n, char *base)
{
	unsigned char	*str;
	unsigned int	size;

	size = ft_size(n) + 1;
	if (!(str = ft_calloc(sizeof(char), size)))
		return (0);
	str[size - 1] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[size - 2] = base[n % 16];
		n /= 16;
		size--;
	}
	return ((char *)str);
}
