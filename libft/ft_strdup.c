/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:09:07 by ygeslin           #+#    #+#             */
/*   Updated: 2019/10/17 10:45:16 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int i;

	i = 0;
	if (src == NULL)
		return (dest);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		*ft_strdup(const char *src)
{
	char	*dest;

	if (src == NULL)
	{
		dest = NULL;
		return (dest);
	}
	dest = (char*)malloc(sizeof(*src) * (ft_strlen(src) + 1));
	if (dest == NULL)
		return (dest);
	dest = ft_strcpy(dest, src);
	return (dest);
}
