/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:53:01 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 10:53:03 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

int		ft_check_semicolons(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (i > 0 && line[i - 1] == '\\')
			i++;
		else if (line[i] == ';' && !ft_not_quoted(line, i))
		{
			i++;
			while (line[i] != '\0' && line[i] == ' ')
				i++;
			if (line[i] == ';')
				return (1);
		}
		else
			i++;
	}
	return (0);
}

void	ft_testchainlist(t_mini *s)
{
	int		i;
	t_cmdl	*tmp;

	i = 0;
	tmp = s->firstcmdl;
	while (tmp)
	{
		ft_printf("CMD LINE %d : %s\n", i, tmp->str);
		i++;
		tmp = tmp->next;
	}
}

int		ft_parse(t_mini *s)
{
	int	ret;

	ret = 0;
	s->error = 0;
	if (s->read.buf[0] == '\n')
		return (0);
	if (ft_check_semicolons(s->read.buf))
		error(s, ERR_SEMCOL);
	if (!s->error && (ret = ft_get_cmd(s->read.buf, s)))
		error(s, ret);
	break_cmdline_into_token(s);
	ret = ft_del_cmdline(s, 0);
	return (0);
}
