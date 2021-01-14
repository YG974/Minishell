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

	i = 1;
	cmd->token = cmd->firsttoken;
	while (cmd->token)
	{
    	printf("------- TOKEN #%d\n\tline : %s\n\tflag : %d\n-------\n\n", i, cmd->token->str, cmd->token->flag);
		if (ft_exit_test(cmd->token))
			return (WANT_EXIT);
		cmd->token = cmd->token->next;
		i++;
	}
    return (0);
}

void	ft_exe_cmd(t_mini *s, t_cmdl *cmd)
{
	int		ret;

	ret = 0;
    (void)s;
    (void)cmd;
    ft_printf("=============>On est rentré dans la fonction d'EXECUTION COMMANDES\n");
    if ((ret = ft_exe_tokens(cmd)))
        error(s, ret);
    ft_printf("=============>On est sorti de la fonction d'EXECUTION COMMANDES\n");
}