/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
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

char	*replace_tab_by_space(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
	return (str);
}


t_tok	*new_dollar_tok(t_mini *s, char *str, t_tok *prev, int flag)
{
	t_tok	*new;

	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	new->str = str;
	if (flag == 0)
		new->flag = T_WORD;
	if (flag != 0)
		new->flag = BLANK;
	new->prev = prev;
	return (new);
}

t_tok	*split_dollar_token(t_mini *s, char *str, t_tok *prev, t_tok *next)
{
	char **tab;
	int		i;
	t_tok	*new;

	i = 0;
	str = replace_tab_by_space(str);
	tab = ft_split(str, ' ');
	free(prev->next);
	if (tab[0][0] == '\0')
	{
		new = new_dollar_tok(s, "", prev, 1);
		new->next = next;
		return (new);
	}
	new = new_dollar_tok(s, tab[i], prev, 0);
	/*print_tab(tab);*/
	i++;
	while (tab[i])
	{
		new = new_dollar_tok(s, tab[i], new, 0);
		new = new_dollar_tok(s, " ", new, 1);
		i++;
	}
	new->next = next;
	return (new);
}

/*
**	replace the env names ($NAME) in the input by their values in cmd->buf
*/

void	expand_dollars(t_mini *s, t_cmdl *cmd, int i, int j)
{
	char	*tmp;

	(void)i;
	(void)j;
	cmd->token = cmd->firsttoken;
	while (cmd->token)
	{
		if (cmd->token->flag == T_DOLLAR)
		{
			tmp = ft_strdup_size(cmd->token->str, ft_strlen(cmd->token->str), 1);
			tmp = get_env_value(s, tmp);
			/*free(cmd->token);*/
			/*cmd->token->str = tmp;*/
			cmd->token = split_dollar_token(s, tmp, cmd->token->prev, cmd->token->next);
		}
		cmd->token = cmd->token->next;
	}
	cmd->token = cmd->firsttoken;
	/*p->buf = ft_strdup("");*/
	/*while (p->str[i])*/
	/*{*/
		/*i = i + j;*/
		/*j = 0;*/
		/*if (p->flag[i] == '4')*/
		/*{*/
			/*while (p->flag[i + j] == '4' && p->str[i + j])*/
				/*j++;*/
			/*tmp = ft_strdup_size(p->str, i + j, i);*/
			/*tmp = get_env_value(s, tmp);*/
			/*p->buf = ft_strjoin_free_s1_s2(p->buf, tmp);*/
		/*}*/
		/*else*/
		/*{*/
			/*while (p->flag[i + j] != '4' && p->str[i + j])*/
				/*j++;*/
			/*tmp = ft_strdup_size(p->str, i + j - 1, i);*/
			/*p->buf = ft_strjoin_free_s1_s2(p->buf, tmp);*/
		/*}*/
	/*}*/
}

/*
** itinerate the string and put the flag 4 on var names followings '$' char
** FLAG = 4 --> not escaped VARIABLE NAME
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
					&& (ft_isalnum(p->str[s->i]) || p->str[s->i] == '_'))
				p->flag[s->i++] = '4';
		}
		else
			s->i++;
	}
}
