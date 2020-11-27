/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convp_ii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:38:34 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/21 15:08:42 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	*ft_setzero(t_ftprintf *mas, int opt, char *tampospace, int len)
{
	if (opt == 1)
	{
		if (mas->zero_activ && mas->star > 0)
		{
			mas->dot_activ = 1;
			mas->dot = mas->star - 2;
			mas->star_activ = 0;
			mas->zero_activ = 0;
		}
	}
	else
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
	return ("ok");
}

void	*ft_dotp_ii(t_ftprintf *mas, char *tmpstr, int len, unsigned long pnum)
{
	char *tampozero;

	if (mas->dot > 0 && mas->dot > len)
	{
		if (!(tampozero = malloc(sizeof(char) * (mas->dot + 1 - len))))
		{
			free(tmpstr);
			return (NULL);
		}
		tampozero[mas->dot - len] = '\0';
		ft_memset(tampozero, '0', mas->dot - len);
		mas->tmp = ft_strjoin(tampozero, tmpstr);
		free(tampozero);
		free(tmpstr);
		if (!mas->tmp)
			return (NULL);
		tmpstr = ft_strjoin("0x", mas->tmp);
		free(mas->tmp);
		if (!tmpstr)
			return (NULL);
	}
	else if (mas->dot == 0 && pnum == 0)
		tmpstr[0] = '\0';
	return (tmpstr);
}

void	*ft_dotp(t_ftprintf *mas, char *tampostr, int len, unsigned long pnum)
{
	if (mas->dot_activ && mas->dot > len)
	{
		tampostr = ft_dotp_ii(mas, tampostr, len, pnum);
		return (tampostr);
	}
	else
	{
		mas->tmp = ft_strdup(tampostr);
		free(tampostr);
		if (!mas->tmp)
			return (NULL);
		if (mas->dot_activ && mas->dot == 0 && pnum == 0)
			tampostr = ft_strdup("0x");
		else
			tampostr = ft_strjoin("0x", mas->tmp);
		free(mas->tmp);
		if (!tampostr)
			return (NULL);
		return (tampostr);
	}
}

void	*ft_starp_ii(t_ftprintf *mas, int len, char *tampostr)
{
	char *tampospace;

	tampospace = NULL;
	if (mas->star_activ && mas->star != 0 && mas->star > len)
	{
		if (mas->star > len)
			if (!(tampospace = ft_setzero(mas, 0, tampospace, len)))
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

void	*ft_nn(char *ts, t_ftprintf *mas, int len, unsigned long pnum)
{
	if (mas->l_align || mas->dot_activ || mas->star < 0)
		mas->zero_activ = 0;
	ts = ft_itoap(pnum, "0123456789abcdef");
	if (!ts)
		return (NULL);
	len = ft_strlen(ts);
	ft_setzero(mas, 1, ts, len);
	if (!(ts = ft_dotp(mas, ts, len, pnum)))
		return (NULL);
	len = ft_strlen(ts);
	if (mas->star < 0)
	{
		mas->star = mas->star * -1;
		mas->l_align = 1;
	}
	return (ft_starp_ii(mas, len, ts));
}
