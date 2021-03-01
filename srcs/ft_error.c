/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:41:20 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/09 14:41:48 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

int		ft_redir_error(char *s)
{
	g_sig.ret = 1;
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	error(t_mini *s, int error)
{
	int	ret;

	s->error = 1;
	if (error == ERR_CALLOC)
		ret = ft_printf("Memory Allocation fail\n");
	if (error == ERR_INVALID_ENV_NAME)
		ret = ft_printf("invalid variable name or value\n");
	if (error == ERR_PARSING)
		ret = ft_printf("Parsing fail\n");
	if (error == ERR_QUOTES)
		ret = ft_printf("Parsing fail, quote not close\n");
	if (error == ERR_SEMCOL)
		ret = ft_printf("Bad using of ';'. Retry mother fucker.\n");
	if (error == ERR_EXEC_CMD)
		ret = ft_printf("ERROR IN COMMAND LINE\n");
	if (error == WANT_EXIT)
	{
		s->error = 2;
		if (g_sig.pid == -1)
			ret = ft_printf("EXIT MINISHELL, GOOD BYE <3\n");
	}
}

void	export_error(char *str)
{
	ft_putstr_fd(RED, STDERR);
	ft_putstr_fd("Minishell: export: \"", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd("\" : not a valid identifier\n", STDERR);
	ft_putstr_fd(RESET, STDERR);
}

void	error_ambigous(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	(void)cmd;
	g_sig.ret = 1;
	ft_putstr_fd(RED, STDERR);
	ft_putstr_fd("Minishell: undefined variable", STDERR);
	ft_putstr_fd(" : ambigous redirect\n", STDERR);
	return ;
}
