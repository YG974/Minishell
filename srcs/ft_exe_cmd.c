#include "../libft/libft.h"
#include "../includes/minishell.h"

	 /*check if the command is a builtin */
	 /*return 1 if it's a builtin */
	 /*return 0 if it's note*/
int		ft_is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "cd", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "pwd", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (1);
	return (0);
}

	 /*open each folder of PATH env variable*/
	/*compare all files whit the cmd name */
	 /*join the PATH whith "/" and with the cmd name -->absolut path*/
	/*return the absolut path if found*/
	/*return NULL if not found*/
char	*try_bin_path(char *bin_path, char *cmd_name)
{
	DIR		*folder;
	struct	dirent *file;
	char	*cmd_path;
	int		len;

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
			break;
	}
	closedir(folder);
	return (cmd_path);
}

int		check_bin_right(char *path)
{
	struct stat		file;
	int				mode;
	DIR				*folder;

	mode = 0;
	stat(path, &file);
	mode = file.st_mode & S_IXUSR;
	if (mode == 0)
	{
		ft_putstr_fd(path, STDERR);
		ft_putstr_fd(" : permission denied\n", STDERR);
		sig.ret = 126;
		return (0);
	}
	if ((folder = opendir(path)))
	{
		ft_putstr_fd(path, STDERR);
		ft_putstr_fd(" : is a directory\n", STDERR);
		sig.ret = 126;
		return (0);
	}
	return (1);
}

	 /*try to find the binary file in each PATH env variable*/
	 /*return path = the absolute path is found*/
	 /*return NULL if the cmd is not find  in PATH ENV*/
char	*find_bin_path(t_mini *s, char **args)
{
	char	**bin_paths;
	char	*path;
	int		i;

	i = 0;
	path = ft_strdup("PATH");
	bin_paths = ft_split(get_env_value(s, path), ':');
	path = NULL;
	if ((path = ft_strchr(args[0], '/')))
		return (args[0]);
	while (bin_paths[i] && !path)
		path = try_bin_path(bin_paths[i++], args[0]);
	if (!path)
	{
		ft_putstr_fd("command not found\n", s->std.err);
		sig.ret = 127;
	}
	/*mieux faire la gestion d'erreur*/
	/*ft_printf("cmd_path :%s|\n", path);*/
	/*print_tab(bin_paths);*/
	/*if (!ft_strncmp(args[0], "env", 3))*/
	/*if (!ft_strchr(args[0], '\\'))*/
	/*env_path = args[0];*/
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

/*exec the binary file if found in PATH env variable and return cmd->ret*/
int		exec_bin(t_mini *s, t_cmdl *cmd, char **args)
{
	char *path;
	char **env;
	int		status;

	sig.pid = fork();
	status = 0;
	if (sig.pid == 0)
	{
		env = put_env_in_tab(s);
		path = find_bin_path(s, args);
		if (path && check_bin_right(path))
			cmd->ret = execve(path, args, env);
		else 
			exit (sig.ret);
		ft_free_tab(env);
		free(path);
	}
	else
		waitpid(sig.pid, &status, 0);
	sig.ret = status;
	if (sig.interrupt == 1 || sig.quit == 1)
		sig.ret = sig.ret + 128;
	/*ft_printf("exec BINNN\n");*/
	return (sig.ret);
}

	 /*exec the builtin and return the ret of the builtin*/
int		exec_builtin(t_mini *s, t_cmdl *cmd, char **args)
{
	/*ft_printf("exec buliltin\n");*/
	(void)cmd;
	if (!ft_strncmp(args[0], "echo", ft_strlen(args[0])))
		sig.ret = ft_echo(s, args);
	if (!ft_strncmp(args[0], "cd", ft_strlen(args[0])))
		sig.ret = ft_cd(s, args);
	if (!ft_strncmp(args[0], "pwd", ft_strlen(args[0])))
		sig.ret = ft_pwd(s, args);
	if (!ft_strncmp(args[0], "export", ft_strlen(args[0])))
		sig.ret = ft_export(s, args);
	if (!ft_strncmp(args[0], "unset", ft_strlen(args[0])))
		sig.ret = ft_unset(s, args);
	if (!ft_strncmp(args[0], "env", ft_strlen(args[0])))
		sig.ret = ft_env(s, args);
	if (!ft_strncmp(args[0], "exit", ft_strlen(args[0])))
	{
		if ((s->i = ft_exit(s, args)) == 2)
			sig.ret = ft_atoi(args[1]);
		else if (s->i == 0)
			sig.ret = 0;
		else
			sig.ret = 1;
		error(s, WANT_EXIT);
	}
	return (sig.ret);
}

	/*parse the arguments into a string, without the meta, each token is */
	/*delimited with '\n' in the string, in order to split it in a char **tab;*/
	/*char **args = ft_split(str, '\n';)*/
int		parse_cmd_args(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	/*if (cmd->buf)*/
		/*free(cmd->buf);*/
	cmd->buf = ft_strdup("");
	cmd->token = cmd->firsttoken;
	/*ft_printf("parse_cmd_args\n");*/
	while ((ft_strchr(cmd->token->str, '=')
				|| (cmd->token->flag == 2 && cmd->token->str[0] == ' ')))
		cmd->token = cmd->token->next;
	while (cmd->token)
	{
		//ft_printf("token :%s|\n", cmd->token->str);
		if (cmd->token->flag != 2 && cmd->token)
		{
			cmd->buf = ft_strjoin_free_s1(cmd->buf, cmd->token->str);
			cmd->buf = ft_strjoin_free_s1(cmd->buf, "\n");
			cmd->token = cmd->token->next;
		}
		else if (cmd->token->flag == 2 && cmd->token->str[0] == ' ' && cmd->token)
			cmd->token = cmd->token->next;
		else if (cmd->token->flag == 2 && cmd->token->str[0] != ' ' && cmd->token)
		{
			cmd->token = cmd->token->next;
			if (cmd->token->flag == 2 && cmd->token->str[0] == ' ' && cmd->token)
				cmd->token = cmd->token->next->next;
			else
				cmd->token = cmd->token->next;
		}
	}
	/*cmd->token = cmd->firsttoken;*/
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
        /*printf("------- TOKEN #%d\n\tline : %s\n\tflag : %d\n-------\n\n", i, cmd->token->str, cmd->token->flag);*/
		cmd->token = cmd->token->next;
		i++;
	}
    return (0);
}

