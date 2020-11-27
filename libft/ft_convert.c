/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:37:42 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/21 15:12:05 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_joina(char *tampostr, char *tampospace, t_ftprintf *mas)
{
	char *dest;

	if (mas->l_align == 0)
		dest = ft_strjoin(tampospace, tampostr);
	else
		dest = ft_strjoin(tampostr, tampospace);
	free(tampospace);
	free(tampostr);
	if (!dest)
		return (NULL);
	else
		return (dest);
}

void	*ft_cnvrt(va_list av, t_ftprintf *mas, const char *str, int n)
{
	void *(*tabft[256])(va_list, t_ftprintf*);

	if (str[n] == '%')
	{
		if (!(ft_convprc(mas)))
			return (NULL);
		return ("ok");
	}
	tabft['c'] = ft_convc;
	tabft['s'] = ft_convs;
	tabft['p'] = ft_convp;
	tabft['d'] = ft_convd;
	tabft['i'] = ft_convd;
	tabft['u'] = ft_convu;
	tabft['x'] = ft_convx;
	tabft['X'] = ft_convxx;
	if (!((*tabft[(int)str[n]])(av, mas)))
		return (NULL);
	return ("ok");
}
