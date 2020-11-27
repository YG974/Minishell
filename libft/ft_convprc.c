/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convprc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:12:53 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/21 15:11:32 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	*ft_starprc_ii(t_ftprintf *mas, char *tampospace, int len)
{
	if (!(tampospace = malloc(sizeof(char) * (mas->star + 1 - len))))
		return (NULL);
	tampospace[mas->star - len] = '\0';
	if (mas->zero_activ)
		ft_memset(tampospace, '0', mas->star - len);
	else
		ft_memset(tampospace, ' ', mas->star - len);
	return (tampospace);
}

void	*ft_starprc(t_ftprintf *mas, int len, char *tampostr)
{
	char *tampospace;

	tampospace = NULL;
	if (mas->star_activ && mas->star != 0 && mas->star > len)
	{
		if (mas->star > len)
			if (!(tampospace = ft_starprc_ii(mas, tampospace, len)))
				return (NULL);
		if (!(mas->s = ft_joina(tampostr, tampospace, mas)))
			return (NULL);
	}
	else
	{
		mas->s = ft_strdup(tampostr);
		free(tampostr);
		if (!mas->s)
			return (NULL);
	}
	return ("ok");
}

void	*ft_convprc(t_ftprintf *mas)
{
	char	*tampostr;
	int		len;

	if (!(tampostr = malloc(sizeof(char) * 2)))
		return (NULL);
	tampostr[0] = '%';
	tampostr[1] = '\0';
	if (mas->l_align || mas->star < 0)
		mas->zero_activ = 0;
	len = ft_strlen(tampostr);
	if (mas->star < 0)
	{
		mas->star = mas->star * -1;
		mas->l_align = 1;
	}
	return (ft_starprc(mas, len, tampostr));
}
