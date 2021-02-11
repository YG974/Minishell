/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:45:47 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:21:57 by pcoureau         ###   ########.fr       */
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
	/*ft_putstr_fd(name, 2);*/
	while (env)
	{
		if (ft_strncmp(env->name, name, i) == 0 && i == ft_strlen(env->name))
			value = ft_strdup(env->value);
		env = env->next;
	}
	/*[>ft_putstr_fd(env->value, 2);<]*/
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

void	check_double_quotes(t_mini *s, t_cmdl *cmd)
{
	if (cmd->str[s->i - 1] == '\\')
	{
		cmd->flag[s->i - 1] = '3';
		cmd->flag[s->i++] = '3';
	}
	else
	{
		cmd->flag[s->i++] = '2';
		while (cmd->str[s->i] != '\"' && cmd->str[s->i])
		{
			cmd->flag[s->i++] = '2';
			if (cmd->str[s->i - 1] == '\\' && cmd->str[s->i] != '\0')
				cmd->flag[s->i++] = '2';
			if (cmd->str[s->i] == '\0')
				error(s, ERR_QUOTES);
		}
		cmd->flag[s->i++] = '2';
	}
}

void	check_simple_quotes(t_mini *s, t_cmdl *cmd)
{
	if (cmd->str[s->i - 1] == '\\')
	{
		cmd->flag[s->i - 1] = '3';
		cmd->flag[s->i++] = '3';
	}
	else
	{
		cmd->flag[s->i++] = '1';
		while (cmd->str[s->i] != '\'' && cmd->str[s->i])
		{
			cmd->flag[s->i++] = '1';
			if (cmd->str[s->i] == '\0')
				error(s, ERR_QUOTES);
		}
		cmd->flag[s->i++] = '1';
	}
}
