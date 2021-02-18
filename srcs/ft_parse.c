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

char	*get_env_value(t_mini *s, char *name)
{
	char	*value;
	t_env	*env;
	int		i;

	value = NULL;
	env = s->env;
	i = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(env->name, name, i) == 0 && i == ft_strlen(env->name))
			value = ft_strdup(env->value);
		env = env->next;
	}
	if (value == NULL)
		value = ft_strdup("");
	free(name);
	return (value);
}

/*
**	replace the env values ($NAME) by their value in cmd->buf
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

void	expand_dollars(t_mini *s, t_parse *p, int i, int j)
{
	char	*tmp;

	p->buf = ft_strdup("");
	while (p->str[i])
	{
		i = i + j;
		j = 0;
		if (p->flag[i] == '4')
		{
			while (p->flag[i + j] == '4' && p->str[i + j])
				j++;
			tmp = ft_strdup_size(p->str, i + j, i);
			tmp = get_env_value(s, tmp);
			p->buf = ft_strjoin_free_s1_s2(p->buf, tmp);
		}
		else
		{
			while (p->flag[i + j] != '4' && p->str[i + j])
				j++;
			tmp = ft_strdup_size(p->str, i + j - 1, i);
			p->buf = ft_strjoin_free_s1_s2(p->buf, tmp);
		}
	}
}

/*
**	flag the dollars sign in the p->flag string with a '4'
*/

void	check_dollars(t_mini *s, t_parse *p)
{
	s->i = 0;
	while (p->str[s->i])
	{
		if (p->str[s->i] == '$' && p->flag[s->i] != '1'
				&& p->str[s->i - 1] != '\\')
		{
			s->i++;
			while (p->str[s->i]
					&& (ft_isalnum(p->str[s->i])
						|| p->str[s->i] == '_'))
				p->flag[s->i++] = '4';
		}
		else
			s->i++;
	}
}

int		syntax_error(t_mini *s, char *str, int err)
{
	s->error = 3;
	(void)s;
	g_sig.ret = 2;
	ft_putstr_fd(RED, STDERR);
	if (err == 1)
		ft_putstr_fd("Minishell: syntax error : single quotes opened.\n", STDERR);
	else if (err == 2)
		ft_putstr_fd("Minishell: syntax error : double quotes opened.\n", STDERR);
	else
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token: \"", STDERR);
		ft_putstr_fd(str, STDERR);
		ft_putstr_fd("\"\n", STDERR);
	}
	ft_putstr_fd(RESET, STDERR);
	return (-1);
}

void	check_lit_char(t_mini *s, t_parse *p)
{
	s->i++;
	if (p->str[s->i])
		p->flag[s->i] = '3';
	s->i++;
}

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
				return(syntax_error(s, NULL, 2));
		}
		p->flag[s->i++] = '2';
	}
	return (1);
}

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
				return(syntax_error(s, NULL, 1));
		}
		p->flag[s->i++] = '1';
	}
	return (1);
}

int		check_quotes(t_mini *s, t_parse *p)
{
	int i;

	i = -1;
	if (p->flag)
		free(p->flag);
	p->flag = ft_strdup(p->str);
	while (p->flag && p->flag[++i])
		p->flag[i] = '0';
	s->i = 0;
	while (p->str[s->i]  && s->error != 3)
	{
		if (p->str[s->i] == '\"')
			check_double_quotes(s, p);
		else if (p->str[s->i] == '\'')
			check_simple_quotes(s, p);
		else if (p->str[s->i] == '\\')
			check_lit_char(s, p);
		else
			s->i++;
	}
	return (1);
}

/*
** itinerate the string and put the flag 5 on every not escaped blank
** FLAG = 5 --> not escaped BLANK
*/
int		is_meta(char c)
{
	if (c == '>' || c == '<' || c == ';' || c == '|')
		return (1);
	else
		return (0);
}

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

