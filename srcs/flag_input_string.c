/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_input_string.c                                :+:      :+:    :+:   */
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
** itinerate the string and put the flag 7 on every not escaped word
** FLAG = 7 --> not escaped WORD
*/

void	flag_word(t_mini *s, t_parse *p)
{
	s->i = 0;
	while (p->str[s->i])
	{
		if (p->str[s->i] != '\\' && p->flag[s->i] == '0')
			p->flag[s->i] = '7';
		s->i++;
	}
	return ;
}

/*
** itinerate the string and put the flag 5 on every not escaped blank
** FLAG = 5 --> not escaped BLANK
*/

void	flag_blank(t_mini *s, t_parse *p)
{
	s->i = 0;
	while (p->str[s->i])
	{
		if ((p->str[s->i] == ' ' || p->str[s->i] == '\t') &&
			(p->flag[s->i] == '0'))
			p->flag[s->i] = '5';
		s->i++;
	}
	return ;
}

/*
** itinerate the string and put the flag 8 on '\n' char, usefull to return
** the good error string when syntax error : syntax error near unexpected token
** FLAG = 8 --> NEWLINE '\n'
*/

void	flag_newline(t_mini *s, t_parse *p)
{
	s->i = 0;
	while (p->str[s->i])
	{
		if (p->str[s->i] == '\n')
			p->flag[s->i] = '8';
		s->i++;
	}
	return ;
}

/*
** itinerate the string and put the flag 6 on every not escaped metacharacter
** FLAG = 6 --> not escaped METACHARACTER
*/

void	flag_meta(t_mini *s, t_parse *p)
{
	s->i = 0;
	while (p->str[s->i])
	{
		if ((is_meta(p->str[s->i]) == 1 && p->flag[s->i] == '0'))
			p->flag[s->i] = '6';
		s->i++;
	}
	return ;
}
