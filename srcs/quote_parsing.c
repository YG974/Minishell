/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:53:01 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 10:53:03 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

/*
** itinerate the string and put the flag 3 on every escaped char
** FLAG = 3 --> ESCAPED CHAR
*/

void	check_lit_char(t_mini *s, t_parse *p)
{
	s->i++;
	if (p->str[s->i])
		p->flag[s->i] = '3';
	s->i++;
}

/*
** itinerate the string and put the flag 2 on every char inside double quotes
** FLAG = 2 --> double quoted char
*/

int		check_double_quotes(t_mini *s, t_parse *p)
{
	if (p->str[s->i - 1] == '\\')
	{
		p->flag[s->i - 1] = '3';
		p->flag[s->i++] = '3';
	}
	else
	{
		p->flag[s->i++] = '2';
		while (p->str[s->i] != '\"' && p->str[s->i])
		{
			p->flag[s->i++] = '2';
			if (p->str[s->i - 1] == '\\' && p->str[s->i] != '\0')
				p->flag[s->i++] = '2';
			if (p->str[s->i] == '\0')
				return (syntax_error(s, NULL, 2));
		}
		p->flag[s->i++] = '2';
	}
	return (1);
}

/*
** itinerate the string and put the flag 1 on every char inside single quotes
** FLAG = 1 --> single quoted char
*/

int		check_simple_quotes(t_mini *s, t_parse *p)
{
	if (p->str[s->i - 1] == '\\')
	{
		p->flag[s->i - 1] = '3';
		p->flag[s->i++] = '3';
	}
	else
	{
		p->flag[s->i++] = '1';
		while (p->str[s->i] != '\'' && p->str[s->i])
		{
			p->flag[s->i++] = '1';
			if (p->str[s->i] == '\0')
				return (syntax_error(s, NULL, 1));
		}
		p->flag[s->i++] = '1';
	}
	return (1);
}

/*
** malloc the flag string, and call the 3 differents quoting type functions
*/

int		check_quotes(t_mini *s, t_parse *p)
{
	int	i;

	i = -1;
	p->flag = ft_strdup(p->str);
	while (p->flag && p->flag[++i])
		p->flag[i] = '0';
	s->i = 0;
	while (p->str[s->i] && s->error != 3)
	{
		if (p->str[s->i] == '\"')
			s->parsed = check_double_quotes(s, p);
		else if (p->str[s->i] == '\'')
			s->parsed = check_simple_quotes(s, p);
		else if (p->str[s->i] == '\\')
			check_lit_char(s, p);
		else
			s->i++;
		if (s->parsed == -1)
		{
			free(p->flag);
			return (-1);
		}
	}
	return (1);
}