int		apply_assignement(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	// (void)cmd;
	/*ft_printf("apply assignement \n");*/
	return (cmd->ret);

}

	/*check if the command line has only assignement : name=value ...*/
	/*return 0 if there is a command in the line (a string without '=')*/
	/*return 1 if there is only assignements in the command line*/
	/*(only strings that contains '=')*/

int		cmd_has_only_assignement(t_cmdl *cmd)
{
	cmd->token = cmd->firsttoken;
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
 *  this functuin exec builtin, or binary or apply assignmenet
 * WARNING : the first argument is not always the command
 * -> if first argument is an assignement(contains "="), it looks forward for a
 * command
 * -> if there is a command, it doesnt apply the assignement and try to run cmd
 * -> if there is only an assignement in the command line, it applies it.
 */
void	handle_dollar_question_mark(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	cmd->token = cmd->firsttoken;
	while (cmd->token)
	{
		if (cmd->token->str[0] == '$' && cmd->token->str[1] == '?'
			&& cmd->token->str[3] == '\0')
		{
			free(cmd->token->str);
			cmd->token->str = ft_itoa(sig.ret);
			//remplacer par la bonne variable qui contiendra le retour de la
			//commande precedente
		}
		cmd->token = cmd->token->next;
	}
	cmd->token = cmd->firsttoken;
	return ;
}

void	ft_exe_cmd(t_mini *s, t_cmdl *cmd)
{

	char **args;
	int		status;
    /*ft_printf("=============>On est rentré dans la fonction d'EXECUTION COMMANDES\n");*/
	cmd->ret = 0;
	s->i = ft_exe_tokens(s, cmd);
	handle_dollar_question_mark(s, cmd);
	if (cmd_has_only_assignement(cmd))
	{
		cmd->ret = apply_assignement(s, cmd);
		return ;
	}
	else 
		parse_cmd_args(s, cmd);
    /*ft_printf("str ok args :%s\n", cmd->buf);*/
	args = ft_split(cmd->buf, '\n');
	/*print_tab(args);*/
	if (ft_is_builtin(args[0]))
		sig.ret = exec_builtin(s, cmd, args);
	else
		sig.ret = exec_bin(s,cmd, args);
	waitpid(-1, &status, 0);
	sig.ret = sig.ret % 255;
	/*status = WEXITSTATUS(status);*/
	ft_free_tab(args);
    /*ft_printf("=============>On est sorti de la fonction d'EXECUTION COMMANDES\n");*/
}
