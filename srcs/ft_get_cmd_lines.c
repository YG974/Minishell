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

int		ft_not_quoted(char *line, int i)
{
	int q;

	q = 0;
	while (i >= 0)
	{
		if (i > 0 && line[i - 1] == '\\')
			q = q + 0;
		else if (line[i] == '\'' && q == 0)
			q = 1;
		else if (line[i] == '\"' && q == 0)
			q = 2;
		else if (line[i] == '\'' && q == 1)
			q = 0;
		else if (line[i] == '\"' && q == 2)
			q = 0;
		i--;
	}
	return (q);
}

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

t_cmdl	*ft_create_cmdl(t_mini *s)
{
	t_cmdl	*tmp;

	tmp = NULL;
	if (s->firstcmdl == NULL)
	{
		if (!(s->firstcmdl = ft_calloc(1, sizeof(t_cmdl))))
			return (NULL);
		tmp = s->firstcmdl;
		tmp->str = NULL;
		tmp->next = NULL;
	}
	else
	{
		tmp = s->firstcmdl;
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (!(tmp->next = ft_calloc(1, sizeof(t_cmdl))))
			return (NULL);
		tmp = tmp->next;
		tmp->str = NULL;
		tmp->next = NULL;
	}
	return (tmp);
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

int		ft_get_cmd(char *line, t_mini *s)
{
	int		i;
	int		j;
	t_cmdl	*tmp;

	i = -1;
	j = 0;
	while (line[++i])
	{
		if (i > 0 && line[i - 1] == '\\')
			i = i + 0;
		else if (line[i] == ';' && !ft_not_quoted(line, i))
		{
			if (!(tmp = ft_create_cmdl(s)))
				return (ft_del_cmdline(s, 1));
			if (!(tmp->str = ft_strdup_size(line, i + 1, j)))
				return (ft_del_cmdline(s, 1));
			i++;
			j = i;
		}
	}
	if (!(tmp = ft_create_cmdl(s)))
		return (ft_del_cmdline(s, 1));
	if (!(tmp->str = ft_strdup_size(line, i, j)))
		return (ft_del_cmdline(s, 1));
	return (0);
}
