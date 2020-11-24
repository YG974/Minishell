/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:08:51 by ygeslin           #+#    #+#             */
/*   Updated: 2019/10/17 20:32:42 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_ischarset(char c, const char *charset)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(charset);
	while (i < len)
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int		start_count(char const *s1, char const *set)
{
	int i;

	i = 0;
	while (ft_ischarset(s1[i], set))
		i++;
	return (i);
}

static int		end_count(char const *s1, char const *set)
{
	int i;

	i = ft_strlen(s1) - 1;
	while (ft_ischarset(s1[i], set) && i > 0)
		i--;
	return (i);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		tab_size;
	int		i;
	char	*tab;

	if (!(s1 && set))
		return (NULL);
	i = end_count(s1, set);
	tab_size = i - start_count(s1, set) + 1;
	if (tab_size < 0)
		tab_size = 0;
	if (!(tab = ft_calloc(sizeof(char) * (tab_size + 1), 1)))
		return (NULL);
	tab[tab_size] = '\0';
	while (tab_size > 0)
	{
		tab[tab_size - 1] = s1[i];
		tab_size--;
		i--;
	}
	return (tab);
}
