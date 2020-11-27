/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:02:55 by pcoureau          #+#    #+#             */
/*   Updated: 2019/10/22 20:18:28 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putstr_p(char *s, int fd)
{
	int i;

	if (fd < 0)
		return (-1);
	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

