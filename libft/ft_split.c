/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:50:15 by ygeslin           #+#    #+#             */
/*   Updated: 2019/10/20 22:17:03 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_tab(char **tab)
{
	int n;

	n = 0;
	while (tab[n])
		free(tab[n++]);
	free(tab);
	return (NULL);
}

static char	**new_tab(char **tab, char *str)
{
	char	**new_tab;
	int		n;

	n = 0;
	while (tab[n])
		n++;
	if (!(new_tab = calloc(sizeof(char **), n + 2)))
		return (NULL);
	n = 0;
	while (tab[n])
	{
		new_tab[n] = tab[n];
		n++;
	}
	free(tab);
	new_tab[n] = str;
	new_tab[n + 1] = NULL;
	return (new_tab);
}

static char	*get_str(const char *s, size_t *i, char c)
{
	char	*str;
	size_t	n;

	n = 0;
	while (s[*i + n] && s[*i + n] != c)
		n++;
	if (!(str = ft_calloc(sizeof(char), n + 1)))
		return (NULL);
	n = 0;
	while (s[*i + n] && s[*i + n] != c)
	{
		str[n] = s[*i + n];
		n++;
	}
	str[n] = '\0';
	*i = *i + n;
	return (str);
}

char		**ft_split(char const *s, char c)
{
	char		**tab;
	char		*str;
	size_t		i;

	if (!s || !(tab = ft_calloc(sizeof(char **), 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			if (!(str = get_str(s, &i, c)))
				return (free_tab(tab));
			tab = new_tab(tab, str);
		}
	}
	return (tab);
}
