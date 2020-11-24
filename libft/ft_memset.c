/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:27:12 by ygeslin           #+#    #+#             */
/*   Updated: 2019/10/20 22:33:21 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *ptr, int c, size_t n)
{
	unsigned char *tmp;

	tmp = (unsigned char *)ptr;
	while (n > 0)
	{
		tmp[n - 1] = c;
		n--;
	}
	return (ptr);
}
