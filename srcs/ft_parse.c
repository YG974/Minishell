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

/*
**	cmd->str = command line;
**	cmd->flag = flags or comments;
**	cmd->str[i] = char i of the line;
**	cmd->flag[i] = flags or comments on char i;
**	flags :
**	1 : inside simpled quotes
**	2 : inside double quotes
**	3 : escaped by backslash
**	4 : dollar expansion
**
**	look for name variable in env
**	if variable name is found, return its value
**	if name is not found, return empty string ""
*/

/*
** join strings s1 and s2 and free them
*/

char	*ft_strjoin_free_s1_s2(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*str;

	if (!(s2 && s1))
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = -1;
	if (!(str = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	while (++i < len1)
		str[i] = s1[i];
	while (i < len1 + len2)
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[len1 + len2] = '\0';
	free((void *)s1);
	free((void *)s2);
	return (str);
}

/*
** return 1 if the char is a non espaced metacharacter, else 0
*/

int		is_meta(char c)
{
	if (c == '>' || c == '<' || c == ';' || c == '|')
		return (1);
	else
		return (0);
}

/*
** look for redirection file into the tokens, and flag it with REDIR_ARG
** return -1 if syntax error
** return 0 if NO syntax error
*/

int		find_redir_arg(t_mini *s, t_tok *tok)
{
	(void)s;
	while (tok && tok->next)
	{
		tok = tok->next;
		if (tok->flag == BLANK)
			tok = tok->next;
		if (tok->flag <= REDIR_ARG)
		{
			tok->flag = REDIR_ARG;
			return (0);
		}
		if (tok->flag == T_DOLLAR)
		{
			tok->flag = T_DOLLAR;
			return (0);
		}
		else
		{
			s->currentcmdl->token = tok;
			return (-1);
		}
	}
	return (-1);
}

/*
** return 1 if the token is a redirection token
** return 0 if the token is NOT a redirection token
*/

int		is_redir(int flag)
{
	if (flag == S_GREATER || flag == D_GREATER || flag == S_LESS)
		return (1);
	else
		return (0);
}

/*
** main parsing, call the differents parsing and error functions
*/

int		ft_parse(t_mini *s)
{
	s->error = 0;
	s->parsed = 0;
	if (s->read.buf[0] == '\n')
		return (0);
	s->p.str = s->read.buf;
	if ((check_quotes(s, &s->p)) < 0)
		return (0);
	check_dollars(s, &s->p);
	flag_blank(s, &s->p);
	flag_meta(s, &s->p);
	flag_word(s, &s->p);
	flag_newline(s, &s->p);
	if (!(break_cmdline_into_token(s)))
		return (ft_del_cmdline(s, 0));
	if ((check_sep_syntax(s)) == -1 || (split_cmdl(s)) == -1)
	{
		free(s->p.flag);
		return (ft_del_cmdline(s, 0));
	}
	exec_cmdlines(s);
	ft_del_cmdline(s, 0);
	free(s->p.flag);
	return (0);
}
