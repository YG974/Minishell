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
** link the new token to the previous ones or to cmdline if it's the first
*/
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

/*
** return a specific FLAG for each metacharacter
*/
int		flag_meta_token(char *str)
{
	if (str[0] == '>' && str[1] == '\0')
		return (S_GREATER);
	else if (str[0] == '>' && str[1] == '>')
		return (D_GREATER);
	else if (str[0] == '<' && str[1] == '\0')
		return (S_LESS);
	else if (str[0] == '|' && str[1] == '\0')
		return (S_PIPE);
	else if (str[0] == ';' && str[1] == '\0')
		return (S_SEMICOLON);
	else
		return (FORBIDEN_SEP);
	return (0);
}

/*
** malloc the new token from metacharacter word and flag it with meta flag
*/
t_tok	*add_meta(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	if (s->p.str[s->i] == '>' && s->p.str[s->i + 1] == '|')
			s->i++;
	else if (s->p.str[s->i] == s->p.str[s->i + 1])
		s->i++;
	s->i++;
	new->str = ft_strdup_size(s->p.str, s->i, j);
	new->flag = flag_meta_token(new->str);
	new = link_token(s, tok, new);
	return (new);
}

/*
** malloc the new token from regular word and flag it with T_WORD
*/
t_tok	*add_word(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '7')
		s->i++;
	new->str = ft_strdup_size(s->p.str, s->i, j);
	new->flag = T_WORD;
	new = link_token(s, tok, new);
	return (new);
}

/*
** malloc the new token from '\n' and flag it with NEWLINE
*/
t_tok	*add_newline(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	(void)j;
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	new->str = ft_strdup("newline");
	new->flag = NEWLINE;
	new = link_token(s, tok, new);
	s->i++;
	return (new);
}

/*
** malloc the new token from space or tqb and flag it with BLANK
*/
t_tok	*add_blank(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	(void)j;
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '5')
		s->i++;
	new->str = ft_strdup(" ");
	new->flag = BLANK;
	new = link_token(s, tok, new);
	return (new);
}

/*
** shift all the string by one to the left in order to erase '\' preceding 
** escaped character
*/
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

/*
** malloc the new token and flag it with T_WORD, for TOKEN WORD
*/
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

/*
** malloc the new token from escaped char and flag it with T_WORD
*/
t_tok	*add_backslash(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	s->i++;
	new->str = ft_strdup_size(s->p.str, s->i, j);
	new->flag = T_WORD;
	new = link_token(s, tok, new);
	return (new);
}

/*
** malloc the new token from double quoted input and flag it with T_WORD
*/
t_tok	*add_double_quote(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '2')
	{
		s->i++;
		if (s->p.str[s->i] == '"' && s->p.str[s->i - 1] != '\\')
			break ;
	}
	s->i++;
	new->str = ft_strdup_size(s->p.str, s->i - 1, j + 1);
	new->str = delete_backslash(new->str);
	new->flag = T_WORD;
	new = link_token(s, tok, new);
	return (new);
}

/*
** malloc the new token from single quoted input and flag it with T_WORD
*/
t_tok	*add_simple_quote(t_mini *s, int j, t_tok *tok)
{
	t_tok	*new;
	
	if (!(new = ft_calloc(1, sizeof(t_cmdl))))
		error(s, ERR_CALLOC);
	while (s->p.flag[s->i] == '1')
		s->i++;
	new->str = ft_strdup_size(s->p.str, s->i -1, j + 1);
	new->flag = T_WORD;
	new = link_token(s, tok, new);
	return (new);
}

/*
** DEBUG FUNCTION : print all the tokens and flags
*/
void	print_token(t_mini *s)
{
	t_tok *tok;
	t_cmdl *cmd;

	cmd = s->firstcmdl;
	tok = cmd->firsttoken;
	int i = 0;
	int j = 0;
	while (cmd && tok && tok->next && tok->flag != NEWLINE)
	{
		j++;
		ft_printf("%dcmd_line----------\n", j);
		while (tok && tok->next && tok->flag != NEWLINE)
		{
			i++;
			ft_printf("%d-tok:%s|\n flag:%d|\n----\n", i, tok->str,tok->flag);
			if (tok->next)
				tok = tok->next;
		}
		if (!cmd->next)
			break;
		cmd = cmd->next;

		tok = cmd->firsttoken;
	}
}

/*
** join token which are not seperated by BLANK
** for example the string \o\k'bo'"goss" will return the 3 followings token
** token 1 : o	|token 2 : k	| token 3 : bo	| token 4: goss
** we have to join them to create a single token like in bash
*/
t_cmdl	*join_tokens(t_cmdl *cmd)
{
	t_tok	*tmp;
	t_tok	*tok;

	tok = cmd->firsttoken;
	while (tok && tok->next)
	{
		while (tok->next && tok->flag == 1 && tok->next->flag == 1)
		{
			tmp = tok->next;
			tok->next = tmp->next;
			tok->str = ft_strjoin_free_s1(tok->str, tmp->str);
			free(tmp->str);
			free(tmp);
		}
		tok = tok->next;
	}
	return (cmd);
}

/*
** main tokenization function, call the differents token functions
*/
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
		else
			s->i++;
	}
	cmd = join_tokens(cmd);
	return (1);
}
