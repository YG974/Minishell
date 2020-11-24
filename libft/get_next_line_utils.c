/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:03:40 by ygeslin           #+#    #+#             */
/*   Updated: 2019/11/21 16:41:43 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strchrgnl(const char *s, int c)
{
	int i;

	i = 0;
	c = (char)c;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}

char		*ft_strjoingnl_endl(char *s1, const char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*str;

	len1 = (s1 == NULL ? 0 : ft_strlengnl(s1));
	len2 = (ft_strchrgnl(s2, ENDL) == -1 ? ft_strlengnl(s2) :
			ft_strchrgnl(s2, ENDL));
	i = 0;
	if (!(str = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

char		*ft_strjoingnl(char *s1, const char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*str;

	len1 = (s1 == NULL ? 0 : ft_strlengnl(s1));
	len2 = ft_strlengnl(s2);
	i = 0;
	if (!(str = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[len1 + len2] = '\0';
	free(s1);
	return (str);
}

int			ft_strlengnl(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
