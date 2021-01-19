#include "../libft/libft.h"
#include "../includes/minishell.h"

int		ft_exit_test(t_tok *token)
{
	if (!ft_strncmp(token->str, "exit", 4))
		return (1);
	return (0);
}

int		ft_exe_tokens(t_cmdl *cmd)
{
	int i;
	char *cmd_str;

	i = 1;
	cmd->token = cmd->firsttoken;
	cmd_str = ft_strdup("");
	while (cmd->token)
	{
    	printf("------- TOKEN #%d\n\tline : %s\n\tflag : %d\n-------\n\n", i, cmd->token->str, cmd->token->flag);
		cmd_str = ft_strjoin_free_s1(cmd_str, "\n");
		if (ft_strchr(cmd->token->str, '='))
			cmd_str = ft_strjoin_free_s1(cmd_str, cmd->token->str);
		if (!(ft_strchr(cmd->token->str, '=')) && cmd->token->flag != 2)
		{
			if (cmd_str)
				free(cmd_str);
			cmd_str = ft_strdup(cmd->token->str);
		}
		if (ft_exit_test(cmd->token))
			return (WANT_EXIT);
		if (cmd_str)
			printf("%s\n", cmd_str);
		cmd->token = cmd->token->next;
		i++;
	}
    return (0);
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
	if ((cmd->ret = ft_exe_tokens(cmd)))
		error(s, cmd->ret);
    ft_printf("=============>On est sorti de la fonction d'EXECUTION COMMANDES\n");
}
