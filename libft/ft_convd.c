/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:38:34 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/26 19:37:56 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_convd_pos(t_ftprintf *mas, char *tampostr)
{
	mas->len = ft_strlen(tampostr);
	if (mas->l_align)
	{
		if (mas->dot_activ)
			if (mas->dot > 0)
				ft_printd_dot(mas->dot, mas);
		ft_printd_tmps(tampostr, mas);
		if (mas->star_activ)
			if (mas->star > mas->len)
				ft_printd_star(mas->star - mas->len, mas);
		return ;
	}
	if (mas->star_activ)
		if (mas->star > mas->len + mas->dot)
			ft_printd_star(mas->star - (mas->len + mas->dot), mas);
	if (mas->dot_activ)
		if (mas->dot > 0)
			ft_printd_dot(mas->dot, mas);
	ft_printd_tmps(tampostr, mas);
}

void	ft_convd_neg(t_ftprintf *mas, char *tampostr)
{
	mas->len = ft_strlen(tampostr) + 1;
	if (mas->l_align)
	{
		ft_printd_m(mas);
		if (mas->dot_activ)
			if (mas->dot > 0)
				ft_printd_dot(mas->dot, mas);
		ft_printd_tmps(tampostr, mas);
		if (mas->star_activ)
			if (mas->star > mas->len)
				ft_printd_star(mas->star - mas->len, mas);
		return ;
	}
	if (mas->zero_activ)
		ft_printd_m(mas);
	if (mas->star_activ)
		if (mas->star > mas->len + mas->dot)
			ft_printd_star(mas->star - (mas->len + mas->dot), mas);
	if (!mas->zero_activ)
		ft_printd_m(mas);
	if (mas->dot_activ)
		if (mas->dot > 0)
			ft_printd_dot(mas->dot, mas);
	ft_printd_tmps(tampostr, mas);
}

void	ft_convd_ii(t_ftprintf *mas, int dnum)
{
	if (mas->star < 0)
	{
		mas->star = mas->star * -1;
		mas->l_align = 1;
	}
	mas->neg = (dnum < 0) ? 1 : 0;
	if (mas->dot < 0)
	{
		mas->dot_activ = 0;
		mas->dot = 0;
	}
}

void	*ft_convd(va_list av, t_ftprintf *mas)
{
	char	*tampostr;
	int		dnum;

	dnum = va_arg(av, int);
	if (!(tampostr = ft_itoad(dnum)))
		return (NULL);
	ft_convd_ii(mas, dnum);
	if (dnum == 0 && mas->dot_activ && mas->dot == 0)
		tampostr[0] = '\0';
	if (mas->l_align || mas->dot_activ || mas->star < 0)
		mas->zero_activ = 0;
	if (mas->dot_activ == 1 && mas->dot > ft_strlen(tampostr))
		mas->dot = mas->dot - ft_strlen(tampostr);
	else
	{
		mas->dot_activ = 0;
		mas->dot = 0;
	}
	if (mas->neg)
		ft_convd_neg(mas, tampostr);
	else
		ft_convd_pos(mas, tampostr);
	free(tampostr);
	return ("ok");
}
