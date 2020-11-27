/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:38:34 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/20 15:55:29 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	*ft_starpi(char *tampostr, t_ftprintf *mas, int len)
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

/*
**void	*ft_ifnull(char *tampostr, t_ftprintf *mas, int len)
**{
**	if (!(tampostr = ft_strdup("(nil)")))
**		return (NULL);
**	len = 5;
**	if (mas->star < 0)
**	{
**		mas->star = mas->star * -1;
**		mas->l_align = 1;
**	}
**	if (!(ft_starpi(tampostr, mas, len)))
**		return (NULL);
**	return ("ok");
**}
*/

void	*ft_convp(va_list av, t_ftprintf *mas)
{
	char			*tampostr;
	int				len;
	unsigned long	pnum;

	tampostr = NULL;
	pnum = va_arg(av, unsigned long);
	len = 0;
	if (pnum == 0)
		return (ft_nn(tampostr, mas, len, pnum));
	else
		return (ft_nn(tampostr, mas, len, pnum));
}
