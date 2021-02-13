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
//#include <sys/_types/_s_ifmt.h>

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
**	open each folder of PATH env variable
**	compare all files whit the cmd name
**	join the PATH whith "/" and with the cmd name -->absolut path
**	return the absolut path if found
**	return NULL if not found
*/

char	*try_bin_path(char *bin_path, char *cmd_name)
{
	DIR				*folder;
	struct dirent	*file;
	char			*cmd_path;
	int				len;

	len = ft_strlen(cmd_name);
	if (!(folder = opendir(bin_path)))
		return (NULL);
	cmd_path = NULL;
	while ((file = readdir(folder)))
	{
		if (ft_strncmp(file->d_name, cmd_name, len + 1) == 0)
		{
			cmd_path = ft_strjoin(bin_path, "/");
			cmd_path = ft_strjoin_free_s1(cmd_path, file->d_name);
		}
		if (cmd_path)
			break ;
	}
	closedir(folder);
	return (cmd_path);
}

int		ft_str_error(char *path, char *str, int ret)
{
	g_sig.ret = ret;
	(void)str;
	ft_putstr_fd(RED, STDERR);
	ft_putstr_fd("Minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd("\n", STDERR);
	ft_putstr_fd(RESET, STDERR);
	return (-1);
}

/*
**	problem si execution d un fichier qui n'est pas un executable
**	je n'ai pas trouve de solution
*/

int		check_bin_right(char *path, char **args)
{
	struct stat		file;

	if (!path)
		return (ft_str_error(args[0], "command not found", CMD_NOT_FOUND));
	if ((stat(path, &file)) == -1)
		return (ft_str_error(path, "no such file or directory", NOT_EXEC));
	if (S_ISDIR(file.st_mode))
		return (ft_str_error(path, "is a directory", NOT_EXEC));
	else if ((file.st_mode & S_IXUSR) == 0)
		return (ft_str_error(path, "permission denied", NOT_EXEC));
	return (1);
}

/*
**	try to find the binary file in each PATH env variable
**	return path = the absolute path is found
**	return NULL if the cmd is not find  in PATH ENV
*/

char	*find_bin_path(t_mini *s, char **args)
{
	char	**bin_paths;
	char	*path;
	int		i;

	i = 0;
	path = ft_strdup("PATH");
	bin_paths = ft_split(get_env_value(s, path), ':');
	path = NULL;
	if (ft_strchr(args[0], '/'))
		return (args[0]);
	while (bin_paths[i] && !path)
		path = try_bin_path(bin_paths[i++], args[0]);
	return (path);
}

void	ft_free_tab(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env[i]);
	free(env);
}

/*
**	exec the binary file if found in PATH env variable and return cmd->ret
*/

int		exec_bin(t_mini *s, t_cmdl *cmd, char **args)
{
	char	*path;
	char	**env;

	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		env = put_env_in_tab(s);
		path = find_bin_path(s, args);
		if ((check_bin_right(path, args) == 1))
			execve(path, args, env);
		else
			exit(g_sig.ret);
		free(path);
		cmd->ret = cmd->ret;
	}
	else
		waitpid(g_sig.pid, &g_sig.ret, 0);
	g_sig.ret = WEXITSTATUS(g_sig.ret);
	if (g_sig.interrupt == 1 || g_sig.quit == 1)
		g_sig.ret = g_sig.ret + 128;
	return (g_sig.ret);
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
			g_sig.ret = 0;
		else
			g_sig.ret = 1;
		error(s, WANT_EXIT);
	}
	return (g_sig.ret);
}

/*
**	parse the arguments into a string, without the meta, each token is
**	delimited with '\n' in the string, in order to split it in a char **tab;
**	char **args = ft_split(str, '\n';)
*/

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

	/*parse the arguments into a string, without the meta, each token is */
	/*delimited with '\n' in the string, in order to split it in a char **tab;*/
	/*char **args = ft_split(str, '\n';)*/
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
		else if (cmd->token->flag == 2 && cmd->token->str[0] == ' ' && cmd->token)
			cmd->token = cmd->token->next;
		else if (cmd->token->flag == 2 && cmd->token->str[0] != ' ' && cmd->token)
			cmd->token = norme_chlag(cmd->token);
	}
	return (0);
}

int		ft_exe_tokens(t_mini *s, t_cmdl *cmd)
{
	int i;

	i = 1;
	(void)s;
	cmd->token = cmd->firsttoken;
	while (cmd->token)
	{
		cmd->token = cmd->token->next;
		i++;
	}
	return (0);
}

int		apply_assignement(t_mini *s, t_cmdl *cmd)
{
	char **args;

	(void)s;
	cmd->buf = ft_strjoin_free_s1(cmd->buf, "\n");
	cmd->token = cmd->firsttoken;
	while (cmd->token)
	{
		if (ft_strchr(cmd->token->str, '='))
		{
			cmd->buf = ft_strjoin_free_s1(cmd->buf, cmd->token->str);
			cmd->buf = ft_strjoin_free_s1(cmd->buf, "\n");
		}
		cmd->token = cmd->token->next;
	}
	args = ft_split(cmd->buf, '\n');
	if (cmd->buf)
		free(cmd->buf);
	cmd->ret = ft_export(s, args);
	return (cmd->ret);
}

/*
**	check if the command line has only assignement : name=value ...
**	return 0 if there is a command in the line (a string without '=')
**	return 1 if there is only assignements in the command line
**	(only strings that contains '=')
*/

int		cmd_has_only_assignement(t_cmdl *cmd)
{
	cmd->token = cmd->firsttoken;
	if (cmd->token == NULL)
		return (0);
	while (cmd->token)
	{
		if (!(ft_strchr(cmd->token->str, '=')) && cmd->token->flag != 2)
			return (0);
		cmd->token = cmd->token->next;
	}
	cmd->token = cmd->firsttoken;
	return (1);
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

void	ft_exe_cmd(t_mini *s, t_cmdl *cmd)
{
	char	**args;
	int		status;

	cmd->ret = 0;
	s->i = ft_exe_tokens(s, cmd);
	if (cmd_has_only_assignement(cmd))
	{
		g_sig.ret = apply_assignement(s, cmd);
		return ;
	}
	if (cmd->token == NULL)
		return ;
	parse_cmd_args(s, cmd);
	args = ft_split_ms(cmd->buf, '\n');
	free(cmd->buf);
	if (ft_is_builtin(args[0]))
		g_sig.ret = exec_builtin(s, cmd, args);
	else
		g_sig.ret = exec_bin(s, cmd, args);
	waitpid(-1, &status, 0);
	ft_free_tab(args);
}
