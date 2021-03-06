/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:38:34 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/27 18:56:03 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_dot(t_ftprintf *mas, int len, char *tampostr, unsigned long unum)
{
	char *tampozero;

	mas->zero_activ = 0;
	if (mas->dot > 0 && mas->dot > len)
	{
		if (!(tampozero = malloc(sizeof(char) * (mas->dot + 1 - len))))
		{
			free(tampostr);
			return (NULL);
		}
		tampozero[mas->dot - len] = '\0';
		ft_memset(tampozero, '0', mas->dot - len);
		mas->tmp = ft_strjoin(tampozero, tampostr);
		free(tampozero);
		free(tampostr);
		if (!mas->tmp)
			return (NULL);
		tampostr = ft_strdup(mas->tmp);
		free(mas->tmp);
		if (!tampostr)
			return (NULL);
	}
	else if (mas->dot == 0 && unum == 0)
		tampostr[0] = '\0';
	return (tampostr);
}

void	*ft_staru_ii(char *tampospace, t_ftprintf *mas, int len)
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

void	*ft_staru(t_ftprintf *mas, int len, char *tampostr)
{
	char	*tampospace;

	tampospace = NULL;
	if (mas->star_activ && mas->star != 0 && mas->star > len)
	{
		if (mas->star > len)
			if (!(tampospace = ft_staru_ii(tampospace, mas, len)))
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

void	*ft_convu(va_list av, t_ftprintf *mas)
{
	char			*tampostr;
	int				len;
	unsigned long	unum;

	tampostr = NULL;
	unum = va_arg(av, unsigned int);
	if (mas->dot < 0)
		mas->dot_activ = 0;
	if (mas->l_align || mas->dot_activ || mas->star < 0)
		mas->zero_activ = 0;
	if (!(tampostr = ft_itoau(unum)))
		return (NULL);
	len = ft_strlen(tampostr);
	if (mas->dot_activ)
		if (!(tampostr = ft_dot(mas, len, tampostr, unum)))
			return (NULL);
	len = ft_strlen(tampostr);
	if (mas->star < 0)
	{
		mas->star = mas->star * -1;
		mas->l_align = 1;
	}
	return (ft_staru(mas, len, tampostr));
}
