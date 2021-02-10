/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:21:44 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:21:47 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

char	*ft_without_quotes(char *s, int i, int j)
{
	int		len;
	char	*dest;

	len = ft_strlen(s);
	if (!(dest = ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	while (s[i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && (i == 0 || i == len - 1))
			i++;
		else
		{
			if (s[0] != '\'' && s[i] == '\\' && s[i + 1] &&
					(s[i + 1] == '\"' || s[i + 1] == '$' || s[i + 1] == '\\' ||
					s[i + 1] == '`' || s[i + 1] == '\n'))
			{
				i++;
				dest[j++] = s[i++];
			}
			else
				dest[j++] = s[i++];
		}
	}
	free(s);
	return (dest);
}

char	*ft_strdup_quotes(char *src, char *flagstr, char c)
{
	int		i;
	int		len;
	char	*dest;

	len = 0;
	i = 0;
	while (flagstr[len] && flagstr[len] == c)
		len++;
	len = ft_inc_i(src, src, 0, c);
	if (!(dest = ft_calloc(len, sizeof(char))))
		return (NULL);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_without_quotes(dest, 0, 0));
}

int		paco_mange_tes_morts(char *str, int i)
{
	i++;
	while (str[i] && str[i] != '\'')
		i++;
	i++;
	return (i);
}

int		extreme(char *str, int i)
{
	i++;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '\\')
			i++;
		i++;
	}
	i++;
	return (i);
}

int		ft_inc_i(char *str, char *flag, int i, char c)
{
	if (c == '1')
		return (paco_mange_tes_morts(str, i));
	else if (c == '2')
		return (extreme(str, i));
	if (str[i] == ' ')
	{
		while (str[i] && str[i] == ' ')
			i++;
		return (i);
	}
	if (str[i] && ft_ismeta(str[i]))
		i++;
	else
		while (str[i] && !ft_ismeta(str[i]) && flag[i] == '0')
			i++;
	return (i);
}
