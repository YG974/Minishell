/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoau.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:43:23 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/20 13:48:14 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static unsigned int	ft_size(unsigned int n)
{
	unsigned int	size;

	size = 0;
	while (n / 10 > 0)
	{
		n /= 10;
		size++;
	}
	return (size + 1);
}

char				*ft_itoau(unsigned int n)
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
		str[size - 2] = n % 10 + '0';
		n /= 10;
		size--;
	}
	return ((char *)str);
}
