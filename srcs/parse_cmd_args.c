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
	while ((ft_strchr(cmd->token->str, '=') || (cmd->token->flag == BLANK)))
		cmd->token = cmd->token->next;
	while (cmd->token && cmd->token->flag < S_PIPE)
	{
		if (cmd->token->flag == T_WORD)
		{
			cmd->buf = ft_strjoin_free_s1(cmd->buf, cmd->token->str);
			cmd->buf = ft_strjoin_free_s1(cmd->buf, "\n");
		}
		cmd->token = cmd->token->next;
	}
	return (0);
}

void	handle_dollar_question_mark(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	cmd->token = cmd->firsttoken;
	while (cmd->token)
	{
		if (cmd->token->str[0] == '$' && cmd->token->str[1] == '?'
			&& cmd->token->str[2] == '\0')
		{
			free(cmd->token->str);
			cmd->token->str = ft_itoa(g_sig.ret);
			cmd->token->flag = T_WORD;
		}
		cmd->token = cmd->token->next;
	}
	cmd->token = cmd->firsttoken;
	return ;
}

void	print_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		ft_putstr_fd(tab[i++], 2);
}
