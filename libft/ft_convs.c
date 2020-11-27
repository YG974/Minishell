/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:38:34 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/20 15:52:38 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	*ft_stars(t_ftprintf *mas, char *tampostr, int len)
{
	char *tampospace;

	tampospace = NULL;
	if (mas->star_activ && mas->star != 0 && mas->star > len)
	{
		if (mas->star > len)
		{
			if (!(tampospace = malloc(sizeof(char) * (mas->star + 1 - len))))
				return (NULL);
			tampospace[mas->star - len] = '\0';
			ft_memset(tampospace, ' ', mas->star - len);
		}
		if (!(mas->s = ft_joina(tampostr, tampospace, mas)))
			return (NULL);
	}
	else
	{
		(mas->s = ft_strdup(tampostr));
		free(tampostr);
		if (!mas->s)
			return (NULL);
	}
	return ("ok");
}

void	*ft_convs(va_list av, t_ftprintf *mas)
{
	char	*tampostr;
	int		len;

	if (!(tampostr = ft_strdup(va_arg(av, char*))))
		if (!(tampostr = ft_strdup("(null)")))
			return (NULL);
	len = ft_strlen(tampostr);
	if (mas->dot_activ && mas->dot < len && mas->dot >= 0)
	{
		len = mas->dot;
		tampostr[mas->dot] = '\0';
	}
	if (mas->star < 0)
	{
		mas->star = mas->star * -1;
		mas->l_align = 1;
	}
	if (!(ft_stars(mas, tampostr, len)))
		return (NULL);
	return ("ok");
}
