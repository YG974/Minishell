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

void	expand_dollars(t_mini *s, t_cmdl *cmd)
{
	char	*tmp;

	s->i = 0;
	s->j = 0;
	cmd->buf = ft_strdup("");
	while (cmd->str[s->i])
	{
		s->i = s->i + s->j;
		s->j = 0;
		if (cmd->flag[s->i] == '4')
		{
			while (cmd->flag[s->i + s->j] == '4' && cmd->str[s->i + s->j])
				s->j++;
			tmp = ft_strdup_size(cmd->str, s->i + s->j, s->i);
			tmp = get_env_value(s, tmp);
		}
		else
		{
			while (cmd->flag[s->i + s->j] != '4' && cmd->str[s->i + s->j])
				s->j++;
			tmp = ft_strdup_size(cmd->str, s->i + s->j - 1, s->i);
		}
		cmd->buf = ft_strjoin_free_s1(cmd->buf, tmp);
		free(tmp);
	}
}

/*
**	flag the dollars sign in the cmd->flag string with a '4'
*/

void	check_dollars(t_mini *s, t_cmdl *cmd)
{
	s->i = 0;
	while (cmd->str[s->i])
	{
		if (cmd->str[s->i] == '$' && cmd->flag[s->i] != '1'
				&& cmd->str[s->i - 1] != '\\')
		{
			s->i++;
			while (cmd->str[s->i]
					&& (ft_isalnum(cmd->str[s->i])
						|| cmd->str[s->i] == '_'))
				cmd->flag[s->i++] = '4';
		}
		else
			s->i++;
	}
}

int		syntax_error(t_mini *s, char *str, int err)
{
	s->error = 2;
	g_sig.ret = 2;
	ft_putstr_fd(RED, STDERR);
	if (err == 1)
	{
	ft_putstr_fd("Minishell: syntax error : single quotes opened.\n", STDERR);

	}
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
	p->flag[s->i] = '3';
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
	p->flag = ft_strdup(p->str);
	while (p->flag && p->flag[++i])
		p->flag[i] = '0';
	s->i = 0;
	while (p->str[s->i])
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


int		ft_parse(t_mini *s)
{
	s->error = 0;
	s->parsed = 0;
	s->p.str = s->read.buf;
	if (s->read.buf[0] == '\n')
		return (0);
	if ((!check_quotes(s, &s->p)) && s->parsed == 0)
		return (0);
	ft_putstr_fd(s->p.str, 1);
	/*exit(1);*/
	return (1);
}
