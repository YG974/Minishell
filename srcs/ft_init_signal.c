/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:52:58 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/09 16:00:53 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

void	sigprompt(void)
{
	sig_ret();
	ft_putstr_fd(CYAN, STDOUT);
	ft_putstr_fd("\nMINISHELL DU TURFU -> ", STDOUT);
	ft_putstr_fd(RESET, STDOUT);
	g_sig.interrupt = 0;
}

void	handle_sigint(int signum)
{
	(void)signum;
	g_sig.interrupt = 1;
	if (g_sig.in_func == 0)
	{
		ft_putstr_fd("\b\b  ", STDERR);
		ft_putstr_fd("\b", STDOUT);
		sigprompt();
	}
	else
		ft_putstr_fd("\n", STDERR);
}

void	handle_sigquit(int signum)
{
	(void)signum;
	if (g_sig.pid != 0)
	{
		ft_putstr_fd(RED, STDERR);
		ft_putstr_fd("Quitter (core dumped)\n", STDERR);
		ft_putstr_fd(RESET, STDERR);
		g_sig.quit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
}

int		init_signal(t_mini *s)
{
	(void)s;
	g_sig.interrupt = 0;
	g_sig.quit = 0;
	g_sig.pid = 0;
	g_sig.status = 0;
	g_sig.has_pipe = 0;
	g_sig.in_func = 0;
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit);
	return (0);
}
