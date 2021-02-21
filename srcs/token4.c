/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:21:15 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:21:17 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

void	ft_closefd(t_mini *s)
{
	if (s->std.out > 1)
		dup2(0, 1);
	if (s->std.in > 0)
		close(s->std.in);
	if (s->std.out > 1)
		close(s->std.out);
	s->std.in = 0;
	s->std.out = 1;
	dup2(1, 1);
	dup2(1, 0);
}
