#include "../libft/libft.h"
#include "../includes/minishell.h"

int		ft_exit_test(t_tok *token)
{
	if (!ft_strncmp(token->str, "exit", 4))
		return (1);
	return (0);
}

int		ft_is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", 4))
		return (1);
	if (!ft_strncmp(str, "cd", 2))
		return (1);
	if (!ft_strncmp(str, "pwd", 3))
		return (1);
	if (!ft_strncmp(str, "export", 6))
		return (1);
	if (!ft_strncmp(str, "unset", 5))
		return (1);
	if (!ft_strncmp(str, "env", 3))
		return (1);
	if (!ft_strncmp(str, "exit", 4))
		return (1);
	return (0);
}

int		exec_bin(t_mini *s, t_cmdl *cmd, char **args)
{
	(void)s;
	(void)cmd;
	(void)args;
	ft_printf("exec BINNN\n");
	return (0);
}

int		exec_builtin(t_mini *s, t_cmdl *cmd, char **args)
{
	// (void)cmd;
	ft_printf("exec buliltin\n");
	if (!ft_strncmp(cmd->str, "echo", 4))
		cmd->ret = ft_echo(s, args);
	if (!ft_strncmp(cmd->str, "cd", 2))
		cmd->ret = ft_cd(s, args);
	if (!ft_strncmp(cmd->str, "pwd", 3))
		cmd->ret = ft_pwd(s, args);
	if (!ft_strncmp(cmd->str, "export", 6))
		cmd->ret = ft_export(s, args);
	if (!ft_strncmp(cmd->str, "unset", 5))
		cmd->ret = ft_unset(s, args);
	if (!ft_strncmp(cmd->str, "env", 3))
		cmd->ret = ft_env(s, args);
	if (!ft_strncmp(cmd->str, "exit", 4))
	{
		if ((s->i = ft_exit(s, args)) == 0)
			cmd->ret = ft_atoi(args[1]);
		ft_printf("ret = %d", cmd->ret);
		error(s, WANT_EXIT);
	}
	return (cmd->ret);
}

int		parse_cmd_args(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	/*if (cmd->buf)*/
		/*free(cmd->buf);*/
	cmd->buf = ft_strdup("");
	cmd->token = cmd->firsttoken;
	ft_printf("parse_cmd_args\n");
	while ((ft_strchr(cmd->token->str, '=')
				|| (cmd->token->flag == 2 && cmd->token->str[0] == ' ')))
		cmd->token = cmd->token->next;
	while (cmd->token)
	{
		/*ft_printf("token :%s|\n", cmd->token->str);*/
		if (cmd->token->flag != 2 && cmd->token)
		{
			cmd->buf = ft_strjoin_free_s1(cmd->buf, cmd->token->str);
			cmd->buf = ft_strjoin_free_s1(cmd->buf, "\n");
			cmd->token = cmd->token->next;
		}
		else if (cmd->token->flag == 2 && cmd->token->str[0] == ' ' && cmd->token)
			cmd->token = cmd->token->next;
		else if (cmd->token->flag == 2 && cmd->token->str[0] != ' ' && cmd->token)
			break;
	}
	/*cmd->token = cmd->firsttoken;*/
	return (cmd->ret);
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
	ft_printf("apply assignement \n");
	return (cmd->ret);

}
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
 * WARNING : the first argument is not always the command
 * -> if first argument is an assignement(contains "="), it looks forward for a
 * command
 * -> if there is a command, it doesnt apply the assignement and try to run cmd
 * -> if there is only an assignement in the command line, it applies it.
 */

void	ft_exe_cmd(t_mini *s, t_cmdl *cmd)
{

	char **args;
    ft_printf("=============>On est rentré dans la fonction d'EXECUTION COMMANDES\n");
	cmd->ret = 0;
	s->i = ft_exe_tokens(s, cmd);
	if (cmd_has_only_assignement(cmd))
		cmd->ret = apply_assignement(s, cmd);
	else 
		parse_cmd_args(s, cmd);
    /*ft_printf("str ok args :%s\n", cmd->buf);*/
	args = ft_split(cmd->buf, '\n');
	print_tab(args);
	if (ft_is_builtin(args[0]))
		cmd->ret = exec_builtin(s, cmd, args);
	else
		cmd->ret = exec_bin(s,cmd, args);
    ft_printf("=============>On est sorti de la fonction d'EXECUTION COMMANDES\n");
}
