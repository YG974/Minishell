/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:21:15 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:21:17 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"


/*void	check_quotes_and_dollars(t_mini *s, t_cmdl *cmd)*/
/*{*/
		/*check_quotes(s, cmd);*/
		/*check_dollars(s, cmd);*/
/*}*/

/*void	syntax_error(t_mini *s, char *str)*/
/*{*/
	/*s->error = 2;*/
	/*g_sig.ret = 2;*/
	/*ft_putstr_fd(RED, STDERR);*/
	/*ft_putstr_fd("Minishell: syntax error near unexpected token: \"", STDERR);*/
	/*ft_putstr_fd(str, STDERR);*/
	/*ft_putstr_fd("\"\n", STDERR);*/
	/*ft_putstr_fd(RESET, STDERR);*/
/*}*/


/*int		check_syntax(t_mini *s, t_cmdl *cmd)*/
/*{*/
	/*s->parsed = 0;*/
	/*while (cmd && !s->error)*/
	/*{*/
		/*cmd = cmd->next;*/
		/*check_quotes_and_dollars(s, cmd);*/
		/*expand_dollars(s, cmd);*/
		/*free_cmd_str(cmd);*/
		/*cmd->str = cmd->buf;*/
		/*check_quotes_and_dollars(s, cmd);*/
		/*ft_get_tokens(s, cmd);*/
		/*check_sep(s, cmd);*/
	/*}*/
	/*if (s->parsed == -1)*/
		/*syntax_error(s, cmd->token->str);*/
	/*return (1);*/
/*}*/


/*void	break_cmdline_into_token(t_mini *s)*/
/*{*/
	/*t_cmdl	*cmd;*/

	/*cmd = s->firstcmdl;*/
	/*if (!check_syntax(s, cmd))*/
		/*return ;*/
	/*while (cmd && !s->error)*/
	/*{*/
		/*check_quotes_and_dollars(s, cmd);*/
		/*expand_dollars(s, cmd);*/
		/*free_cmd_str(cmd);*/
		/*cmd->str = cmd->buf;*/
		/*check_quotes_and_dollars(s, cmd);*/
		/*ft_get_tokens(s, cmd);*/
		/*handle_dollar_question_mark(s, cmd);*/
		/*if (thereisapipe(cmd) && (!ft_redirection(s, cmd)))*/
			/*ft_exe_cmd(s, cmd);*/
		/*else*/
			/*ft_firstpipe(s, cmd);*/
		/*ft_closefd(s);*/
		/*ft_del_tokens(cmd, 0);*/
		/*cmd = cmd->next;*/
	/*}*/
/*}*/