void	print_str(t_mini *s)
{
	ft_putstr_fd( "str:", 1);
	ft_putstr_fd(s->p.str, 1);
	ft_putstr_fd( "\nflg:", 1);
	ft_putstr_fd(s->p.flag, 1);
	ft_putstr_fd( "\nbuf:", 1);
	ft_putstr_fd(s->p.buf, 1);
	ft_putstr_fd( "\n--------\n", 1);
}

int		syntax_sep_error(t_mini *s, t_tok *tok, int err)
{
	ft_putstr_fd(RED, STDERR);
	if (err == 1)
		ft_putstr_fd("Minishell: syntax error near unexpected token: \"", STDERR);
	else if (err == 2)
		ft_putstr_fd("Minishell: syntax error token not supported: \"", STDERR);
	if (tok->str)
		ft_putstr_fd(tok->str, STDERR);
	ft_putstr_fd("\"\n", STDERR);
	ft_del_tokens(s->currentcmdl, 0);
	return (0);
}

int		is_redir(int flag)
{
	if (flag == S_GREATER || flag == D_GREATER || flag == S_LESS)
		return (1);
	else
		return (0);
}

int		pipe_syntax_error(t_mini *s, t_tok *tok)
{
	if (!tok->next)
		return (-1);
	if (!tok->prev)
		return (-1);
	while (tok && tok->next)
	{
		tok = tok->next;
		if (tok->flag == T_WORD)
		{
			tok->flag = PIPE_ARG;
			s->currentcmdl->token = tok;
			return (0);
		}
		else if (tok->flag > BLANK)
		{
			s->currentcmdl->token = tok;
			return (-1);
		}
	}
	return (-1);
}

int		find_redir_arg(t_mini *s, t_tok *tok)
{
	while (tok && tok->next)
	{
		tok = tok->next;
		if (tok->flag == T_WORD)
		{
			tok->flag = REDIR_ARG;
			s->currentcmdl->token = tok;
			return (0);
		}
		else if (tok->flag == S_PIPE)
			return (pipe_syntax_error(s, tok));
		else if (tok->flag > BLANK)
		{
			s->currentcmdl->token = tok;
			return (-1);
		}
	}
	return (-1);
}

int		check_sep_syntax(t_mini *s)
{
	t_tok	*tok;

	(void)s;
	tok = s->firstcmdl->firsttoken;
	if (tok->flag == S_SEMICOLON)
		return(syntax_sep_error(s, tok, 1));
	while (tok)
	{
		if (tok->flag >= D_PIPE)
			return(syntax_sep_error(s, tok, 2));
		else if ((is_redir(tok->flag) == 1) && ((find_redir_arg(s, tok)) == -1))
			return(syntax_sep_error(s, tok, 1));
		else if (tok->flag == S_PIPE && (pipe_syntax_error(s, tok)) == -1)
			return(syntax_sep_error(s, tok, 1));
		tok = tok->next;
	}
	return (1);
}

int		split_cmdl(t_mini *s)
{
	/*t_tok	*tok;*/

	(void)s;
	/*tok = s->firstcmdl->firsttoken;*/
	/*if ((check_sep_syntax(s)) == -1)*/
		return (0);

}

int		ft_parse(t_mini *s)
{
	s->error = 0;
	s->parsed = 0;
	s->p.str = s->read.buf;
	s->p.flag = ft_strdup("");
	if (s->read.buf[0] == '\n')
		return (0);
	if ((!check_quotes(s, &s->p)) && s->parsed == 0)
		return (0);
	check_dollars(s, &s->p);
	expand_dollars(s, &s->p, 0, 0);
	s->p.str = s->p.buf;
	check_quotes( s, &s->p);
	flag_blank(s, &s->p);
	flag_meta(s, &s->p);
	flag_word(s, &s->p);
	flag_newline(s, &s->p);
	print_str(s);
	if (!(break_cmdline_into_token(s)))
		return (0);
	if ((check_sep_syntax(s)) == -1 || ((split_cmdl(s)) == -1))
		return (0);
	print_token(s->currentcmdl->firsttoken);
	/*join_tokens(s->currentcmdl);*/
	free(s->p.buf);
	free(s->p.flag);
	return (0);
}
