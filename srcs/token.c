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

t_tok	*link_token(t_mini *s, t_tok *tok, t_tok *new)
{
	if (tok)
	{
		tok->next = new;
		new->prev = tok;
		s->currentcmdl->token = tok->next;
	}
	else
		s->currentcmdl->firsttoken = new;
	return (new);
}

int		flag_meta_token(char *str)
{
	if (str[0] == '>' && str[1] == '\0')
		return (S_GREATER);
	else if (str[0] == '>' && str[1] == '>')
		return (D_GREATER);
	else if (str[0] == '<' && str[1] == '\0')
		return (S_LESS);
	else if (str[0] == '<' && str[1] == '<')
		return (D_LESS);
	else if (str[0] == '|' && str[1] == '\0')
		return (S_PIPE);
	else if (str[0] == '|' && str[1] == '|')
		return (D_PIPE);
	else if (str[0] == ';' && str[1] == '\0')
		return (S_SEMICOLON);
	else if (str[0] == ';' && str[1] == ';')
		return (D_SEMICOLON);
	return (0);
}

t_tok	*add_meta(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	if (s->p.flag[s->i] == '6' && (s->p.str[s->i] == s->p.str[s->i + 1]))
		s->i++;
	new->str = ft_strdup_size(s->p.str, s->i + 1, j);
	new->flag = flag_meta_token(new->str);
	new = link_token(s, tok, new);
	return (new);
}

t_tok	*add_word(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '7')
		s->i++;
	new->str = ft_strdup_size(s->p.str, s->i + 1, j);
	new->flag = 1;
	new = link_token(s, tok, new);
	return (new);
}

t_tok	*add_newline(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	(void)j;
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	new->str = ft_strdup("newline");
	new->flag = 16;
	new = link_token(s, tok, new);
	return (new);
}

t_tok	*add_blank(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	(void)j;
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i + 1] == '5')
		s->i++;
	new->str = ft_strdup(" ");
	new->flag = 5;
	new = link_token(s, tok, new);
	return (new);
}

char *shift_str_left(char *str, int i)
{
	while (str[i])
	{
		str[i - 1] = str[i];
		i++;
	}
	str[i - 1] = '\0';
	return (str);
}
char *delete_backslash(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i - 1] == '\\' && str[i -1])
			str = shift_str_left(str, i);
		else if (str[i] == '"' && str[i - 1] == '\\' && str[i -1])
			str = shift_str_left(str, i);
		else if (str[i] == '\\' && str[i - 1] == '\\' && str[i -1])
			str = shift_str_left(str, i);
		i++;
	}
	return (str);
}

t_tok	*add_backslash(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	new->str = ft_strdup_size(s->p.str, s->i + 1, j);
	new->flag = 1;
	new = link_token(s, tok, new);
	return (new);
}

t_tok	*add_double_quote(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '2')
		s->i++;
	new->str = ft_strdup_size(s->p.str, s->i -1, j + 1);
	new->str = delete_backslash(new->str);
	new->flag = 1;
	new = link_token(s, tok, new);
	return (new);
}

t_tok	*add_simple_quote(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '1')
		s->i++;
	new->str = ft_strdup_size(s->p.str, s->i -1, j + 1);
	new->flag = 1;
	new = link_token(s, tok, new);
	return (new);
}

void	print_token(t_tok *tok)
{
	int i = 0;
	while (tok)
	{
		i++;
		ft_printf("%d-tok:%s|\n flag:%d|\n----\n", i, tok->str,tok->flag);
		/*ft_printf("|%s|f:%d-", tok->str,tok->flag);*/
		tok = tok->next;
	}
}

t_cmdl	*join_tokens(t_cmdl *cmd)
{
	t_tok	*tmp;
	t_tok	*tok;

	tok = cmd->firsttoken;
	while (tok && tok->next)
	{
		if (tok->next && tok->flag == 1 && tok->next->flag == 1)
		{
			tmp = tok->next;
			tok->next = tmp->next;
			tok->str = ft_strjoin_free_s1(tok->str, tmp->str);
			free(tmp->str);
		}
		tok = tok->next;
	}
	return (cmd);
}

int		break_cmdline_into_token(t_mini *s)
{
	t_cmdl	*cmd;

	if (!(cmd = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	s->firstcmdl = cmd;
	s->currentcmdl = cmd;
	s->i = 0;
	while (s->p.buf[s->i])
	{
		if (s->p.flag[s->i] == '5')
			cmd->token = add_blank(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '1')
			cmd->token = add_simple_quote(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '2')
			cmd->token = add_double_quote(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '3')
			cmd->token = add_backslash(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '6')
			cmd->token = add_meta(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '7')
			cmd->token = add_word(s, s->i, cmd->token);
		else if (s->p.flag[s->i] == '8')
			cmd->token = add_newline(s, s->i, cmd->token);
		s->i++;
	}
	cmd = join_tokens(cmd);
	print_token(cmd->firsttoken);
	return (1);
}
