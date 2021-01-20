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

int		parse_cmd_args(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	// (void)cmd;
	ft_printf("parse_cmd_args\n");
	return (cmd->ret);
}

int		exec_builtin(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	// (void)cmd;
	ft_printf("exec buliltin\n");
	return (cmd->ret);
}

int		ft_exe_tokens(t_mini *s, t_cmdl *cmd)
{
	int i;

	i = 1;
	cmd->token = cmd->firsttoken;
	while (cmd->token)
	{
    	printf("------- TOKEN #%d\n\tline : %s\n\tflag : %d\n-------\n\n", i, cmd->token->str, cmd->token->flag);
		if (ft_is_builtin(cmd->token->str))
			cmd->ret = exec_builtin(s, cmd);
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
	int		cmd_flag;
	
	cmd_flag = 0;
	cmd->token = cmd->firsttoken;
	while (cmd->token)
	{
		if (!(ft_strchr(cmd->token->str, '=')) && cmd->token->flag != 2)
			return (0);
		cmd->token = cmd->token->next;
	}
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

    ft_printf("=============>On est rentré dans la fonction d'EXECUTION COMMANDES\n");
	cmd->ret = 0;
	if (cmd_has_only_assignement(cmd))
		cmd->ret = apply_assignement(s, cmd);
	else 
		parse_cmd_args(s, cmd);
	if ((cmd->ret = ft_exe_tokens(s, cmd)))
		error(s, cmd->ret);
    ft_printf("=============>On est sorti de la fonction d'EXECUTION COMMANDES\n");
}
