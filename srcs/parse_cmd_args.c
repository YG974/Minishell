/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:41:58 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/09 15:39:42 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

void	parse_cmd_args2(t_cmdl *cmd)
{
	cmd->token = cmd->token->next;
	if (cmd->token->flag == 2 && cmd->token->str[0] == ' '
			&& cmd->token)
		cmd->token = cmd->token->next->next;
	else
		cmd->token = cmd->token->next;
}

t_tok	*norme_chlag(t_tok *token)
{
	token = token->next;
	while (token->flag == 2 && token->str[0] == '>' && token)
		token = token->next;
	if (token->flag == 2 && token->str[0] == ' ' && token)
		token = token->next->next;
	else
		token = token->next;
	return (token);
}

/*
**	parse the arguments into a string, without the meta, each token is
**	delimited with '\n' in the string, in order to split it in a char **tab;
**	char **args = ft_split(str, '\n';)
*/

int		parse_cmd_args(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	cmd->buf = ft_strdup("");
	cmd->token = cmd->firsttoken;
	while ((ft_strchr(cmd->token->str, '=')
				|| (cmd->token->flag == 2 && cmd->token->str[0] == ' ')))
		cmd->token = cmd->token->next;
	while (cmd->token && cmd->token->flag != FLAG_PIPE)
	{
		if (cmd->token->flag != 2 && cmd->token)
		{
			cmd->buf = ft_strjoin_free_s1(cmd->buf, cmd->token->str);
			cmd->buf = ft_strjoin_free_s1(cmd->buf, "\n");
			cmd->token = cmd->token->next;
		}
		else if (cmd->token->flag == 2 && cmd->token->str[0] == ' ' &&
				cmd->token)
			cmd->token = cmd->token->next;
		else if (cmd->token->flag == 2 && cmd->token->str[0] != ' ' &&
				cmd->token)
			cmd->token = norme_chlag(cmd->token);
	}
	return (0);
}

t_cmdl	*join_tokens(t_cmdl *cmd)
{
	t_tok	*tmp;

	tmp = cmd->token->next;
	cmd->token->next = tmp->next;
	cmd->token->str = ft_strjoin_free_s1(cmd->token->str, tmp->str);
	free(tmp->str);
	return (cmd);
}

void	handle_dollar_question_mark(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	if (cmd->flag)
		free(cmd->flag);
	cmd->token = cmd->firsttoken;
	while (cmd->token)
	{
		while ((cmd->token->flag == FLAG_STR || cmd->token->flag == FLAG_CMD) &&
			(cmd->token->next) && (cmd->token->next->flag == FLAG_STR ||
			cmd->token->next->flag == FLAG_CMD))
			cmd = join_tokens(cmd);
		if (cmd->token->str[0] == '$' && cmd->token->str[1] == '?'
			&& cmd->token->str[2] == '\0')
		{
			free(cmd->token->str);
			cmd->token->str = ft_itoa(g_sig.ret);
		}
		cmd->token = cmd->token->next;
	}
	cmd->token = cmd->firsttoken;
	return ;
}
