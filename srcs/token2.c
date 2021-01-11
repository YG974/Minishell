#include "../libft/libft.h"
#include "../includes/minishell.h"

void	ft_give_flag(t_tok *tok, char c)
{
	if (c == ' ')
		tok->flag = FLAG_SPACE;
	else
		tok->flag = FLAG_STR;
}

int		ft_add_token(t_cmdl *cmd, int i)
{
	t_tok *tmp;

	if (!(tmp = calloc(1, sizeof(t_tok))))
		return (1);
	if (!cmd->firsttoken)
		tmp->flag = FLAG_CMD;
	else
		ft_give_flag(tmp, cmd->str[i]);
	if (tmp->flag != FLAG_SPACE)
		tmp->str = ft_strdup_space(cmd->str + i);
	return (0);
}

int     ft_get_tokens(t_mini *s, t_cmdl *cmd)
{
	int		i;

	i = 0;
    (void)cmd;
    ft_printf("On entre dans la fonction qui split les commandes en tokens.\n");
	while (cmd->str[i] == ' ')
		i++;
	while (cmd->str[i])
	{
		if (ft_add_token(cmd, i))
			error(s, 1);
	}
    ft_printf("On quitte la fonction qui split les commandes en tokens.\n");
    return (0);
}