/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
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
		return (ft_str_error(path, "no such file or directory", CMD_NOT_FOUND));
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
	path = get_env_value(s, path);
	bin_paths = ft_split(path, ':');
	free(path);
	path = NULL;
	if (ft_strchr(args[0], '/'))
	{
		ft_free_tab(bin_paths);
		return (args[0]);
	}
	while (bin_paths[i] && !path)
		path = try_bin_path(bin_paths[i++], args[0]);
	ft_free_tab(bin_paths);
	return (path);
}

/*
**	exec the binary file if found in PATH env variable and return cmd->ret
*/

int		exec_bin(t_mini *s, t_cmdl *cmd, char **args)
{
	char	*path;
	char	**env;

	g_sig.pid = fork();
	(void)cmd;
	if (g_sig.pid == 0)
	{
		env = put_env_in_tab(s);
		path = find_bin_path(s, args);
		if (check_bin_right(path, args) == 1)
			execve(path, args, env);
		else
		{
			free_all(s, args, env, path);
			exit(g_sig.ret);
		}
	}
	else
		waitpid(g_sig.pid, &g_sig.ret, 0);
	ft_del_tokens(s->currentcmdl, 0);
	g_sig.ret = WEXITSTATUS(g_sig.ret);
	return (g_sig.ret);
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
