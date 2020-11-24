/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:00:08 by ygeslin           #+#    #+#             */
/*   Updated: 2019/10/17 20:25:27 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t i;
	size_t pos;

	i = 0;
	if (to_find[i] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i <= n)
	{
		pos = 0;
		if (str[i] == to_find[pos])
			while (str[i + pos] == to_find[pos] && i + pos < n)
			{
				if (to_find[pos + 1] == '\0')
					return ((char *)&str[i]);
				pos++;
			}
		i++;
	}
	return (NULL);
}
