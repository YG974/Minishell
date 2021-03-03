/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:41:58 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/09 15:39:42 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

int		ft_is_builtin(char *str)
{
	if (ft_strlen(str) == 4 && !ft_strncmp(str, "echo", 4))
		return (1);
	if (ft_strlen(str) == 2 && !ft_strncmp(str, "cd", 2))
		return (1);
	if (ft_strlen(str) == 3 && !ft_strncmp(str, "pwd", 3))
		return (1);
	if (ft_strlen(str) == 6 && !ft_strncmp(str, "export", 6))
		return (1);
	if (ft_strlen(str) == 5 && !ft_strncmp(str, "unset", 5))
		return (1);
	if (ft_strlen(str) == 3 && !ft_strncmp(str, "env", 3))
		return (1);
	if (ft_strlen(str) == 4 && !ft_strncmp(str, "exit", 4))
		return (1);
	return (0);
}

/*
**	exec the builtin and return the ret of the builtin
*/

int		exec_builtin(t_mini *s, t_cmdl *cmd, char **args)
{
	(void)cmd;
	if (ft_strlen(args[0]) == 4 && !ft_strncmp(args[0], "echo", 4))
		g_sig.ret = ft_echo(s, args);
	if (ft_strlen(args[0]) == 2 && !ft_strncmp(args[0], "cd", 2))
		g_sig.ret = ft_cd(s, args);
	if (ft_strlen(args[0]) == 3 && !ft_strncmp(args[0], "pwd", 3))
		g_sig.ret = ft_pwd(s, args);
	if (ft_strlen(args[0]) == 6 && !ft_strncmp(args[0], "export", 6))
		g_sig.ret = ft_export(s, args);
	if (ft_strlen(args[0]) == 5 && !ft_strncmp(args[0], "unset", 5))
		g_sig.ret = ft_unset(s, args);
	if (ft_strlen(args[0]) == 3 && !ft_strncmp(args[0], "env", 3))
		g_sig.ret = ft_env(s, args);
	if (ft_strlen(args[0]) == 4 && !ft_strncmp(args[0], "exit", 4))
	{
		if ((s->i = ft_exit(s, args)) == 2)
			g_sig.ret = ft_atoi(args[1]);
		else if (s->i == 0)
			g_sig.ret = g_sig.ret;
		else
			g_sig.ret = 2;
		error(s, WANT_EXIT);
	}
	return (g_sig.ret);
}

void	sig_ret(void)
{
	if (g_sig.pid == 0 || g_sig.has_pipe == 0)
	{
		if (g_sig.interrupt == 1)
			g_sig.ret = 130;
		if (g_sig.quit == 1)
			g_sig.ret = 131;
	}
}

/*
**	this functuin exec builtin, or binary or apply assignmenet
**	WARNING : the first argument is not always the command
**	-> if first argument is an assignement(contains "="),
**	it looks forward for a
**	command
**	-> if there is a command, it doesnt apply the assignement
**	and try to run cmd
**	-> if there is only an assignement in the command line, it applies it.
*/

void	ft_exe_cmd(t_mini *s, t_cmdl *cmd)
{
	char	**args;
	int		status;

	cmd->ret = 0;
	g_sig.in_func = 1;
	if (cmd->buf)
		free(cmd->buf);
	parse_cmd_args(s, cmd);
	args = ft_split_ms(cmd->buf, '\n');
	free(cmd->buf);
	if (!args[0] || args[0][0] == '\0')
		return ;
	if (ft_is_builtin(args[0]))
		g_sig.ret = exec_builtin(s, cmd, args);
	else
		g_sig.ret = exec_bin(s, cmd, args);
	waitpid(-1, &status, 0);
	sig_ret();
	ft_free_tab(args);
}
