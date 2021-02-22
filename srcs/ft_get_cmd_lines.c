/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:52:58 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/09 16:00:53 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

char	*ft_strdup_size(char *line, int end, int start)
{
	char	*dest;
	int		k;

	k = 0;
	if (!(dest = malloc(sizeof(char) * (end - start) + 1)))
		return (NULL);
	while (start < end)
	{
		dest[k] = line[start];
		start++;
		k++;
	}
	dest[k] = '\0';
	return (dest);
}

int		ft_del_cmdline(t_mini *s, int ret)
{
	t_cmdl	*tmp;
	t_cmdl	*todel;

	todel = s->firstcmdl;
	while (todel)
	{
		tmp = todel->next;
		if (todel->str)
			free(todel->str);
		free(todel);
		todel->str = NULL;
		todel->next = NULL;
		todel = tmp;
	}
	s->firstcmdl = NULL;
	return (ret);
}
